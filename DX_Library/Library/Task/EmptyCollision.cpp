//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [EmptyCollision.cpp]
// author : �哴�ˑ�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "EmptyCollision.h"

EmptyCollision::EmptyCollision( std::string Name, D3DXVECTOR3 CubeSize, float fCircleSize ){
	m_Transform.Name = Name;
	
	if(CubeSize != D3DXVECTOR3_ZERO)
		SetCollisionCubeSize(CubeSize);

	if(fCircleSize != 0.0f)
		SetCollisionCircleSize(fCircleSize);
}

// �S�Ă̎q�I�u�W�F�N�g���폜
EmptyCollision::~EmptyCollision(){
	
}

bool EmptyCollision::Start() {
	m_ColObj.SetMatrix(m_Transform.Position, m_Transform.Size, m_Transform.Rotation);
	return true;
}

void EmptyCollision::LateDraw() {
	m_ColObj.ColDraw(this, D3DXCOLOR(1,1,0,0.25f));
}