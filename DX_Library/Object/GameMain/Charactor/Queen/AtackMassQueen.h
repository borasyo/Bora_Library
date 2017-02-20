//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackMassQueen.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackMassQueen_H_____
#define _____AtackMassQueen_H_____

#include <iostream>
#include "../Base/AtackMassBase.h"

class CAtackMassQueen : public CAtackMassBase {

private:

public:

	CAtackMassQueen();
	~CAtackMassQueen();

	bool Start();
	void Update();
	void Draw();
	
	CAtackMassQueen* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackMassQueen" ) // Ž¸”s!!!
			return nullptr;

		CAtackMassQueen* Child = static_cast<CAtackMassQueen*>(Obj); 
		return Child;
	}
};

#endif