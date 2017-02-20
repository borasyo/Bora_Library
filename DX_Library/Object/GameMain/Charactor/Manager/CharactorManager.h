//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorManager.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorManager_H_____
#define _____CharactorManager_H_____

#include <iostream>
#include "../../../../Library/Task/TaskManager.h"
#include "../../../../Library/Task/GameObject.h"
#include "../Base/CharactorBase.h"
#include "../../Field/FieldMassManager.h"

class CCharactorManager : public GameObject {

private:
	std::list<CCharactorBase*> m_PlayerList;
	std::list<CCharactorBase*> m_EnemyList;

	CFieldMassManager* m_pFieldMassManager;

public:

	CCharactorManager(CFieldMassManager* pFieldMassManager);
	~CCharactorManager();

//	bool Start();
//	void Update();
	
	// �v���C���[�A�G�l�~�[�̃L�����f�[�^�擾
	std::list<CCharactorBase*> GetPlayerChara() { return m_PlayerList; }
	std::list<CCharactorBase*> GetEnemyChara()  { return m_EnemyList; }
	
	CCharactorManager* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorManager" ) // ���s!!!
			return nullptr;

		CCharactorManager* Child = static_cast<CCharactorManager*>(Obj); 
		return Child;
	}
};

#endif