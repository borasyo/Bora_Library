
#include "Object3D_Model.h"
#include "../DirectX/Direct3D.h"

// -- 実体定義
bool CObject3DModel::m_bColDraw = false;

CObject3DModel::CObject3DModel(){
	// デバイス取得
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// マネージャー取得
	m_pModelManager = CModelManager::Create();

	// 名前初期化
	m_FileName = nullptr;

	// 基準値を格納
	m_fAnimSpeed = 1.0f;

	// アニメーションするか
	m_bAnim = true;
	
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxWorld );

	// マテリアルカラー初期化
	m_MaterialColor = D3DXCOLOR(1,1,1,1);

	//m_bColDraw = true;
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_OldColSize = D3DXVECTOR3_ZERO;
	
	// 境界表示用メッシュ生成
	D3DXCreateBox(m_pD3DDevice, 2.0f, 2.0f, 2.0f, &m_pBBox, NULL);
	D3DXCreateSphere(m_pD3DDevice, 1.0f, 16, 8, &m_pBSphere, NULL);
}

CObject3DModel::~CObject3DModel(){
	
	SAFE_RELEASE(m_pBSphere);
	SAFE_RELEASE(m_pBBox);
}	

void CObject3DModel::SetMatrix( GameObject* pObj ) {
	
	D3DXVECTOR3 Pos = *(pObj->GetPosition());
	D3DXVECTOR3 Size = *(pObj->GetSize());
	D3DXVECTOR3 Rot = *(pObj->GetRotation());

	SetMatrix(Pos,Size,Rot);
}

void CObject3DModel::SetMatrix( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const D3DXVECTOR3 Rot ) {
	
	D3DXMATRIXA16 mtxTranslate, mtxRotation, mtxSize;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxWorld );

	// スケールセット
	D3DXMatrixScaling( &mtxSize, Size.x, Size.y, Size.z );
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxSize);

	// 回転セット
	D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotation);
	
	// ポジションセット
	D3DXMatrixTranslation( &mtxTranslate, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
}

void CObject3DModel::SetOffset( const D3DXVECTOR3 Pos ) {

	m_mtxWorld._41 = Pos.x;
	m_mtxWorld._42 = Pos.y;
	m_mtxWorld._43 = Pos.z;
}

// 描画関数
void CObject3DModel::Draw( GameObject* pObj, const bool bShadow ) {
	
	D3DXVECTOR3 Pos = *(pObj->GetPosition());
	D3DXVECTOR3 Size = *(pObj->GetSize());
	D3DXVECTOR3 Rot = *(pObj->GetRotation());

	Draw(pObj, Pos, Size, Rot, bShadow);
}

void CObject3DModel::Draw( GameObject* pObj, const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const D3DXVECTOR3 Rot, const bool bShadow ) {

	// アニメーションするので時間更新
	if( m_bAnim && m_AnimationManager.GetAnimationController() )
		UpdateAnim();

	// もしtransformが変更されているならばマトリクス更新
	if( *(pObj->GetOldRotation()) != Rot || 
		*(pObj->GetOldSize())     != Size ) {

		SetMatrix(Pos,Size,Rot);
	} 
	else if (*(pObj->GetOldPosition()) != Pos ) {
		SetOffset(Pos);
	}

	// 描画情報セット
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );
	
	// モデル描画
	m_pModelManager->RenderModel( &m_mtxWorld, m_FileName, bShadow, m_MaterialColor );
}

