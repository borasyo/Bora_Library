//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Field.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Field_H_____
#define _____Field_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"
#include "../../../Library/ObjectType/Object3D_Model.h"

class CField : public GameObject {

private:
	CObject3DModel m_Object;

public:

	CField();
	~CField();

	bool Start();
	void Update();
	void Draw();
	
	CField* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "Field" ) // Ž¸”s!!!
			return nullptr;

		CField* Child = static_cast<CField*>(Obj); 
		return Child;
	}
};

#endif