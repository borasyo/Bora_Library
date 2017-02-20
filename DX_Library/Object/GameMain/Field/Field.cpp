//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Field.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Field.h"

CField::CField() {
	m_Transform.Name = "Field";
	m_Object.SetFileName(_T("FIELD/Field.x"));
}

CField::~CField() {
	
}

bool CField::Start() {

	m_Transform.Position.y = -0.615f;
	m_Transform.Size = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	m_Object.SetMatrix(this);

	return true;
}

void CField::Update() {

}

void CField::Draw() {
	m_Object.Draw(this);
}