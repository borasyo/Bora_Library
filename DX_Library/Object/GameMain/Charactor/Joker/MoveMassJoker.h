//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MoveMassJoker.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MoveMassJoker_H_____
#define _____MoveMassJoker_H_____

#include <iostream>
#include "../Base/MoveMassBase.h"

class CMoveMassJoker : public CMoveMassBase {

private:

public:

	CMoveMassJoker();
	~CMoveMassJoker();

	bool Start();
	void Update();
	void Draw();
	
	CMoveMassJoker* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "MoveMassBase" ) // ���s!!!
			return nullptr;

		CMoveMassJoker* Child = static_cast<CMoveMassJoker*>(Obj); 
		return Child;
	}
};

#endif