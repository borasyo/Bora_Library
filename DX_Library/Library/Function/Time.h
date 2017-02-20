//=======================================================================================
//
//	  Time�֌W����֐�
//
//=======================================================================================

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TIME_H_____
#define _____TIME_H_____

#include <time.h>
#include "Define.h"

class CTime { 

private:
	static float m_fDeltaTime;	//	1�t���[���ɂ�����o�ߕb��(1.0f��1�b)
	static DWORD m_dwOldTime;	//	�O�t���[���̌o�ߎ���
	static float m_fSpeed;		//	�f���^�^�C���ɕ␳��������(�ʏ�1�{)
	
private:
	CTime();

public:
	~CTime();

	// ---- ����ɌĂ�ł͂����Ȃ�
	static void Init();
	static void Update();	

	// ---- �f���^�^�C���擾
	static float GetDeltaTime() { return m_fDeltaTime * m_fSpeed; }

	// ---- ���΃X�s�[�h��ύX
	static void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

	// ---- �w�肵�����ԂŎw�肵�����A�ϓ�������ꍇ�̌v�Z���s��
	// ex) Max = (3,3,3), Time = 1.0f �̏ꍇ�A1�b��(3,3,3)�g�傷�邽�߂�1F�ɂ�����g��ʂ�Ԃ��B
	//	   60FPS�̏ꍇ�A(0.05,0.05,0.05)���Ԃ�B
	static D3DXVECTOR3 GetChangeAmount(D3DXVECTOR3 Max, float fTime) {
		return Max * (m_fDeltaTime / fTime);
	}

	static D3DXVECTOR2 GetChangeAmount(D3DXVECTOR2 Max, float fTime) {
		return Max * (m_fDeltaTime / fTime);
	}

	static float GetChangeAmount(float Max, float fTime) {
		return Max * (m_fDeltaTime / fTime);
	}

	static int GetChangeAmount(int Max, float fTime) {
		return (int)(Max * (m_fDeltaTime / fTime));
	}

	static D3DXCOLOR GetChangeAmount(D3DXCOLOR Max, float fTime) {
		return Max * (m_fDeltaTime / fTime);
	}
};

#endif