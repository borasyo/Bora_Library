//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testObj2D.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____testObj_2D_H_____
#define _____testObj_2D_H_____

#include <iostream>
#include <tchar.h>
#include "../Library/Task/GameObject.h"
#include "../Library/ObjectType/Object2D.h"

class testObj2D : public GameObject {

private:
	float m_fAlpha;

public:
	// ObjectType
	CObject2D m_Object2D;

	testObj2D(){
		m_Transform.Name = "testObj2D";
		m_Object2D.SetFileName(_T("BlueBall.png"));
	}
	~testObj2D(){}

	bool Start(){
		m_Transform.Position = D3DXVECTOR3(100.f,100.f,100.f);
		m_Transform.Size     = D3DXVECTOR3(100.f,100.f,100.f);
		m_fAlpha = 1.0f;
		return true;
	}
	
	void Update(){
		m_Object2D.SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,m_fAlpha) );
		m_fAlpha -= 0.001f;
	}

	void Draw(){

		m_Object2D.Draw( this );
	}

	testObj2D* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		testObj2D* Child = static_cast<testObj2D*>(Obj); 
		return Child;
	}
};

#endif