//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Sky.h]
// author : 大洞祥太
//
// 概要 : スカイドーム表示
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____Sky_H_____
#define _____Sky_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"
#include "../../../Library/ObjectType/Object3D_Model.h"

class CSky : public GameObject {

private:
	GameObject* pCamera;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

public:
	// ObjectType
	CObject3DModel m_Object3D;

	CSky();
	~CSky();

	bool Start();
	void Update();
	void FastDraw();
	
	CSky* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // 失敗!!!
			return nullptr;

		CSky* Child = static_cast<CSky*>(Obj); 
		return Child;
	}
};

#endif