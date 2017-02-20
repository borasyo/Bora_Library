//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorQueen.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorQueen_H_____
#define _____CharactorQueen_H_____

#include <iostream>
#include "../Base/CharactorBase.h"

class CCharactorQueen : public CCharactorBase {

private:

public:

	CCharactorQueen(int nMass, eUser user, CFieldMassManager* pFieldMassManager);
	~CCharactorQueen();

	virtual bool Start();
	virtual void Update();
	
	CCharactorQueen* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorQueen" ) // Ž¸”s!!!
			return nullptr;

		CCharactorQueen* Child = static_cast<CCharactorQueen*>(Obj); 
		return Child;
	}
};

#endif