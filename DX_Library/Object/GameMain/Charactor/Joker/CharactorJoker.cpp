//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorJoker.cpp]
// author : 大洞祥太
//
// 概要 : キャラタイプ「ジョーカー」の処理
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorJoker.h"

CCharactorJoker::CCharactorJoker(int nMass, eUser user, CFieldMassManager* pFieldMassManager) 
	: CCharactorBase(nMass, user, pFieldMassManager) {
	m_Transform.Name = "CharactorJoker";
	
	m_eCharaType = CHARA_JOKER;
	switch(m_eUser) {

	case USER_PLAYER:
		m_Chara.SetFileName(_T("Chara/Chara_Joker_Player.x"));
		break;

	case USER_ENEMY:
		m_Chara.SetFileName(_T("Chara/Chara_Joker_Enemy.x"));
		break;
	}
}

CCharactorJoker::~CCharactorJoker() {
	
}

bool CCharactorJoker::Start() {

	return true;
}

void CCharactorJoker::Update() {

}