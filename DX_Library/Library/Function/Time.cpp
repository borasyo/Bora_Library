//=======================================================================================
//
//	  Time関係自作関数
//
//=======================================================================================
#include "Time.h"
#include <iostream>

float CTime::m_fDeltaTime = 0.0f;
DWORD CTime::m_dwOldTime = 0;
float CTime::m_fSpeed = 0.0f;

//	コンストラクタ
CTime::CTime() {

}

//	デストラクタ
CTime::~CTime() {

}

//	初期化
void CTime::Init() {
	m_fDeltaTime = 0.0f;
	m_dwOldTime = timeGetTime();
	m_fSpeed = 1.0f;
}

//	更新
void CTime::Update() {

	//	時間取得
	DWORD dwNowTime = timeGetTime();

	//	経過時間更新
	m_fDeltaTime = (float)(dwNowTime - m_dwOldTime) / 1000.0f;

	// 時間を保存
	m_dwOldTime = dwNowTime;
}