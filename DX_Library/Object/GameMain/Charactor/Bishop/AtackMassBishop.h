//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackMassBishop.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackMassBishop_H_____
#define _____AtackMassBishop_H_____

#include <iostream>
#include "../Base/AtackMassBase.h"

class CAtackMassBishop : public CAtackMassBase {

private:

public:

	CAtackMassBishop();
	~CAtackMassBishop();

	bool Start();
	void Update();
	void Draw();
	
	CAtackMassBishop* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackMassBishop" ) // Ž¸”s!!!
			return nullptr;

		CAtackMassBishop* Child = static_cast<CAtackMassBishop*>(Obj); 
		return Child;
	}
};

#endif