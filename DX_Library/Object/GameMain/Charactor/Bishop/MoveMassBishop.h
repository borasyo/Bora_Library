//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MoveMassBishop.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MoveMassBishop_H_____
#define _____MoveMassBishop_H_____

#include <iostream>
#include "../Base/MoveMassBase.h"

class CMoveMassBishop : public CMoveMassBase {

private:

public:

	CMoveMassBishop();
	~CMoveMassBishop();

	bool Start();
	void Update();
	void Draw();
	
	CMoveMassBishop* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "MoveMassBase" ) // Ž¸”s!!!
			return nullptr;

		CMoveMassBishop* Child = static_cast<CMoveMassBishop*>(Obj); 
		return Child;
	}
};

#endif