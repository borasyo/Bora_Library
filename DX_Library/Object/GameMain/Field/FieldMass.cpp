//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [FieldMass.cpp]
// author : ‘å“´Ë‘¾
//
// ŠT—v : 1ƒ}ƒX•ª‚Ì•`‰æ&î•ñ•Û
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "FieldMass.h"

CFieldMass::CFieldMass(int x, int z, int Size){
	m_Transform.Name = "FieldMass";
	m_Transform.Size = D3DXVECTOR3(BOX_SIZE, 1.0f, BOX_SIZE);
	
	if(Size != 4) {
		Size /= 2;
		Move(D3DXVECTOR3((x - Size) * BOX_SIZE, -0.5f, (-z + Size) * BOX_SIZE));
	}
	else {
		Move(D3DXVECTOR3((x - 1.5f) * BOX_SIZE, -0.5f, (-z + 1.5f) * BOX_SIZE));
	}

	m_Mass.SetBillFlg(false);
	m_Mass.SetMatrix(this);
	m_Mass.SetFileName(_T("Field/FieldMass.png"));
	m_Mass.SetVertexColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
//	m_Mass.SetVertexColor(D3DXCOLOR((rand()%100) / 100.0f, (rand()%100) / 100.0f, (rand()%100) / 100.0f, 1.0f));
}

CFieldMass::~CFieldMass() {

}

//bool CFieldMass::Start(){
//	return true;
//}

//void CFieldMass::Update(){
//	
//}

void CFieldMass::Draw(){
	m_Mass.Draw(this);
}