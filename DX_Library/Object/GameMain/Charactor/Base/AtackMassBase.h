//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackMassBase.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackMassBase_H_____
#define _____AtackMassBase_H_____

#include <iostream>
#include "../../../../Library/Task/TaskManager.h"
#include "../../../../Library/Task/GameObject.h"
#include "../../../../Library/ObjectType/Object3D_Polygon.h"

class CAtackMassBase : public GameObject {

protected:
	CObject3DPolygon m_Mass;

public:

	CAtackMassBase();
	~CAtackMassBase();

	bool Start();
	void Update();
	void Draw();
	
	CAtackMassBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackMassBase" ) // Ž¸”s!!!
			return nullptr;

		CAtackMassBase* Child = static_cast<CAtackMassBase*>(Obj); 
		return Child;
	}
};

#endif