//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorManager.h]
// author : 大洞祥太
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
	
	// プレイヤー、エネミーのキャラデータ取得
	std::list<CCharactorBase*> GetPlayerChara() { return m_PlayerList; }
	std::list<CCharactorBase*> GetEnemyChara()  { return m_EnemyList; }
	
	CCharactorManager* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorManager" ) // 失敗!!!
			return nullptr;

		CCharactorManager* Child = static_cast<CCharactorManager*>(Obj); 
		return Child;
	}
};

#endif