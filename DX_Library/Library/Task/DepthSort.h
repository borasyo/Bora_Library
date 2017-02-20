//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DepthSort.h]
// author : 大洞祥太
//
// 概要 : ソートをかける際に使用する関数
// ※勝手なインクルード禁止！！！
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DepthSort_h_____
#define _____DepthSort_h_____

#include "GameObject.h"

// 深度ソート用関数
bool CheckDepth(GameObject* lhs, GameObject* rhs) { 

	if(lhs->GetSortingLayer() != rhs->GetSortingLayer())
		return lhs->GetSortingLayer() > rhs->GetSortingLayer();

	return lhs->GetOrderinLayer() < rhs->GetOrderinLayer(); 
}

#endif