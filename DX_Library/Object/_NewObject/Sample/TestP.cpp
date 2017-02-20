//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TestP.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "TestP.h"

TestP::TestP() {
	m_Transform.Name = "TestP";
	m_Object2D.SetFileName(_T("thessaloniks.jpg"));
}

TestP::~TestP() {
	
}

bool TestP::Start(){

	m_Transform.Position.x += 300.0f;
	m_Transform.Position.y += 300.0f;
	SetCollisionCubeSize(D3DXVECTOR3_ONE);
	SetCollisionCircleSize(1.0f);
	ScaleChange(100.0f);
	m_pDirectInputManager = CDirectInputManager::Create();
	//m_Transform.Rotation.z = 45.0f;
	
	// s—ñ‰Šú‰»
	//m_Object3D.SetMatrix(m_Transform.Position, m_Transform.Size, m_Transform.Rotation);

	return true;
}

void TestP::Update(){

	const int move = 3;
	if( m_pDirectInputManager->GetKeyboardHold(DIK_W) ) {
		Move(D3DXVECTOR3(0,-move,0));
	}
	else if( m_pDirectInputManager->GetKeyboardHold(DIK_S) ) {
		Move(D3DXVECTOR3(0,move,0));
	}
	
	if( m_pDirectInputManager->GetKeyboardHold(DIK_A) ) {
		Move(D3DXVECTOR3(-move,0,0));
	}
	else if( m_pDirectInputManager->GetKeyboardHold(DIK_D) ) {
		Move(D3DXVECTOR3(move,0,0));
	}

}

void TestP::Draw(){
	
	m_Object2D.Draw( this );
}

void TestP::LateDraw() {
	//m_Object3D.ColDraw(this, D3DXCOLOR(1,0,0,0.5f));
}


void TestP::OnCollisionEnter(GameObject* pObj) {
	std::cout << "ŒÄ‚Î‚ê‚½" << std::endl;
}