void CObject3DModel::ColDraw(GameObject* pObj, D3DXCOLOR Color) {
	
	if(!m_bColDraw)
		return;
	
	if(pObj->GetCollisionCubePlusSize() != m_OldColSize) {
		SetMesh(pObj);
	}
	m_OldColSize = pObj->GetCollisionCubePlusSize();
	
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DXMATRIX mtx;
	D3DXMatrixIdentity(&mtx);
	
	mtx._11 = mtx._22 = mtx._33 = 1.0f;
	
	if(*(pObj->GetRotation()) != D3DXVECTOR3_ZERO) {	
		// 回転セット
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationYawPitchRoll( &mtxRotation, pObj->GetRotation()->y, pObj->GetRotation()->x, pObj->GetRotation()->z );
		D3DXMatrixMultiply(&mtx, &mtx, &mtxRotation);
	}

	mtx._41 = m_mtxWorld._41;
	mtx._42 = m_mtxWorld._42;
	mtx._43 = m_mtxWorld._43;

	//	コリジョンの形に合わせて描画切り替え
	if(pObj->GetCollisionCircleSize() > 0.0f) {
		DrawSphere(pObj, mtx, Color);
	} else if(*(pObj->GetRotation()) > D3DXVECTOR3_ZERO) {
		DrawOBB(pObj, mtx, Color);
	} else {
		DrawAABB(pObj, mtx, Color);
	}
	
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// ゲッター
const LPCWSTR CObject3DModel::GetFileName(){
	return m_FileName;
}

// セッター
void CObject3DModel::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;

	// ファイル名が指定された時、マップに追加させる
	m_pModelManager->RenderModel( &m_mtxWorld, m_FileName, false, m_MaterialColor );
}

void CObject3DModel::SetMaterialColor( const D3DXCOLOR Color ){
	
	m_MaterialColor = Color;
	//CModel* pModel = m_pModelManager->GetModel( m_FileName );
	//pModel->SetMaterialColor( Color );
}

// コピーしたアニメーションコントローラーを取得し、保存
void CObject3DModel::SetAnimationController(){

	// 名前が分からないのにモデルのアニメーションコントローラーを取得できるわけない
	if( !m_FileName )
		return;

	LPD3DXANIMATIONCONTROLLER pCopyAnimationController = m_pModelManager->GetModel( m_FileName )->GetMainAnimationController();

	// 取得失敗
	if( !pCopyAnimationController )
		return;

	// 取得成功
	m_AnimationManager.SetAnimationController( pCopyAnimationController );
}

bool CObject3DModel::UpdateAnim(){
	
	// アニメーションコントローラーがあって、アニメーションを再生してもよいなら
	//if( m_AnimationManager.GetAnimationController() || m_bAnim )
	return m_AnimationManager.AdvanceTime( m_fAnimSpeed );

	//return false;
}

void CObject3DModel::SetAnimSpeed( const float fAnimSpeed ) {

	if( !m_bAnim )
		return;

	// 指定したスピードに格納
	m_fAnimSpeed = fAnimSpeed;
}

// アニメーションするかどうかのフラグを反転する
void CObject3DModel::SetAnimFlg( const bool bFlg ){
	m_bAnim = bFlg;
}

// アニメーションコントローラーを取得
CAnimationController* CObject3DModel::GetAnimationManager() {
	return &m_AnimationManager;
}

D3DXMATRIX* CObject3DModel::GetBoneMatrixWithName(const LPSTR Name, eBonePlace BonePlace) {
	return m_pModelManager->GetModel(m_FileName)->GetBoneMatrixWithName(Name,BonePlace);
}

// ---- Debug

void CObject3DModel::SetMesh(GameObject* pObj) {
	
	// 境界表示用メッシュ再生成
	D3DXVECTOR3 Cube = pObj->GetCollisionCubePlusSize();
	D3DXCreateBox(m_pD3DDevice, Cube.x, Cube.y, Cube.z, &m_pBBox, NULL);
	D3DXCreateSphere(m_pD3DDevice, pObj->GetCollisionCircleSize() / 2.0f, 16, 8, &m_pBSphere, NULL);
}
	
void CObject3DModel::DrawOBB(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color) {
	
	// ワールドマトリックス設定
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	// マテリアル設定
	m_pD3DDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = Color;
	m_pD3DDevice->SetMaterial(&mtrl);

	// 描画
	m_pBBox->DrawSubset(0);
}

void CObject3DModel::DrawAABB(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color) {
	
	// ワールドマトリックス設定
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	// マテリアル設定
	m_pD3DDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = Color;
	m_pD3DDevice->SetMaterial(&mtrl);

	// 描画
	m_pBBox->DrawSubset(0);
}

void CObject3DModel::DrawSphere(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color) {

	// ワールドマトリックス設定
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	// マテリアル設定
	m_pD3DDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = Color;
	m_pD3DDevice->SetMaterial(&mtrl);

	// 描画
	m_pBSphere->DrawSubset(0);
}

//#endif
