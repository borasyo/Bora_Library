//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldMass.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FieldMass_H_____
#define _____FieldMass_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"
#include "../../../Library/ObjectType/Object3D_Polygon.h"

#define BOX_SIZE 1.5f

class CFieldMass : public GameObject {

private:
	CObject3DPolygon m_Mass;
	int m_nColor;

public:

	CFieldMass(int x, int z, int Size);
	~CFieldMass();

//	bool Start();
//	void Update();
	void Draw();
	
	CFieldMass* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		CFieldMass* Child = static_cast<CFieldMass*>(Obj); 
		return Child;
	}
};

#endif