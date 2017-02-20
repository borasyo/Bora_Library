//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CameraBase.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CameraBase_H_____
#define _____CameraBase_H_____

#include <iostream>
#include "../../Library/Task/TaskManager.h"
#include "../../Library/Task/GameObject.h"
#include "../../Library/ObjectType/ObjectCamera.h"

class CCameraBase : public GameObject {

protected:
	CObjectCamera m_Camera;
	
	// --- ��u���p�ϐ�
	bool m_bSway;
	int m_nNowTime;
	int m_nMaxTime;
	float m_fSwayRange;
	float m_fTotalSway;
	bool m_bBeside;
	bool m_bUp;
	float m_fSwayAmount;

public:

	CCameraBase();
	~CCameraBase();

	virtual bool Start();
	virtual void Update();
	virtual void FastDraw();
	
	D3DXMATRIX* GetMatrix(){ return &m_Camera.GetView(); }

	// ���ԁA�h���͈́A�h���X�s�[�h�A�c�������A�v���X��������h��邩
	void Sway( int nTime, float fSwayRange, bool bBeside, bool bUp = true );
	
	CCameraBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CameraBase" ) // ���s!!!
			return nullptr;

		CCameraBase* Child = static_cast<CCameraBase*>(Obj); 
		return Child;
	}
};

#endif