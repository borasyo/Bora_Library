//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorManager.cpp]
// author : �哴�ˑ�
//
// �T�v : �L�����̃��X�g��ێ�����}�l�[�W���N���X
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorManager.h"
#include "../../../../Library/Task/ObjectFactory.h"

#include "../Bishop/CharactorBishop.h"
#include "../Rook/CharactorRook.h"
#include "../Joker/CharactorJoker.h"
#include "../Knight/CharactorKnight.h"
#include "../King/CharactorKing.h"
#include "../Queen/CharactorQueen.h"

CCharactorManager::CCharactorManager(CFieldMassManager* pFieldMassManager) {
	m_Transform.Name = "CharactorManager";

	m_pFieldMassManager = pFieldMassManager;
	
	// �K���ɃL��������
	CCharactorBase* pTemp = nullptr;

	int nSize = (int)sqrtf(pFieldMassManager->GetMassList().size());
	for(int i = 0; i < nSize * 2; i++) {

		int nCharaType = rand()%CHARA_MAX;
		int nUser = (i % 2) ^ 1;
		int nMass = ((i / 2) * nSize) + ((i % 2) * (nSize - 1));

		// �����_���ɑI�������^�C�v�̃L�����𐶐�
		switch((eCharaType)nCharaType) {

		case CHARA_BISHOP:
			pTemp = CreateObject(new CCharactorBishop(nMass, (eUser)nUser, m_pFieldMassManager));
			break;

		case CHARA_JOKER:
			pTemp = CreateObject(new CCharactorJoker(nMass, (eUser)nUser, m_pFieldMassManager));
			break;

		case CHARA_KING:
			pTemp = CreateObject(new CCharactorKing(nMass, (eUser)nUser, m_pFieldMassManager));
			break;

		case CHARA_KNIGHT:
			pTemp = CreateObject(new CCharactorKnight(nMass, (eUser)nUser, m_pFieldMassManager));
			break;

		case CHARA_QUEEN:
			pTemp = CreateObject(new CCharactorQueen(nMass, (eUser)nUser, m_pFieldMassManager));
			break;

		case CHARA_ROOK:
			pTemp = CreateObject(new CCharactorRook(nMass, (eUser)nUser, m_pFieldMassManager));
			break;

		default:
			break;
		}

		//	�v���C���[�ƃG�l�~�[�̃��X�g�Ɋi�[
		switch((eUser)nUser) {
		
		case USER_PLAYER:
			m_PlayerList.push_back(pTemp);
			break;

		case USER_ENEMY:
			m_EnemyList.push_back(pTemp);
			break;

		default:
			break;
		}
	}
}

CCharactorManager::~CCharactorManager() {
	
}

/*bool CCharactorManager::Start() {

	return true;
}

void CCharactorManager::Update() {

}*/