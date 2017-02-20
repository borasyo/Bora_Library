//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DepthSort.h]
// author : �哴�ˑ�
//
// �T�v : �\�[�g��������ۂɎg�p����֐�
// ������ȃC���N���[�h�֎~�I�I�I
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DepthSort_h_____
#define _____DepthSort_h_____

#include "GameObject.h"

// �[�x�\�[�g�p�֐�
bool CheckDepth(GameObject* lhs, GameObject* rhs) { 

	if(lhs->GetSortingLayer() != rhs->GetSortingLayer())
		return lhs->GetSortingLayer() > rhs->GetSortingLayer();

	return lhs->GetOrderinLayer() < rhs->GetOrderinLayer(); 
}

#endif