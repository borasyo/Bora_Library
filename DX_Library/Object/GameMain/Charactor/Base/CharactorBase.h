//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorBase.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorBase_H_____
#define _____CharactorBase_H_____

#include <iostream>
#include "../../../../Library/Task/TaskManager.h"
#include "../../../../Library/Task/GameObject.h"
#include "../../../../Library/ObjectType/Object3D_Model.h"

#include "MoveMassBase.h"
#include "AtackMassBase.h"
#include "AtackEffectBase.h"
#include "../../Field/FieldMassManager.h"

enum eCharaType {
	CHARA_ROOK = 0,
	CHARA_BISHOP,
	CHARA_KNIGHT,
	CHARA_QUEEN,
	CHARA_KING,
	CHARA_JOKER,

	CHARA_MAX,
};

enum eUser {
	USER_PLAYER = 0,
	USER_ENEMY,

	USER_MAX,
};

class CCharactorBase : public GameObject {

protected:

	CObject3DModel	m_Chara;
	eCharaType		m_eCharaType;
	eUser			m_eUser;
	int				m_nNowMass;

	CFieldMassManager* m_pFieldMassManager;	//	�S�}�X���ێ�
	
	//	�ړ��֌W�̕ϐ�
	int m_nNext;	//	�ړ���̃}�X
	tBez m_Bez;		//	�ړ��v�Z

	std::list<CMoveMassBase*> m_MoveMassList;		//	�ړ��\�G���A��\������
	std::list<CAtackMassBase*> m_AtackMassList;		//	�U������G���A��\������
	std::list<CAtackEffectBase*> m_AtackEffectList;	//	�U���G�t�F�N�g��\������

public:

	CCharactorBase(int nMass, eUser user, CFieldMassManager* pFieldManager);
	~CCharactorBase();

	virtual bool Start();
	virtual void Update();
	void Draw();
#if _DEBUG
	void LateDraw();
#endif
	
	void Select(bool bOn);	//	�v���C���[���I���A�L�����Z���������̏���

	void MoveMass(bool bActive);	//	�ړ��\�G���AON�EOFF
	void AtackMass(bool bActive);	//	�U���\�G���AON�EOFF
	void AtackEffect(bool bActive);	//	�U���G�t�F�N�gON�EOFF

	virtual void Move();	//	�ړ�����
	virtual void Atack();	//	�U������

	//	�L�����^�C�v�̃Q�b�g
	eCharaType GetCharaType() { return m_eCharaType; }

	//	���[�U�[�̃Q�b�g
	eUser GetUser() { return m_eUser; }

	//	Mass�̃Q�b�g�Z�b�g
	void SetMass(int nMass) { m_nNowMass = nMass; }
	int GetMass() { return m_nNowMass; }

	//	Next�̃Q�b�g�Z�b�g
	void SetNext(int nNext) { m_nNext = nNext; }
	int GetNext() { return m_nNext; }
	
	CCharactorBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorBase" ) // ���s!!!
			return nullptr;

		CCharactorBase* Child = static_cast<CCharactorBase*>(Obj); 
		return Child;
	}
};

#endif