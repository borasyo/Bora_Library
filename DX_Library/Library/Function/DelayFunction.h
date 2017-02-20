//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DelayFunction.h]
// author : 大洞祥太
// 
// 指定の関数を指定した秒数後に実行する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DelayFunction_H_____
#define _____DelayFunction_H_____

#include <time.h>
#include <Windows.h>
#include <list>
#include <initializer_list>
#include <functional>

// 遅らせる関数を作成するための親クラス
class IDelayFunction
{
private:
	DWORD	m_ExecTime;		// 実行予定時間
	int m_nPriority;		// 優先度

public:
	IDelayFunction() : m_ExecTime(0),m_nPriority(0) {}
	virtual ~IDelayFunction() {}

	// 予約する関数をセットする関数
	//virtual void SetFunction( std::function<void()> Function ) = 0;
	
	// ここで関数を呼ぶので、指定の物にオーバーライドする必要がある。
	virtual void Run () = 0;

	// 引数が必要であればオーバーライド
	virtual void SetArgument () {}

	// 何秒後に実行するか時間を指定
	inline void SetExecTime( DWORD time ) { m_ExecTime = time; }

	// 設定した時間を取得
	inline const DWORD GetExecTime() const { return m_ExecTime; }

	const bool operator< ( const IDelayFunction& rhs ) const
	{
		// 同時に実行される場合は、優先度をチェック
		if( GetExecTime() == rhs.GetExecTime() ) {
			return m_nPriority > rhs.m_nPriority;
		}

		// 問題なければ通常実行
		return GetExecTime() > rhs.GetExecTime();
	}
};

class CDelayFunctionManager
{
	
private:
	// メンバ変数
	static CDelayFunctionManager* m_pDelayFunctionManager;
	std::list<IDelayFunction*> m_FuncList;

	// メンバ関数
	CDelayFunctionManager();

public:
	~CDelayFunctionManager();

	// 実体取得
	static CDelayFunctionManager* Instance() { return m_pDelayFunctionManager; }

	// 予約関数を追加
	void Add( IDelayFunction* pFunc );
	
	// 現在から指定秒後の時間を取得
	DWORD AfterTime( float x );

	// 格納されている関数をチェック
	void CheckStoreFunc();
};	

#endif