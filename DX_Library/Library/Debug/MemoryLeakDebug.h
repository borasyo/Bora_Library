//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MemoryLeakDebug.h]
// author : 大洞祥太
// 
// MemoryLeakをチェックする
// 
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MEMORYLEAKDEBUG_H_____
#define _____MEMORYLEAKDEBUG_H_____

#include "../Function/Define.h"

#ifdef DEBUG
	#include <crtdbg.h>
#endif

// セットアップ
void SetMemoryLeakDebug(){
	
#ifdef DEBUG
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
}

#endif