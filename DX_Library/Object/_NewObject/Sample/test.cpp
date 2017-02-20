//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [test.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "test.h"

test::test() {
	m_Transform.Name = "Test";
}

test::~test() {
	m_particle.Clear();
}

bool test::Start(){
	
	m_particle.SetFileName(_T("PARTICLE/flare07.bmp"));
	//m_particle.SetFileName(_T("flare08.bmp"));
	//m_particle.SetFileName(_T("ParticleCloudWhite.png"));
	//m_particle.SetFileName(_T("Shadow.jpg"));

	TParticleParam pp;
	
	/*
	pp.fDuration = 10.0f;
	pp.uMaxParticles = 100;
	pp.coord = eCartesian;
	pp.synthetic = eAdditive;
	pp.bLooping = true;
	pp.fGravity = 9.8f;
	pp.fStartSpeed = -5.0f;
	pp.fStartSpeed2 = -50.0f;
	pp.fStartSize = 100.0f;
	pp.fStartSize2 = 100.0f;
	pp.fStartRotation = 0.0f;
	pp.fStartRotation2 = pp.fStartRotation;
	pp.cStartColor = D3DCOLOR_ARGB(127, 255, 255, 255);
	pp.cStartColor2 = pp.cStartColor;
	pp.fStartLifetime = 2.0f;
	pp.fStartLifetime2 = pp.fStartLifetime;
	pp.uRate = 10;
	pp.fCornAngle = 3.0f;
	pp.fRadius = 0.0f;
	pp.bColorOverLifetime = true;
	pp.cOverLifetime[0] = D3DCOLOR_ARGB(127, 255, 255, 127);
	pp.cOverLifetime[1] = D3DCOLOR_ARGB(0, 127, 0, 0);
	pp.bSizeOverLifetime = true;
	pp.fOverLifetime[0] = 10.0f;
	pp.fOverLifetime[1] = 200.0f;
	*/
	
	/*
	pp.fDuration = 2.5f;
	pp.uMaxParticles = 100;
	pp.coord = eCartesian;
	pp.synthetic = eAdditive;
	pp.bLooping = true;
	pp.fGravity = 0.0f;//9.8f;
	pp.fStartSpeed = 25.0f;
	pp.fStartSpeed2 = 50.0f;
	pp.fStartSize = 25.0f;
	pp.fStartSize2 = pp.fStartSize;
	pp.fStartRotation = 0.0f;
	pp.fStartRotation2 = pp.fStartRotation;
	pp.cStartColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pp.cStartColor2 = pp.cStartColor;
	pp.fStartLifetime = 3.0f;
	pp.fStartLifetime2 = pp.fStartLifetime;
	pp.uRate = 30;
	pp.fCornAngle = 360.0f;
	pp.fRadius = 0.0f;
	pp.bColorOverLifetime = true;
	const int nColor = 5;
	pp.cOverLifetime[0] = D3DCOLOR_ARGB(255, nColor, nColor, nColor);
	pp.cOverLifetime[1] = D3DCOLOR_ARGB(  0, nColor,      0, nColor);
	pp.bSizeOverLifetime = true;
	pp.fOverLifetime[0] = 400.0f;
	pp.fOverLifetime[1] = 80.0f;
	*/

	///*
	pp.fDuration = 5.0f;
	pp.uMaxParticles = 15000;
	pp.bLooping = true;
	pp.synthetic = eAdditive;
	pp.eShape = eCircleXY;
	pp.fGravity = 0.0f;//90.8f;
	pp.fStartSpeed = 10.0f;
	pp.fStartSpeed2 = 1.0f;
	pp.fStartSize = 0.0f;
	pp.fStartSize2 = pp.fStartSize;
	pp.fStartRotation = 0.0f;
	pp.fStartRotation2 = pp.fStartRotation;
	pp.cStartColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pp.cStartColor2 = pp.cStartColor;
	pp.fStartLifetime = 1.0f;
	pp.fStartLifetime2 = pp.fStartLifetime;
	pp.StartRange = D3DXVECTOR3(20.0f,20.0f,20.0f);
	pp.StartRange2 = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pp.uRate = 3000;
	pp.fCornAngle = 360.0f;
	pp.fRadius = 0.0f;
	pp.bColorOverLifetime = true;
	pp.cOverLifetime[0] = D3DCOLOR_ARGB(255,  51,  51, 255);
	pp.cOverLifetime[1] = D3DCOLOR_ARGB(  0,  51,  51, 255);
	pp.bSizeOverLifetime = true;
	pp.fOverLifetime[0] = 2.0f;
	pp.fOverLifetime[1] = 1.0f;
	//*/
	
	/*
	pp.fDuration = 10.0f;
	pp.uMaxParticles = 300;
	pp.coord = eCartesian;
	pp.synthetic = eAdditive;
	pp.bLooping = true;
	pp.fGravity = 0.0f;//-9.8f;
	pp.fStartSpeed = 0.0f;
	pp.fStartSpeed2 = 0.5f;
	pp.fStartSize = 1.0f;
	pp.fStartSize2 = 10.0f;
	pp.fStartRotation = 0.0f;
	pp.fStartRotation2 = pp.fStartRotation;
	pp.cStartColor = D3DCOLOR_ARGB(127, 255, 255, 255);
	pp.cStartColor2 = pp.cStartColor;
	pp.fStartLifetime = 2.0f;
	pp.fStartLifetime2 = pp.fStartLifetime;
	pp.uRate = 20;
	pp.fCornAngle = 360.0f;
	pp.fRadius = 0.0f;
	pp.bColorOverLifetime = true;
	pp.cOverLifetime[0] = D3DCOLOR_ARGB(127, 255, 255, 127);
	pp.cOverLifetime[1] = D3DCOLOR_ARGB(0, 127, 0, 0);
	pp.bSizeOverLifetime = true;
	pp.fOverLifetime[0] = 2.0f;
	pp.fOverLifetime[1] = 40.0f;
	*/
	
	m_particle.SetParam(pp);
	m_particle.Start();
	//m_particle.SetPosition(D3DXVECTOR3(0,0,0));
	//m_Transform.Position.x = fWindowWidth /2.0f;
	//m_Transform.Position.y = fWindowHeight/2.0f;

	m_Transform.Position.z += 10.0f;

	m_pDirectInputManager = CDirectInputManager::Create();

	return true;
}

