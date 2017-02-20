//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MoveMassBase.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MoveMassKnight_H_____
#define _____MoveMassKnight_H_____

#include <iostream>
#include "../Base/MoveMassBase.h"

class CMoveMassKnight : public CMoveMassBase {

private:

public:

	CMoveMassKnight();
	~CMoveMassKnight();

	bool Start();
	void Update();
	void Draw();
	
	CMoveMassKnight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "MoveMassBase" ) // Ž¸”s!!!
			return nullptr;

		CMoveMassKnight* Child = static_cast<CMoveMassKnight*>(Obj); 
		return Child;
	}
};

#endif