//=======================================================================================
//
//	  Time関係自作関数
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
	static float m_fDeltaTime;	//	1フレームにおける経過秒数(1.0fで1秒)
	static DWORD m_dwOldTime;	//	前フレームの経過時間
	static float m_fSpeed;		//	デルタタイムに補正をかける(通常1倍)
	
private:
	CTime();

public:
	~CTime();

	// ---- 勝手に呼んではいけない
	static void Init();
	static void Update();	

	// ---- デルタタイム取得
	static float GetDeltaTime() { return m_fDeltaTime * m_fSpeed; }

	// ---- 相対スピードを変更
	static void SetSpeed(float fSpeed) { m_fSpeed = fSpeed; }

	// ---- 指定した時間で指定した数、変動させる場合の計算を行う
	// ex) Max = (3,3,3), Time = 1.0f の場合、1秒で(3,3,3)拡大するために1Fにおける拡大量を返す。
	//	   60FPSの場合、(0.05,0.05,0.05)が返る。
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