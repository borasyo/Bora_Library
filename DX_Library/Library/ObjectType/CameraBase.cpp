//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CameraBase.cpp]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CameraBase.h"

CCameraBase::CCameraBase() {
	m_Transform.Name = "CameraBase";
	m_Transform.Tag = "Camera";
	m_nSortingLayer = DEPTH_CAMERA;
}

CCameraBase::~CCameraBase() {
	
}

bool CCameraBase::Start() {
	
	// 当たり判定は行わない
	SetCollisionFlg(false);
	
	// 画ブレ用変数初期化
	m_bSway = false;
	m_nNowTime = 0;
	m_nMaxTime = 0;
	m_fSwayRange = 0.0f;
	m_fTotalSway = 0.0f;
	m_bBeside = false;
	m_fSwayAmount = 0.0f;

	return true;
}

void CCameraBase::Update() {
	
	if( m_bSway ) {

		D3DXVECTOR3 Pos = m_Transform.Position;

		if( m_nNowTime % 2 == 0 ) {
			m_fSwayAmount = rand()%((int)(m_fSwayRange*100))/100.0f + 0.1f;
		}

		// プラス方向か
		if( m_bUp ) {
			m_fTotalSway = m_fSwayAmount;
		}
		// マイナス方向か
		else {
			m_fTotalSway = -m_fSwayAmount;
		}
		
		// 横揺れなら
		if( m_bBeside ) {
			
			float fDistanceX = m_Camera.GetLookatPt()->x - Pos.x;
			float fDistanceZ = m_Camera.GetLookatPt()->z - Pos.z;
			float fAngle = atan2f(fDistanceX,fDistanceZ)+Pai/2;
			float fSin = sinf(fAngle);
			float fCos = cosf(fAngle);

			Pos.x += fSin*m_fTotalSway;
			Pos.z += fCos*m_fTotalSway;
			m_Camera.GetLookatPt()->x += fSin*m_fTotalSway;
			m_Camera.GetLookatPt()->z += fCos*m_fTotalSway;
		}

		// 縦揺れなら
		else {
			Pos.y += m_fTotalSway;
			m_Camera.GetLookatPt()->y += m_fTotalSway;
		}
		
		// 反転
		m_bUp = !m_bUp;

		// カウントアップ
		m_nNowTime ++;
		if( m_nNowTime >= m_nMaxTime ) {
			m_bSway = false;
		}
	}
}

void CCameraBase::FastDraw() {
	m_Camera.Set(m_Transform.Position);
}

// 時間、揺れる範囲、揺れるスピード、縦か横か (ダウンキャストあり)
void CCameraBase::Sway( int nTime, float fSwayRange, bool bBeside, bool bUp  ) {
	
	// 重複禁止
	if( m_bSway )
		return;

	// 各値を設定
	m_nMaxTime = nTime;
	m_fSwayRange = fSwayRange;
	m_bBeside = bBeside;	// trueなら横揺れ
	m_bUp = bUp;
	m_bSway = true;
	m_nNowTime = 0;
	m_fTotalSway = 0.0f;
	m_fSwayAmount = 0.0f;
}