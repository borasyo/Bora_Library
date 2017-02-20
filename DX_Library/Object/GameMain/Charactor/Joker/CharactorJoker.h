//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorJoker.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorJoker_H_____
#define _____CharactorJoker_H_____

#include <iostream>
#include "../Base/CharactorBase.h"

class CCharactorJoker : public CCharactorBase {

private:

public:

	CCharactorJoker(int nMass, eUser user, CFieldMassManager* pFieldMassManager);
	~CCharactorJoker();

	virtual bool Start();
	virtual void Update();
	
	CCharactorJoker* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorJoker" ) // Ž¸”s!!!
			return nullptr;

		CCharactorJoker* Child = static_cast<CCharactorJoker*>(Obj); 
		return Child;
	}
};

#endif