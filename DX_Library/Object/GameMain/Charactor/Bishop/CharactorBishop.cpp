//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorBishop.cpp]
// author : �哴�ˑ�
//
// �T�v : �L�����^�C�v�u�r�V���b�v�v�̏���
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorBishop.h"

CCharactorBishop::CCharactorBishop(int nMass, eUser user, CFieldMassManager* pFieldMassManager) 
	: CCharactorBase(nMass, user, pFieldMassManager) {
	m_Transform.Name = "CharactorBishop";
	
	m_eCharaType = CHARA_BISHOP;
	switch(m_eUser) {

	case USER_PLAYER:
		m_Chara.SetFileName(_T("Chara/Chara_Bishop_Player.x"));
		break;

	case USER_ENEMY:
		m_Chara.SetFileName(_T("Chara/Chara_Bishop_Enemy.x"));
		break;
	}
}

CCharactorBishop::~CCharactorBishop() {
	
}

bool CCharactorBishop::Start() {

	return true;
}

void CCharactorBishop::Update() {

}