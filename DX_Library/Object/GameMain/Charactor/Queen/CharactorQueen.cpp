//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorQueen.cpp]
// author : 大洞祥太
//
// 概要 : キャラタイプ「クイーン」の処理
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorQueen.h"

CCharactorQueen::CCharactorQueen(int nMass, eUser user, CFieldMassManager* pFieldMassManager) 
	: CCharactorBase(nMass, user, pFieldMassManager) {
	m_Transform.Name = "CharactorQueen";
	
	m_eCharaType = CHARA_QUEEN;
	switch(m_eUser) {

	case USER_PLAYER:
		m_Chara.SetFileName(_T("Chara/Chara_Queen_Player.x"));
		break;

	case USER_ENEMY:
		m_Chara.SetFileName(_T("Chara/Chara_Queen_Enemy.x"));
		break;
	}
}

CCharactorQueen::~CCharactorQueen() {
	
}

bool CCharactorQueen::Start() {

	return true;
}

void CCharactorQueen::Update() {

}