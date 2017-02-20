//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [AtackEffectBase.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____AtackEffectBase_H_____
#define _____AtackEffectBase_H_____

#include <iostream>
#include "../../../../Library/Task/TaskManager.h"
#include "../../../../Library/Task/GameObject.h"
#include "../../../../Library/ObjectType/Particle3D.h"

class CAtackEffectBase : public GameObject {

protected:
	CParticle3D m_Effect;

public:

	CAtackEffectBase();
	~CAtackEffectBase();

	bool Start();
	void Update();
	void Draw();
	
	CAtackEffectBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "AtackEffectBase" ) // Ž¸”s!!!
			return nullptr;

		CAtackEffectBase* Child = static_cast<CAtackEffectBase*>(Obj); 
		return Child;
	}
};

#endif