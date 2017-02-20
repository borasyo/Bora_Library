//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ObjectFactory.h]
// author : 大洞祥太
// 
// オブジェクト生成時、子クラスを返す。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____ObjectFactory_H_____
#define _____ObjectFactory_H_____

#include "TaskManager.h"

template<class T> 
T* CreateObject(T* pObj) {

	TaskManager::Instance()->CreateObject(pObj);

	return pObj;
}

#endif