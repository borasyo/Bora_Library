//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DelayFunctionManager.cpp]
// author : 大洞祥太
// 
// 関数実行を指定したフレーム数遅らせてから実行する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "DelayFunction.h"
#include <list>

// 実体定義
CDelayFunctionManager* CDelayFunctionManager::m_pDelayFunctionManager = new CDelayFunctionManager;

// コンストラクタ
CDelayFunctionManager::CDelayFunctionManager() {

}

// デストラクタ
CDelayFunctionManager::~CDelayFunctionManager() {
	for( auto Ite = m_FuncList.begin(); Ite != m_FuncList.end(); Ite++ ) delete *Ite;
	m_FuncList.erase(m_FuncList.begin(),m_FuncList.end());
}

// 予約関数を追加
void CDelayFunctionManager::Add( IDelayFunction* pFunc ) { 
	m_FuncList.push_back( pFunc ); 
}

// 現在から指定秒後の時間を取得
DWORD CDelayFunctionManager::AfterTime( float x ) { 
	return timeGetTime() + (DWORD)(x*1000); 
}

// 格納されている関数をチェック
void CDelayFunctionManager::CheckStoreFunc()
{
	// 空でないなら
	DWORD dwNowTime = timeGetTime();
	for(auto Ite = m_FuncList.begin(); Ite != m_FuncList.end();) {
		
		// List順に時間を計測
		if ( (*Ite)->GetExecTime() <= dwNowTime )
		{
			// 実行
			(*Ite)->Run(); 
			auto temp = (*Ite);
			Ite = m_FuncList.erase(Ite);
			delete temp;
		}
		// Topがまだ実行しないならその他も実行しない
		else
		{
			break;
		}
	}
}