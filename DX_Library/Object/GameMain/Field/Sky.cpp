//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Sky.cpp]
// author : 大洞祥太
//
// 概要 : スカイドーム表示
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Sky.h"
#include "../../../Library/Task/TaskManager.h"
#include "../../../Library/DirectX/Direct3D.h"

const float fRotTime = 25.0f;

CSky::CSky() {
	m_Transform.Name = "Sky";
	m_Object3D.SetFileName(_T("Field/Sky.x"));

	//ScaleChange(0.5f);
	SetCollisionFlg(false);
}

CSky::~CSky() {
	
}

bool CSky::Start(){

	//m_Object3D.SetColDraw(false);

	pCamera = TaskManager::Instance()->FindWithTag("Camera");
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	return true;
}

void CSky::Update(){

	m_Transform.Position = *(pCamera->GetPosition());
	m_Transform.Rotation.y += CTime::GetChangeAmount(Pai*2.0f,fRotTime);
}

void CSky::FastDraw(){
	
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	m_Object3D.Draw(this);
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}