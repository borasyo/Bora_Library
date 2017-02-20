//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldMassManager.cpp]
// author : �哴�ˑ�
//
// �T�v : �S�Ẵ}�X�̏���ێ�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FieldMassManager.h"
#include "../../../Library/Task/ObjectFactory.h"
#include "../Player/SelectMass.h"

CFieldMassManager::CFieldMassManager(int nStageSize) {
	m_Transform.Name = "FieldMassManager";
	
	SetStageInfo(nStageSize);				// �X�e�[�W�}�X����
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
	
	// �n�ʈꊇ�Ǘ��pEmpty
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