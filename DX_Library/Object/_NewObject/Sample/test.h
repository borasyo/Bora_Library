//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [test.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEST_H_____
#define _____TEST_H_____

#include <iostream>
#include "../../Library/Task/TaskManager.h"
#include "../../Library/Task/GameObject.h"
#include "../../Library/ObjectType/Particle2D.h"
#include "../../Library/ObjectType/Particle3D.h"
#include "../../Library/DirectX/DirectInputManager.h"

class test : public GameObject {

private:
	CParticle3D m_particle;
	CDirectInputManager* m_pDirectInputManager;

public:
	test();
	~test();

	bool Start();
	void Update();
	void LateDraw();
	
	test* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		test* Child = static_cast<test*>(Obj); 
		return Child;
	}
};

#endif