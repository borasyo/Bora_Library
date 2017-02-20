//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldMassManager.h]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____FieldMassManager_H_____
#define _____FieldMassManager_H_____

#include <iostream>
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/Task/GameObject.h"

#include "FieldMass.h"

class CFieldMassManager : public GameObject {

private:
	std::vector<CFieldMass*> m_Mass;

public:
	CFieldMassManager(int nStageSize);
	~CFieldMassManager();

//	bool Start();
//	void Update();
//	void Draw();
	
	void SetStageInfo(int nStageSize);
	std::vector<CFieldMass*> GetMassList() { return m_Mass; }
	D3DXVECTOR3 GetMassPos(int nMass) { return *(m_Mass[nMass])->GetPosition(); }
	
	CFieldMassManager* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != this->GetName() ) // Ž¸”s!!!
			return nullptr;

		CFieldMassManager* Child = static_cast<CFieldMassManager*>(Obj); 
		return Child;
	}
};

#endif