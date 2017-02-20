//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorBishop.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorBishop_H_____
#define _____CharactorBishop_H_____

#include <iostream>
#include "../Base/CharactorBase.h"

class CCharactorBishop : public CCharactorBase {

private:

public:

	CCharactorBishop(int nMass, eUser user, CFieldMassManager* pFieldMassManager);
	~CCharactorBishop();

	virtual bool Start();
	virtual void Update();
	
	CCharactorBishop* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorBishop" ) // Ž¸”s!!!
			return nullptr;

		CCharactorBishop* Child = static_cast<CCharactorBishop*>(Obj); 
		return Child;
	}
};

#endif