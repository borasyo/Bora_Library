//=======================================================================================
//
//	  Time�֌W����֐�
//
//=======================================================================================
#include "Time.h"
#include <iostream>

float CTime::m_fDeltaTime = 0.0f;
DWORD CTime::m_dwOldTime = 0;
float CTime::m_fSpeed = 0.0f;

//	�R���X�g���N�^
CTime::CTime() {

}

//	�f�X�g���N�^
CTime::~CTime() {

}

//	������
void CTime::Init() {
	m_fDeltaTime = 0.0f;
	m_dwOldTime = timeGetTime();
	m_fSpeed = 1.0f;
}

//	�X�V
void CTime::Update() {

	//	���Ԏ擾
	DWORD dwNowTime = timeGetTime();

	//	�o�ߎ��ԍX�V
	m_fDeltaTime = (float)(dwNowTime - m_dwOldTime) / 1000.0f;

	// ���Ԃ�ۑ�
	m_dwOldTime = dwNowTime;
}