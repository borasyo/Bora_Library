//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorRook.cpp]
// author : 大洞祥太
//
// 概要 : キャラタイプ「ルーク」の処理
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorRook.h"

CCharactorRook::CCharactorRook(int nMass, eUser user, CFieldMassManager* pFieldMassManager) 
	: CCharactorBase(nMass, user, pFieldMassManager) {
	m_Transform.Name = "CharactorRook";

	m_eCharaType = CHARA_ROOK;
	switch(m_eUser) {

	case USER_PLAYER:
		m_Chara.SetFileName(_T("Chara/Chara_Rook_Player.x"));
		break;

	case USER_ENEMY:
		m_Chara.SetFileName(_T("Chara/Chara_Rook_Enemy.x"));
		break;
	}
}

CCharactorRook::~CCharactorRook() {
	
}

bool CCharactorRook::Start() {

	return true;
}

void CCharactorRook::Update() {

}