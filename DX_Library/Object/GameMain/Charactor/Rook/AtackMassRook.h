//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackMassRook.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackMassRook_H_____
#define _____AtackMassRook_H_____

#include <iostream>
#include "../Base/AtackMassBase.h"

class CAtackMassRook : public CAtackMassBase {

private:

public:

	CAtackMassRook();
	~CAtackMassRook();

	bool Start();
	void Update();
	void Draw();
	
	CAtackMassRook* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackMassRook" ) // ���s!!!
			return nullptr;

		CAtackMassRook* Child = static_cast<CAtackMassRook*>(Obj); 
		return Child;
	}
};

#endif