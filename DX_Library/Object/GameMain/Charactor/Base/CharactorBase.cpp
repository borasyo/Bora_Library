//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorBase.cpp]
// author : 大洞祥太
//
// 概要 : キャラのベースクラス
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "CharactorBase.h"

#define CHARA_COLLISION_SIZE (D3DXVECTOR3(1.0f, 3.0f, 1.0f))

CCharactorBase::CCharactorBase(int nMass, eUser user, CFieldMassManager* pFieldManager) {
	m_Transform.Name = "CharactorBase";

	m_nNowMass = nMass;
	m_eUser = user;
	m_pFieldMassManager = pFieldManager;

	switch(m_eUser) {

	case USER_PLAYER:
		m_Transform.Rotation.y = Pai/2.0f;
		break;

	case USER_ENEMY:
		m_Transform.Rotation.y = -Pai/2.0f;
		break;
	}

	m_Transform.Position = m_pFieldMassManager->GetMassPos(m_nNowMass);
	SetCollisionCubeSize(CHARA_COLLISION_SIZE);
	m_Chara.SetMatrix(this);
	
#if _DEBUG
	m_Chara.SetColDrawFlg(true);
#endif
}

CCharactorBase::~CCharactorBase() {
	
}

bool CCharactorBase::Start() {

	return true;
}

void CCharactorBase::Update() {

}

void CCharactorBase::Draw() {
	m_Chara.Draw(this);
}

#if _DEBUG
void CCharactorBase::LateDraw() {
	m_Chara.ColDraw(this);
}
#endif

void CCharactorBase::Select(bool bOn) {

	// 選択された瞬間に実行する処理を記述
}

void CCharactorBase::MoveMass(bool bActive) {

	for(auto Ite = m_MoveMassList.begin(); Ite != m_MoveMassList.end(); Ite++) {
		(*Ite)->SetActive(bActive);
	}
}

void CCharactorBase::AtackMass(bool bActive) {
	
	for(auto Ite = m_AtackMassList.begin(); Ite != m_AtackMassList.end(); Ite++) {
		(*Ite)->SetActive(bActive);
	}
}

void CCharactorBase::AtackEffect(bool bActive) {
	
	for(auto Ite = m_AtackEffectList.begin(); Ite != m_AtackEffectList.end(); Ite++) {
		(*Ite)->SetActive(bActive);
	}
}

void CCharactorBase::Move() {

}

void CCharactorBase::Atack() {

}