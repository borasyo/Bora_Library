
#include "ObjectCamera.h"
#include "../DirectX/Direct3D.h"
#include "../DirectX/Window.h"

CObjectCamera::CObjectCamera()
	:m_LookatPt(0,0,0)
	,m_UpVec(0,1,0) {
	m_pD3DDevice = CDirect3D::Instance()->GetDirect3DDevice();

	CWindow* pWindow = CWindow::Instance();
	m_ViewPort.X = (DWORD)0.0f;
	m_ViewPort.Y = (DWORD)0.0f;
	m_ViewPort.Height = (DWORD)pWindow->GetClientHeight();
	m_ViewPort.Width = (DWORD)pWindow->GetClientWidth();
	m_ViewPort.MinZ = 0.0f;
	m_ViewPort.MaxZ = 1.0f;

	D3DXMatrixIdentity(&m_View);
}

CObjectCamera::~CObjectCamera(){

}

// カメラをセットする
void CObjectCamera::Set(D3DXVECTOR3 pos){

	m_pD3DDevice->SetViewport(&m_ViewPort);
	D3DXMatrixLookAtLH(&m_View, &pos, &m_LookatPt , &m_UpVec);
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &m_View);
}

// ViewPortを設定
void CObjectCamera::SetViewPort(D3DVIEWPORT9 ViewPort){
	m_ViewPort = ViewPort;
}

void CObjectCamera::SetMatrix(D3DXVECTOR3 pos) {
	D3DXMatrixLookAtLH( &m_View, &pos, &m_LookatPt , &m_UpVec );
}

// ゲッター
D3DXVECTOR3* CObjectCamera::GetLookatPt(){
	return &m_LookatPt;
}

D3DXVECTOR3* CObjectCamera::GetUpVec(){
	return &m_UpVec;
}