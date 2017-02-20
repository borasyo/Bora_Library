//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackEffectJoker.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackEffectJoker_H_____
#define _____AtackEffectJoker_H_____

#include <iostream>
#include "../Base/AtackEffectBase.h"

class CAtackEffectJoker : public CAtackEffectBase {

private:

public:

	CAtackEffectJoker();
	~CAtackEffectJoker();

	bool Start();
	void Update();
	void Draw();
	
	CAtackEffectJoker* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackEffectJoker" ) // Ž¸”s!!!
			return nullptr;

		CAtackEffectJoker* Child = static_cast<CAtackEffectJoker*>(Obj); 
		return Child;
	}
};

#endif