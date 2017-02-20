//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [copy.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____COPY_H_____
#define _____COPY_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"
#include "../../../Library/ObjectType/.h"

class Ccopy : public GameObject {

private:
	ObjectType

public:

	Ccopy();
	~Ccopy();

	bool Start();
	void Update();
	void Draw();
	
	Ccopy* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "copy" ) // Ž¸”s!!!
			return nullptr;

		Ccopy* Child = static_cast<Ccopy*>(Obj); 
		return Child;
	}
};

#endif