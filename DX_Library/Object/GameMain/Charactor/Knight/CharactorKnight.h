//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorKnight.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorKnight_H_____
#define _____CharactorKnight_H_____

#include <iostream>
#include "../Base/CharactorBase.h"

class CCharactorKnight : public CCharactorBase {

private:

public:

	CCharactorKnight(int nMass, eUser user, CFieldMassManager* pFieldMassManager);
	~CCharactorKnight();

	virtual bool Start();
	virtual void Update();
	
	CCharactorKnight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorKnight" ) // Ž¸”s!!!
			return nullptr;

		CCharactorKnight* Child = static_cast<CCharactorKnight*>(Obj); 
		return Child;
	}
};

#endif