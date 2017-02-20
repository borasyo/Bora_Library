//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [main.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include <stdio.h>
#include <time.h>
#include "d3dx9.h"
#include "../Library/Debug/DebugWindow.h"
#include "../Library/Debug/MemoryLeakDebug.h"
#include "GameBase.h"

// ---- メイン
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR CmdLine, int ShowCmd )
{
	//_CrtSetBreakAlloc(285); // メモリリーク時、メモリ番号が固定ならこれで場所を検出できる
	srand((unsigned int)time(NULL)); // シード値設定

	Debug::DebugWindow DebugWindow;
	DebugWindow.Init();

	SetMemoryLeakDebug();

	CGameBase GameBase;

	// ゲームを走らせる
	return GameBase.Run();
}