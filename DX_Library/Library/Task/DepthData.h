//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DepthData.h]
// author : 大洞祥太
//
// 概要 : デプスを指定しているオブジェクトの値を列挙化
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DepthData_h_____
#define _____DepthData_h_____

#include <iostream>
#include <stdio.h>

// Depth定数
enum eDepth {

	// ---- 描画早い ----
	
	DEPTH_MIN = -100, 
	DEPTH_CAMERA,
	DEPTH_CLICK,

	DEPTH_FADE,
	DEPTH_TUTORIAL,
	DEPTH_DEBUG,
	DEPTH_BAR,
	DEPTH_ROTUI,
	DEPTH_PARTICLE,
	DEPTH_SCENE,

	DEPTH_NORMAL = 0,

	DEPTH_BACK,
	
	// ---- 描画遅い ----

	DEPTH_MAX,
};

#endif