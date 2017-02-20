//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorKing.cpp]
// author : 大洞祥太
//
// 概要 : キャラタイプ「キング」の処理
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorKing.h"

CCharactorKing::CCharactorKing(int nMass, eUser user, CFieldMassManager* pFieldMassManager) 
	: CCharactorBase(nMass, user, pFieldMassManager) {
	m_Transform.Name = "CharactorKing";
	
	m_eCharaType = CHARA_KING;
	switch(m_eUser) {

	case USER_PLAYER:
		m_Chara.SetFileName(_T("Chara/Chara_King_Player.x"));
		break;

	case USER_ENEMY:
		m_Chara.SetFileName(_T("Chara/Chara_King_Enemy.x"));
		break;
	}
}

CCharactorKing::~CCharactorKing() {
	
}

bool CCharactorKing::Start() {

	return true;
}

void CCharactorKing::Update() {

}