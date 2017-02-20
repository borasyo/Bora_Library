//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SelectMass.h]
// author : �哴�ˑ�
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
	Collision3D m_Collsion;	// �L�����Ƃ̃R���W�����������ōs����������

	//	�}�X����֘A
	int m_nNowMass;
	int m_nMassRange;
	int m_nMassMax;
	D3DXVECTOR3* m_MassPos;

	//	�L�����I���֘A
	CCharactorBase* m_pNowSelectChara;
	
	//	�}�l�[�W���[�֌W
	CCharactorManager* m_pCharactorManager;
	CFieldMassManager* m_pFieldMassManager;

	//	���͐���
	float m_fNowTime;
	bool m_bSelect;	//	�����I��������True�ɁA�L�����Z��or�I���ł��Ȃ�������False
//	static bool m_bSelect;	//	�����I��������True�ɁA�L�����Z��or�I���ł��Ȃ�������False

	// private�֐�
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
		if( Obj->GetName() != "SelectMass" ) // ���s!!!
			return nullptr;

		CSelectMass* Child = static_cast<CSelectMass*>(Obj); 
		return Child;
	}
};

#endif