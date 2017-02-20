//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameManager.h]
// author : 大洞祥太
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
	PHASE_GAMESTART = 0,	//	ゲーム開始フェイズ

	PHASE_PLAYER_SELECT,	//	プレイヤーの移動選択
	PHASE_ENEMY_AI,			//	敵のAI処理

	PHASE_MOVE_REQUEST,		//	キャラの移動を要求
	//	無ければPHASE_PLAYER_SELECTへ
	PHASE_MOVE_ACTION,		//	キャラの移動を実行

	PHASE_ATACK_REQUEST,	//	キャラの攻撃を要求
	//	無ければPHASE_MOVE_REQUESTへ
	PHASE_ATACK_ACTION,		//	キャラの攻撃を実行
	PHASE_DECISION,			//	勝敗判定
	//	決まらなかったらPHASE_MOVE_REQUESTへ

	PHASE_RESULT,			//	リザルト実行

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
		if( Obj->GetName() != "GameManager" ) // 失敗!!!
			return nullptr;

		CGameManager* Child = static_cast<CGameManager*>(Obj); 
		return Child;
	}
};

#endif