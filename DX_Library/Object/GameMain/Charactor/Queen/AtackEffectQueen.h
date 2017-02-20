//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackEffectQueen.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackEffectQueen_H_____
#define _____AtackEffectQueen_H_____

#include <iostream>
#include "../Base/AtackEffectBase.h"

class CAtackEffectQueen : public CAtackEffectBase {

private:

public:

	CAtackEffectQueen();
	~CAtackEffectQueen();

	bool Start();
	void Update();
	void Draw();
	
	CAtackEffectQueen* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackEffectQueen" ) // Ž¸”s!!!
			return nullptr;

		CAtackEffectQueen* Child = static_cast<CAtackEffectQueen*>(Obj); 
		return Child;
	}
};

#endif