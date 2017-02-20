//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackEffectKnight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackEffectKnight_H_____
#define _____AtackEffectKnight_H_____

#include <iostream>
#include "../Base/AtackEffectBase.h"

class CAtackEffectKnight : public CAtackEffectBase {

private:

public:

	CAtackEffectKnight();
	~CAtackEffectKnight();

	bool Start();
	void Update();
	void Draw();
	
	CAtackEffectKnight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackEffectKnight" ) // Ž¸”s!!!
			return nullptr;

		CAtackEffectKnight* Child = static_cast<CAtackEffectKnight*>(Obj); 
		return Child;
	}
};

#endif