//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainLight.h]
// author : ‘å“´Ë‘¾
//
// ŠT—v :
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MAINLIGHT_H_____
#define _____MAINLIGHT_H_____

#include <iostream>
#include "../../Library/Task/GameObject.h"
#include "../../Library/ObjectType/ObjectDirectionLight.h"

class CMainLight : public GameObject {

private:

public:
	// ObjectType
	CObjectDirectionLight m_ObjectLight;

	CMainLight(){
		m_Transform.Name = "MainLight";
	}
	~CMainLight(){}

	bool Start(){
		m_ObjectLight.SetVecDirection( D3DXVECTOR3(0,-1,1) );
		SetCollisionFlg(false);
		return true;
	}

	CMainLight* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		CMainLight* Child = static_cast<CMainLight*>(Obj); 
		return Child;
	}
};

#endif