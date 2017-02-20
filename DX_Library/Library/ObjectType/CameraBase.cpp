//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CameraBase.cpp]
// author : �哴�ˑ�
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
	
	// �����蔻��͍s��Ȃ�
	SetCollisionFlg(false);
	
	// ��u���p�ϐ�������
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

		// �v���X������
		if( m_bUp ) {
			m_fTotalSway = m_fSwayAmount;
		}
		// �}�C�i�X������
		else {
			m_fTotalSway = -m_fSwayAmount;
		}
		
		// ���h��Ȃ�
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

		// �c�h��Ȃ�
		else {
			Pos.y += m_fTotalSway;
			m_Camera.GetLookatPt()->y += m_fTotalSway;
		}
		
		// ���]
		m_bUp = !m_bUp;

		// �J�E���g�A�b�v
		m_nNowTime ++;
		if( m_nNowTime >= m_nMaxTime ) {
			m_bSway = false;
		}
	}
}

void CCameraBase::FastDraw() {
	m_Camera.Set(m_Transform.Position);
}

// ���ԁA�h���͈́A�h���X�s�[�h�A�c������ (�_�E���L���X�g����)
void CCameraBase::Sway( int nTime, float fSwayRange, bool bBeside, bool bUp  ) {
	
	// �d���֎~
	if( m_bSway )
		return;

	// �e�l��ݒ�
	m_nMaxTime = nTime;
	m_fSwayRange = fSwayRange;
	m_bBeside = bBeside;	// true�Ȃ牡�h��
	m_bUp = bUp;
	m_bSway = true;
	m_nNowTime = 0;
	m_fTotalSway = 0.0f;
	m_fSwayAmount = 0.0f;
}