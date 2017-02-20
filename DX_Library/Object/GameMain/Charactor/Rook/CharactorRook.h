//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorRook.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorRook_H_____
#define _____CharactorRook_H_____

#include <iostream>
#include "../Base/CharactorBase.h"

class CCharactorRook : public CCharactorBase {

private:

public:

	CCharactorRook(int nMass, eUser user, CFieldMassManager* pFieldMassManager);
	~CCharactorRook();

	virtual bool Start();
	virtual void Update();
	
	CCharactorRook* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorRook" ) // ���s!!!
			return nullptr;

		CCharactorRook* Child = static_cast<CCharactorRook*>(Obj); 
		return Child;
	}
};

#endif