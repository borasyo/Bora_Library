//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameManager.h]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GameManager_H_____
#define _____GameManager_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"

enum ePhase {
	PHASE_GAMESTART = 0,	//	�Q�[���J�n�t�F�C�Y

	PHASE_PLAYER_SELECT,	//	�v���C���[�̈ړ��I��
	PHASE_ENEMY_AI,			//	�G��AI����

	PHASE_MOVE_REQUEST,		//	�L�����̈ړ���v��
	//	�������PHASE_PLAYER_SELECT��
	PHASE_MOVE_ACTION,		//	�L�����̈ړ������s

	PHASE_ATACK_REQUEST,	//	�L�����̍U����v��
	//	�������PHASE_MOVE_REQUEST��
	PHASE_ATACK_ACTION,		//	�L�����̍U�������s
	PHASE_DECISION,			//	���s����
	//	���܂�Ȃ�������PHASE_MOVE_REQUEST��

	PHASE_RESULT,			//	���U���g���s

	PHASE_MAX,
};

class CGameManager : public GameObject {

private:
	ePhase m_eNowPhase;

public:

	CGameManager();
	~CGameManager();

	bool Start();
	void Update();
	
	CGameManager* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "GameManager" ) // ���s!!!
			return nullptr;

		CGameManager* Child = static_cast<CGameManager*>(Obj); 
		return Child;
	}
};

#endif