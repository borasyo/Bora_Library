//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CameraBase.h]
// author : 大洞祥太
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
	
	// --- 画ブレ用変数
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

	// 時間、揺れる範囲、揺れるスピード、縦か横か、プラス方向から揺れるか
	void Sway( int nTime, float fSwayRange, bool bBeside, bool bUp = true );
	
	CCameraBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CameraBase" ) // 失敗!!!
			return nullptr;

		CCameraBase* Child = static_cast<CCameraBase*>(Obj); 
		return Child;
	}
};

#endif