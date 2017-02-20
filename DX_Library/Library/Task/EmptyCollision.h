//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [EmptyCollision.h]
// author : �哴�ˑ�
//
// ��̃I�u�W�F�N�g�B
// �����̃I�u�W�F�N�g���܂Ƃ߂�e���~�������ɐ�������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____EmptyCollision_H_____
#define _____EmptyCollision_H_____

#include <iostream>
#include "GameObject.h"
#include "../ObjectType/Object3D_Model.h"

class EmptyCollision : public GameObject {

private:
	CObject3DModel m_ColObj;

public:
	EmptyCollision(std::string Name, D3DXVECTOR3 CubeSize, float fCircleSize);
	~EmptyCollision();

	bool Start();
	void LateDraw();
	
	EmptyCollision* GetDownCastClass(GameObject* Obj){
		return nullptr; // ��̃I�u�W�F�N�g�Ȃ̂Ń_�E���L���X�g�����Ȃ�
	}
};

#endif