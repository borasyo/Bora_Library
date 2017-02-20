//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackEffectBishop.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackEffectBishop_H_____
#define _____AtackEffectBishop_H_____

#include <iostream>
#include "../Base/AtackEffectBase.h"

class CAtackEffectBishop : public CAtackEffectBase {

private:

public:

	CAtackEffectBishop();
	~CAtackEffectBishop();

	bool Start();
	void Update();
	void Draw();
	
	CAtackEffectBishop* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackEffectBishop" ) // Ž¸”s!!!
			return nullptr;

		CAtackEffectBishop* Child = static_cast<CAtackEffectBishop*>(Obj); 
		return Child;
	}
};

#endif