//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MoveMassKing.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MoveMassKing_H_____
#define _____MoveMassKing_H_____

#include <iostream>
#include "../Base/MoveMassBase.h"

class CMoveMassKing : public CMoveMassBase {

private:

public:

	CMoveMassKing();
	~CMoveMassKing();

	bool Start();
	void Update();
	void Draw();
	
	CMoveMassKing* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "MoveMassBase" ) // Ž¸”s!!!
			return nullptr;

		CMoveMassKing* Child = static_cast<CMoveMassKing*>(Obj); 
		return Child;
	}
};

#endif