//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MoveMassRook.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MoveMassRook_H_____
#define _____MoveMassRook_H_____

#include <iostream>
#include "../Base/MoveMassBase.h"

class CMoveMassRook : public CMoveMassBase {

private:

public:

	CMoveMassRook();
	~CMoveMassRook();

	bool Start();
	void Update();
	void Draw();
	
	CMoveMassRook* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "MoveMassBase" ) // Ž¸”s!!!
			return nullptr;

		CMoveMassRook* Child = static_cast<CMoveMassRook*>(Obj); 
		return Child;
	}
};

#endif