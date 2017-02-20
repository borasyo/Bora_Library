//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackMassKing.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackMassKing_H_____
#define _____AtackMassKing_H_____

#include <iostream>
#include "../Base/AtackMassBase.h"

class CAtackMassKing : public CAtackMassBase {

private:

public:

	CAtackMassKing();
	~CAtackMassKing();

	bool Start();
	void Update();
	void Draw();
	
	CAtackMassKing* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackMassKing" ) // Ž¸”s!!!
			return nullptr;

		CAtackMassKing* Child = static_cast<CAtackMassKing*>(Obj); 
		return Child;
	}
};

#endif