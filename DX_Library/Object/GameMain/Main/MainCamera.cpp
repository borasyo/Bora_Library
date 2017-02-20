//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MainCamera.cpp]
// author : ‘å“´Ë‘¾
//
// ŠT—v : 
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "MainCamera.h"

// --- ’è”
const float fHeight = 1.0f;
const float fDistance = 6.5f;

CMainCamera::CMainCamera() {
	m_Transform.Name = "MainCamera";

	m_Transform.Position = D3DXVECTOR3(11.5f,8.0f,0.0f);
	*(m_Camera.GetLookatPt()) = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

CMainCamera::~CMainCamera() {

}

bool CMainCamera::Start(){
	
#ifdef DEBUG
	// InputŽæ“¾
	m_pDirectInputManager = CDirectInputManager::Instance();
#endif
	
	CCameraBase::Start();

	return true;
}

void CMainCamera::Update(){
	
	CCameraBase::Update();
	
#ifdef DEBUG
	const float move = 0.1f;
	if(m_pDirectInputManager->GetKeyboardHold(DIK_1)) {
		m_Transform.Position.x += move;
		//m_ObjectCamera.GetLookatPt()->x += move;
	}
	if(m_pDirectInputManager->GetKeyboardHold(DIK_2)) {
		m_Transform.Position.x -= move;
		//m_ObjectCamera.GetLookatPt()->x -= move;
	}
	if(m_pDirectInputManager->GetKeyboardHold(DIK_3)) {
		m_Transform.Position.y += move;
		//m_ObjectCamera.GetLookatPt()->y += move;
	}
	if(m_pDirectInputManager->GetKeyboardHold(DIK_4)) {
		m_Transform.Position.y -= move;
		//m_ObjectCamera.GetLookatPt()->y -= move;
	}
	if(m_pDirectInputManager->GetKeyboardHold(DIK_5)) {
		m_Transform.Position.z += move;
		//m_ObjectCamera.GetLookatPt()->z += move;
	}
	if(m_pDirectInputManager->GetKeyboardHold(DIK_6)) {
		m_Transform.Position.z -= move;
		//m_ObjectCamera.GetLookatPt()->z -= move;
	}

	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_RSHIFT)) {
		DebugLogVec3("CameraPos", m_Transform.Position);
	}
#endif
}