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
#include "../../Library/Task/GameObject.h"
#include "../../Library/ObjectType/Object2D.h"
#include "../../Library/Scene/SceneManager.h"

class testObj2D : public GameObject {

private:
	float m_fAlpha;

public:
	// ObjectType
	CObject2D m_Object2D;

	testObj2D(){
		m_Transform.Name = "testObj2D";
		m_Object2D.SetFileName(_T("Fade.png"));
	}
	~testObj2D(){}

	bool Start(){
		m_Transform.Position = D3DXVECTOR3(100.f,100.f,100.f);
		m_Transform.Size     = D3DXVECTOR3(100.f,100.f,100.f);
		m_fAlpha = 1.0f;
		return true;
	}
	
	void Update(){
		
		CDirectInputManager* pI = CDirectInputManager::Instance();

		if(pI->GetKeyboardHold(DIK_A) || pI->GetJoyPress(0, 0)) {
			m_Transform.Position.x -= 1.0f;
		}
		if(pI->GetKeyboardHold(DIK_D) || pI->GetJoyPress(0, 3)) {
			m_Transform.Position.x += 1.0f;
		}

		if(pI->GetKeyboardHold(DIK_W) || pI->GetJoyPress(0, 1)) {
			m_Transform.Position.y -= 1.0f;
		}
		if(pI->GetKeyboardHold(DIK_S) || pI->GetJoyPress(0, 2)) {
			m_Transform.Position.y += 1.0f;
		}

		if(pI->GetKeyboardTrigger(DIK_RETURN) || pI->GetJoyTrigger(0, 9)) {
			SceneManager::Instance()->SetScene(SCENE_GAMEMAIN);
		}

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