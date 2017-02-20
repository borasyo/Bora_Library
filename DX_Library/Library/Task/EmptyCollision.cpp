//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [EmptyCollision.cpp]
// author : 大洞祥太
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

// 全ての子オブジェクトを削除
EmptyCollision::~EmptyCollision(){
	
}

bool EmptyCollision::Start() {
	m_ColObj.SetMatrix(m_Transform.Position, m_Transform.Size, m_Transform.Rotation);
	return true;
}

void EmptyCollision::LateDraw() {
	m_ColObj.ColDraw(this, D3DXCOLOR(1,1,0,0.25f));
}