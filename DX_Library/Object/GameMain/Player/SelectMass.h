//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SelectMass.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SelectMass_H_____
#define _____SelectMass_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"
#include "../../../Library/ObjectType/Object3D_Polygon.h"
#include "../Field/FieldMassManager.h"
#include "../Charactor/Manager/CharactorManager.h"
#include "../../../Library/ObjectType/Collision3D.h"

enum eMoveVec {
	
	MOVE_RIGHT = 0,
	MOVE_LEFT,
	MOVE_UP,
	MOVE_DOWN,

	MOVE_MAX
};

class CSelectMass : public GameObject {

private:
	CObject3DPolygon m_Obj;
	Collision3D m_Collsion;	// キャラとのコリジョンをここで行いたいため

	//	マス制御関連
	int m_nNowMass;
	int m_nMassRange;
	int m_nMassMax;
	D3DXVECTOR3* m_MassPos;

	//	キャラ選択関連
	CCharactorBase* m_pNowSelectChara;
	
	//	マネージャー関係
	CCharactorManager* m_pCharactorManager;
	CFieldMassManager* m_pFieldMassManager;

	//	入力制御
	float m_fNowTime;
	bool m_bSelect;	//	何か選択したらTrueに、キャンセルor選択できなかったらFalse
//	static bool m_bSelect;	//	何か選択したらTrueに、キャンセルor選択できなかったらFalse

	// private関数
	void MoveSelect(eMoveVec moveVec);
	bool CheckCharaSelect();

public:
	CSelectMass(CCharactorManager* pCharactorManager, CFieldMassManager* pFieldMassManager);
	~CSelectMass();

//	bool Start();
	void Update();
	void Draw();
	
//	bool Select() { return m_bSelect; }
//	static bool Select() { return m_bSelect; }
	
	CSelectMass* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "SelectMass" ) // 失敗!!!
			return nullptr;

		CSelectMass* Child = static_cast<CSelectMass*>(Obj); 
		return Child;
	}
};

#endif