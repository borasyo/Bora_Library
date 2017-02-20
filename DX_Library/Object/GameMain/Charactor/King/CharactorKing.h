//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorKing.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorKing_H_____
#define _____CharactorKing_H_____

#include <iostream>
#include "../Base/CharactorBase.h"

class CCharactorKing : public CCharactorBase {

private:

public:

	CCharactorKing(int nMass, eUser user, CFieldMassManager* pFieldMassManager);
	~CCharactorKing();

	virtual bool Start();
	virtual void Update();
	
	CCharactorKing* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorKing" ) // Ž¸”s!!!
			return nullptr;

		CCharactorKing* Child = static_cast<CCharactorKing*>(Obj); 
		return Child;
	}
};

#endif