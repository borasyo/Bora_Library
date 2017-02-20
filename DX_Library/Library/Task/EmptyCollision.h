//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [EmptyCollision.h]
// author : 大洞祥太
//
// 空のオブジェクト。
// 複数のオブジェクトをまとめる親が欲しい時に生成する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____EmptyCollision_H_____
#define _____EmptyCollision_H_____

#include <iostream>
#include "GameObject.h"
#include "../ObjectType/Object3D_Model.h"

class EmptyCollision : public GameObject {

private:
	CObject3DModel m_ColObj;

public:
	EmptyCollision(std::string Name, D3DXVECTOR3 CubeSize, float fCircleSize);
	~EmptyCollision();

	bool Start();
	void LateDraw();
	
	EmptyCollision* GetDownCastClass(GameObject* Obj){
		return nullptr; // 空のオブジェクトなのでダウンキャストさせない
	}
};

#endif