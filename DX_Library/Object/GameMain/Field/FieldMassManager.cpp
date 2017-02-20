//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldMassManager.cpp]
// author : 大洞祥太
//
// 概要 : 全てのマスの情報を保持する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FieldMassManager.h"
#include "../../../Library/Task/ObjectFactory.h"
#include "../Player/SelectMass.h"

CFieldMassManager::CFieldMassManager(int nStageSize) {
	m_Transform.Name = "FieldMassManager";
	
	SetStageInfo(nStageSize);				// ステージマス生成
}

CFieldMassManager::~CFieldMassManager() {

}

/*bool CFieldMassManager::Start(){
	
	return true;
}*/

/*void CFieldMassManager::Update() {

}*/

/*void CFieldMassManager::Draw() {

}*/

void CFieldMassManager::SetStageInfo(int nStageSize) {
	
	// 地面一括管理用Empty
	TaskManager* pTask = TaskManager::Instance();

	CFieldMass* OnePeace = nullptr;
	for (int i = 0; i < nStageSize * nStageSize; i++)
	{
		OnePeace = CreateObject(new CFieldMass(i % nStageSize, i / nStageSize, nStageSize));
		OnePeace->SetParent(this);
		OnePeace->Start();
		m_Mass.push_back(OnePeace);
	}
}