void test::Update(){
	
	D3DXVECTOR3 move = D3DXVECTOR3(0,0,0);
	//const float fMove = 0.3f;
	const float fMove = 1.0f;

	if(m_pDirectInputManager->GetKeyboardHold(DIK_W)) {
		move.y = fMove;
	} else if(m_pDirectInputManager->GetKeyboardHold(DIK_S)) {
		move.y = -fMove;
	}
	if(m_pDirectInputManager->GetKeyboardHold(DIK_A)) {
		move.x = -fMove;
	} else if(m_pDirectInputManager->GetKeyboardHold(DIK_D)) {
		move.x = fMove;
	}

	if(move.x != 0.0f && move.y != 0.0f) {
		move.x *= 0.66f;
		move.y *= 0.66f;
		Move(move);
	} else if(move.x != 0.0f || move.y != 0.0f) {
		Move(move);
	}

	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_Z)) {
		//m_particle.ChangeColor(D3DCOLOR_ARGB(255,  51,  51, 255), D3DCOLOR_ARGB(0,  51,  51, 255));
		//m_particle.ChangeSize(2.0f, 1.0f);
		//m_particle.ChangeSpeed(10.0f, 1.0f);
	} 

	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_X)) {
		//m_particle.ChangeColor(D3DCOLOR_ARGB(255,  255,  51, 51), D3DCOLOR_ARGB(0,  255,  51, 51));
		//m_particle.ChangeSize(4.0f, 1.0f);
		//m_particle.ChangeSpeed(20.0f, 1.0f);
	} 

	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_C)) {
		//m_particle.ChangeColor(D3DCOLOR_ARGB(255,  51,  255, 51), D3DCOLOR_ARGB(0,  51,  255, 51));
		//m_particle.ChangeSize(8.0f, 1.0f);
		//m_particle.ChangeSpeed(30.0f, 1.0f);
	} 
	
	/*if(m_pDirectInputManager->GetKeyboardTrigger(DIK_Z)) {
		m_particle.Play();
	}
	
	else if(m_pDirectInputManager->GetKeyboardTrigger(DIK_X)) {
		m_particle.Pause();
	}
	
	else if(m_pDirectInputManager->GetKeyboardTrigger(DIK_C)) {
		m_particle.Simulate();
	}
	
	else if(m_pDirectInputManager->GetKeyboardTrigger(DIK_V)) {
		m_particle.Stop();
	}
	
	else if(m_pDirectInputManager->GetKeyboardHold(DIK_B)) {
		m_particle.Emit(300);
	}*/

	m_particle.SetPosition(m_Transform.Position);
	m_particle.Update();
}

void test::LateDraw(){
	m_particle.LateDraw();
}