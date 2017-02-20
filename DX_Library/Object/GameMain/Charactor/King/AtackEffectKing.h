//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackEffectKing.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackEffectKing_H_____
#define _____AtackEffectKing_H_____

#include <iostream>
#include "../Base/AtackEffectBase.h"

class CAtackEffectKing : public CAtackEffectBase {

private:

public:

	CAtackEffectKing();
	~CAtackEffectKing();

	bool Start();
	void Update();
	void Draw();
	
	CAtackEffectKing* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackEffectKing" ) // Ž¸”s!!!
			return nullptr;

		CAtackEffectKing* Child = static_cast<CAtackEffectKing*>(Obj); 
		return Child;
	}
};

#endif