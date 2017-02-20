//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorKnight.cpp]
// author : 大洞祥太
//
// 概要 : キャラタイプ「ナイト」の処理
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorKnight.h"

CCharactorKnight::CCharactorKnight(int nMass, eUser user, CFieldMassManager* pFieldMassManager) 
	: CCharactorBase(nMass, user, pFieldMassManager) {
	m_Transform.Name = "CharactorKnight";
	
	m_eCharaType = CHARA_KNIGHT;
	switch(m_eUser) {

	case USER_PLAYER:
		m_Chara.SetFileName(_T("Chara/Chara_Knight_Player.x"));
		break;

	case USER_ENEMY:
		m_Chara.SetFileName(_T("Chara/Chara_Knight_Enemy.x"));
		break;
	}
}

CCharactorKnight::~CCharactorKnight() {
	
}

bool CCharactorKnight::Start() {

	return true;
}

void CCharactorKnight::Update() {

}