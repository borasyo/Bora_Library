//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackMassJoker.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackMassJoker_H_____
#define _____AtackMassJoker_H_____

#include <iostream>
#include "../Base/AtackMassBase.h"

class CAtackMassJoker : public CAtackMassBase {

private:

public:

	CAtackMassJoker();
	~CAtackMassJoker();

	bool Start();
	void Update();
	void Draw();
	
	CAtackMassJoker* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackMassJoker" ) // Ž¸”s!!!
			return nullptr;

		CAtackMassJoker* Child = static_cast<CAtackMassJoker*>(Obj); 
		return Child;
	}
};

#endif