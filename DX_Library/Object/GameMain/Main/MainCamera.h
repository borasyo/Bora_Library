//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainCamera.h]
// author : ‘å“´Ë‘¾
//
// ŠT—v : 
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MainCamera_H_____
#define _____MainCamera_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"
#include "../../../Library/ObjectType/CameraBase.h"
#include "../../../Library/DirectX/DirectInputManager.h"

class CMainCamera : public CCameraBase {

private:
	
#ifdef DEBUG
	CDirectInputManager* m_pDirectInputManager;
#endif

public:

	CMainCamera();
	~CMainCamera();

	bool Start();
	void Update();
	
	CMainCamera* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		CMainCamera* Child = static_cast<CMainCamera*>(Obj); 
		return Child;
	}
};

#endif