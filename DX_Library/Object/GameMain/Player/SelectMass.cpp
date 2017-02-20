//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SelectMass.cpp]
// author : �哴�ˑ�
//
// �T�v : �v���C���|���}�X�𑀍삷��Ƃ��̎w�W
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "SelectMass.h"
#include "../Field/FieldMass.h"

//	--	���̒�`
//bool CSelectMass::m_bSelect = false;

const float fMaxTime = 0.15f;	// 1.0f��1�b��1�񔽉�

CSelectMass::CSelectMass(CCharactorManager* pCharactorManager, CFieldMassManager* pFieldMassManager) {

	m_Transform.Name = "SelectMass";
	
	//	�`��ݒ�
	m_Transform.Size = D3DXVECTOR3(BOX_SIZE, 1.0f, BOX_SIZE);
	m_Obj.SetFileName(_T("Player/SelectMass.png"));
	m_Obj.SetBillFlg(false);
	m_Obj.SetMatrix(this);

	//	�}�l�[�W���N���X�̃|�C���^�i�[
	m_pCharactorManager = pCharactorManager;
	m_pFieldMassManager = pFieldMassManager;
	std::vector<CFieldMass*> Mass = m_pFieldMassManager->GetMassList();

	//	�}�X�̐����A���W�i�[�z��𐶐�
	m_MassPos = new D3DXVECTOR3[Mass.size()];	// �}�X�̐���
	int nCnt = 0;
	for(auto Ite = Mass.begin(); Ite != Mass.end(); Ite++, nCnt++) {
		m_MassPos[nCnt] = *((*Ite)->GetPosition());
	}

	//	�e�ϐ�������
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

	// Input�擾
	CDirectInputManager* pI = CDirectInputManager::Instance();

	// �I�𔻒�
	if(pI->GetKeyboardTrigger(DIK_RETURN) || pI->GetJoyTrigger(0, JOYBUTTON_01)) {
		
		if(CheckCharaSelect()) {
			m_bSelect = true;
			DebugLog("�L������I������");
		} else {
			m_bSelect = false;
			DebugLog("�����ɃL�����͂��Ȃ�...");
		}
	}

	// �L�����Z������
	if(pI->GetKeyboardTrigger(DIK_BACKSPACE) || pI->GetJoyTrigger(0, JOYBUTTON_03)) {
		m_bSelect = false;
		m_pNowSelectChara->Select(false);
		m_pNowSelectChara = nullptr;
		DebugLog("�L�����Z��");
	}

	// ���͂��󂯕t���邩�X�V������
	m_fNowTime += CTime::GetDeltaTime();
	if(m_fNowTime < fMaxTime)
		return;

	// ���͔���㉺
	if(pI->GetKeyboardHold(DIK_W) || pI->GetJoyAxisPress(0, JOY_Y) < 0) {
		MoveSelect(MOVE_UP);
	} 

	else if(pI->GetKeyboardHold(DIK_S) || pI->GetJoyAxisPress(0, JOY_Y) > 0) {
		MoveSelect(MOVE_DOWN);
	} 
	
	// ���͔��荶�E
	if(pI->GetKeyboardHold(DIK_A) || pI->GetJoyAxisPress(0, JOY_X) < 0) {
		MoveSelect(MOVE_LEFT);
	} 

	else if(pI->GetKeyboardHold(DIK_D) || pI->GetJoyAxisPress(0, JOY_X) > 0) {
		MoveSelect(MOVE_RIGHT);
	} 

	// ���o�����Ȃ�
	// .....
}

void CSelectMass::Draw() {
	m_Obj.Draw(this);
}

//	�L������I�����������`�F�b�N
bool CSelectMass::CheckCharaSelect() {

	std::list<CCharactorBase*> Temp = m_pCharactorManager->GetPlayerChara();

	for(auto Ite = Temp.begin(); Ite != Temp.end(); Ite++) {
		if(!m_Collsion.CollisionCubeandPoint(*Ite, this))
			continue;

		//	��������
		m_pNowSelectChara = *Ite;
		m_pNowSelectChara->Select(true);
		return true;
	}

	//	���������L�����͋��Ȃ�����
	return false;
}

//	�Z���N�g�}�X�̈ʒu���ړ�
void CSelectMass::MoveSelect(eMoveVec moveVec) {

	int nTemp = m_nNowMass;	//	���ۑ�

	// Mass�ړ�����O�`�F�b�N
	switch(moveVec) {

		// ���Ɉړ�
	case MOVE_UP:
		m_nNowMass --;
		
		if(m_nMassRange - 1 == m_nNowMass % m_nMassRange)
			m_nNowMass += m_nMassRange; // 
		
		if(m_nNowMass < 0)
			m_nNowMass = m_nMassRange - 1;

		break;

		// ��O�Ɉړ�
	case MOVE_DOWN:
		m_nNowMass ++;
		
		if(0 == m_nNowMass % m_nMassRange)
			m_nNowMass -= m_nMassRange; // 

		if(m_nNowMass >= m_nMassMax) 
			m_nNowMass = m_nMassMax - 1;
		
		break;
		

		// �E�Ɉړ�
	case MOVE_RIGHT:
		m_nNowMass -= m_nMassRange;
		
		if(m_nNowMass < 0) 
			m_nNowMass = m_nNowMass + m_nMassMax;

		break;

		// ���Ɉړ�
	case MOVE_LEFT:
		m_nNowMass += m_nMassRange;
		
		if(m_nNowMass >= m_nMassMax) 
			m_nNowMass = m_nNowMass % m_nMassRange;

		break;
	}

	// �`��ʒu�ύX
	m_Transform.Position = m_MassPos[m_nNowMass];

	// �^�C�}�[���Z�b�g
	m_fNowTime = 0.0f;
}