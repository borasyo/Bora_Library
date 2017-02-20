//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameManager.cpp]
// author : 大洞祥太
//
// 概要 : ゲームメインの進行を管理する
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

	// GameMainを処理フェイズに合わせて進行
	switch(m_eNowPhase) {

	case PHASE_GAMESTART:		//	ゲーム開始処理

		break;

	case PHASE_PLAYER_SELECT:	//	プレイヤーの選択処理
		
		break;

	case PHASE_ENEMY_AI:		//	AIを実行

		break;

	case PHASE_MOVE_REQUEST:	//	移動を要求

		break;

	case PHASE_MOVE_ACTION:		//	移動を実行

		break;

	case PHASE_ATACK_REQUEST:	//	攻撃を要求

		break;

	case PHASE_ATACK_ACTION:	//	攻撃を実行

		break;

	case PHASE_DECISION:		//	勝敗判定

		break;

	case PHASE_RESULT:			//	リザルト実行

		break;
	}
}