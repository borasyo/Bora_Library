//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackEffectRook.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackEffectRook_H_____
#define _____AtackEffectRook_H_____

#include <iostream>
#include "../Base/AtackEffectBase.h"

class CAtackEffectRook : public CAtackEffectBase {

private:

public:

	CAtackEffectRook();
	~CAtackEffectRook();

	bool Start();
	void Update();
	void Draw();
	
	CAtackEffectRook* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackEffectRook" ) // ���s!!!
			return nullptr;

		CAtackEffectRook* Child = static_cast<CAtackEffectRook*>(Obj); 
		return Child;
	}
};

#endif