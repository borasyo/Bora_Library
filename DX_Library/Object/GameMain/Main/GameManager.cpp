//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameManager.cpp]
// author : �哴�ˑ�
//
// �T�v : �Q�[�����C���̐i�s���Ǘ�����
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameManager.h"

CGameManager::CGameManager() {
	m_Transform.Name = "GameManager";
	m_eNowPhase = PHASE_GAMESTART;
}

CGameManager::~CGameManager() {
	
}

bool CGameManager::Start() {

	return true;
}

void CGameManager::Update() {

	// GameMain�������t�F�C�Y�ɍ��킹�Đi�s
	switch(m_eNowPhase) {

	case PHASE_GAMESTART:		//	�Q�[���J�n����

		break;

	case PHASE_PLAYER_SELECT:	//	�v���C���[�̑I������
		
		break;

	case PHASE_ENEMY_AI:		//	AI�����s

		break;

	case PHASE_MOVE_REQUEST:	//	�ړ���v��

		break;

	case PHASE_MOVE_ACTION:		//	�ړ������s

		break;

	case PHASE_ATACK_REQUEST:	//	�U����v��

		break;

	case PHASE_ATACK_ACTION:	//	�U�������s

		break;

	case PHASE_DECISION:		//	���s����

		break;

	case PHASE_RESULT:			//	���U���g���s

		break;
	}
}