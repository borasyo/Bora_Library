//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackMassKnight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackMassKnight_H_____
#define _____AtackMassKnight_H_____

#include <iostream>
#include "../Base/AtackMassBase.h"

class CAtackMassKnight : public CAtackMassBase {

private:

public:

	CAtackMassKnight();
	~CAtackMassKnight();

	bool Start();
	void Update();
	void Draw();
	
	CAtackMassKnight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackMassKnight" ) // Ž¸”s!!!
			return nullptr;

		CAtackMassKnight* Child = static_cast<CAtackMassKnight*>(Obj); 
		return Child;
	}
};

#endif