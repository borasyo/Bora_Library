//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SelectMass.cpp]
// author : 大洞祥太
//
// 概要 : プレイヤ－がマスを操作するときの指標
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SelectMass.h"
#include "../Field/FieldMass.h"

//	--	実体定義
//bool CSelectMass::m_bSelect = false;

const float fMaxTime = 0.15f;	// 1.0fで1秒に1回反応

CSelectMass::CSelectMass(CCharactorManager* pCharactorManager, CFieldMassManager* pFieldMassManager) {

	m_Transform.Name = "SelectMass";
	
	//	描画設定
	m_Transform.Size = D3DXVECTOR3(BOX_SIZE, 1.0f, BOX_SIZE);
	m_Obj.SetFileName(_T("Player/SelectMass.png"));
	m_Obj.SetBillFlg(false);
	m_Obj.SetMatrix(this);

	//	マネージャクラスのポインタ格納
	m_pCharactorManager = pCharactorManager;
	m_pFieldMassManager = pFieldMassManager;
	std::vector<CFieldMass*> Mass = m_pFieldMassManager->GetMassList();

	//	マスの数分、座標格納配列を生成
	m_MassPos = new D3DXVECTOR3[Mass.size()];	// マスの数分
	int nCnt = 0;
	for(auto Ite = Mass.begin(); Ite != Mass.end(); Ite++, nCnt++) {
		m_MassPos[nCnt] = *((*Ite)->GetPosition());
	}

	//	各変数初期化
	m_nNowMass = 0;
	m_nMassMax = Mass.size();
	m_nMassRange = (int)sqrtf(Mass.size());
	m_Transform.Position = m_MassPos[m_nNowMass];
	m_fNowTime = 0.0f;
	m_pNowSelectChara = nullptr;
}

CSelectMass::~CSelectMass() {

}

void CSelectMass::Update() {

	// Input取得
	CDirectInputManager* pI = CDirectInputManager::Instance();

	// 選択判定
	if(pI->GetKeyboardTrigger(DIK_RETURN) || pI->GetJoyTrigger(0, JOYBUTTON_01)) {
		
		if(CheckCharaSelect()) {
			m_bSelect = true;
			DebugLog("キャラを選択した");
		} else {
			m_bSelect = false;
			DebugLog("そこにキャラはいない...");
		}
	}

	// キャンセル判定
	if(pI->GetKeyboardTrigger(DIK_BACKSPACE) || pI->GetJoyTrigger(0, JOYBUTTON_03)) {
		m_bSelect = false;
		m_pNowSelectChara->Select(false);
		m_pNowSelectChara = nullptr;
		DebugLog("キャンセル");
	}

	// 入力を受け付けるか更新＆判定
	m_fNowTime += CTime::GetDeltaTime();
	if(m_fNowTime < fMaxTime)
		return;

	// 入力判定上下
	if(pI->GetKeyboardHold(DIK_W) || pI->GetJoyAxisPress(0, JOY_Y) < 0) {
		MoveSelect(MOVE_UP);
	} 

	else if(pI->GetKeyboardHold(DIK_S) || pI->GetJoyAxisPress(0, JOY_Y) > 0) {
		MoveSelect(MOVE_DOWN);
	} 
	
	// 入力判定左右
	if(pI->GetKeyboardHold(DIK_A) || pI->GetJoyAxisPress(0, JOY_X) < 0) {
		MoveSelect(MOVE_LEFT);
	} 

	else if(pI->GetKeyboardHold(DIK_D) || pI->GetJoyAxisPress(0, JOY_X) > 0) {
		MoveSelect(MOVE_RIGHT);
	} 

	// 演出処理など
	// .....
}

void CSelectMass::Draw() {
	m_Obj.Draw(this);
}

//	キャラを選択したかをチェック
bool CSelectMass::CheckCharaSelect() {

	std::list<CCharactorBase*> Temp = m_pCharactorManager->GetPlayerChara();

	for(auto Ite = Temp.begin(); Ite != Temp.end(); Ite++) {
		if(!m_Collsion.CollisionCubeandPoint(*Ite, this))
			continue;

		//	当たった
		m_pNowSelectChara = *Ite;
		m_pNowSelectChara->Select(true);
		return true;
	}

	//	当たったキャラは居なかった
	return false;
}

//	セレクトマスの位置を移動
void CSelectMass::MoveSelect(eMoveVec moveVec) {

	int nTemp = m_nNowMass;	//	情報保存

	// Mass移動＆例外チェック
	switch(moveVec) {

		// 奥に移動
	case MOVE_UP:
		m_nNowMass --;
		
		if(m_nMassRange - 1 == m_nNowMass % m_nMassRange)
			m_nNowMass += m_nMassRange; // 
		
		if(m_nNowMass < 0)
			m_nNowMass = m_nMassRange - 1;

		break;

		// 手前に移動
	case MOVE_DOWN:
		m_nNowMass ++;
		
		if(0 == m_nNowMass % m_nMassRange)
			m_nNowMass -= m_nMassRange; // 

		if(m_nNowMass >= m_nMassMax) 
			m_nNowMass = m_nMassMax - 1;
		
		break;
		

		// 右に移動
	case MOVE_RIGHT:
		m_nNowMass -= m_nMassRange;
		
		if(m_nNowMass < 0) 
			m_nNowMass = m_nNowMass + m_nMassMax;

		break;

		// 左に移動
	case MOVE_LEFT:
		m_nNowMass += m_nMassRange;
		
		if(m_nNowMass >= m_nMassMax) 
			m_nNowMass = m_nNowMass % m_nMassRange;

		break;
	}

	// 描画位置変更
	m_Transform.Position = m_MassPos[m_nNowMass];

	// タイマーリセット
	m_fNowTime = 0.0f;
}