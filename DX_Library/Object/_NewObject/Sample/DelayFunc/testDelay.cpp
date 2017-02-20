//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testDelay.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "testDelay.h"

testDelay::testDelay() {
	m_Transform.Name = "testDelay";
	m_Object2D.SetFileName(_T("SLOT/slot.png"));
}

testDelay::~testDelay() {
	
}

bool testDelay::Start(){

	Move(D3DXVECTOR3(rand()%(int)fWindowWidth, rand()%(int)fWindowHeight, 0.0f));
	m_Transform.Size = D3DXVECTOR3_ONE * 100.0f;
	m_nLife = 60;

	return true;
}

void testDelay::Update(){
	m_nLife--;
}

void testDelay::Draw(){
	m_Object2D.Draw(this);
}