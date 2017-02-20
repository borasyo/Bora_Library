//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MoveMassQueen.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MoveMassQueen_H_____
#define _____MoveMassQueen_H_____

#include <iostream>
#include "../Base/MoveMassBase.h"

class CMoveMassQueen : public CMoveMassBase {

private:

public:

	CMoveMassQueen();
	~CMoveMassQueen();

	bool Start();
	void Update();
	void Draw();
	
	CMoveMassQueen* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "MoveMassBase" ) // Ž¸”s!!!
			return nullptr;

		CMoveMassQueen* Child = static_cast<CMoveMassQueen*>(Obj); 
		return Child;
	}
};

#endif