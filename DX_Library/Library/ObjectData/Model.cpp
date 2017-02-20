//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Model.cpp]
// author : 大洞祥太
// 
// モデルを読み込みそのデータを保持する
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Model.h"
#include "../DirectX/Direct3D.h"
#include <iostream>
#include "../Function/Define.h"

CModel::CModel():m_Mesh(nullptr),
				 m_pAttr(nullptr),
			     m_Materials(nullptr),
			     m_Textures(nullptr),
				 m_pRootFrame(nullptr),
				 m_NumMaterials(0){
	// デバイス取得
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
}

CModel::~CModel(){}

void CModel::Uninit(){

	//SAFEARRAY(m_dwAttr);

	if( m_pAttr ) {
		delete[] m_pAttr;
		m_pAttr = nullptr;
	}
	
	if( m_Materials ){
		delete[] m_Materials;
		m_Materials = nullptr;
	}
	
	if( m_Textures ){
		for( DWORD i = 0; i < m_NumMaterials; i++ ){
			if( !m_Textures[i] ) continue;
			m_Textures[i]->Release();
		}
		delete[] m_Textures;
		m_Textures = nullptr;
	}

	if( m_Mesh ){
		m_Mesh->Release();
		m_Mesh = nullptr;
	}

	// 開放処理
	if ( m_pMainAnimationController ) {
		m_pMainAnimationController->Release();
		m_pMainAnimationController = nullptr;
	}
	m_Allocater.DestroyFrame( m_pRootFrame );
}

// モデル読み込み
bool CModel::LoadModel( const std::wstring& filename ){
	
	// 読み込み
	if ( FAILED( D3DXLoadMeshHierarchyFromX( filename.c_str(), D3DXMESH_MANAGED, m_pD3DDevice,
				 &m_Allocater, NULL, (D3DXFRAME**)&m_pRootFrame, &m_pMainAnimationController) ) ||
		 !m_pMainAnimationController )	// アニメーションコントローラーを取得できなかった時も通常読み込みとする
	{	
		LPD3DXBUFFER pD3DXMtrlBuffer;
		// Xファイル読み込み
		if( FAILED( D3DXLoadMeshFromX( filename.c_str(), D3DXMESH_SYSTEMMEM, m_pD3DDevice, NULL,
					&pD3DXMtrlBuffer, NULL, &m_NumMaterials, &m_Mesh ) ) ){
			MessageBox( NULL, _T("There is no X-file that the filename"), _T("3D Lib"), MB_OK );
			return false;
		}
		
		// 法線が無い場合は強制的に追加
		if ((m_Mesh->GetFVF() & D3DFVF_NORMAL) == 0) {
			LPD3DXMESH pMeshTmp = m_Mesh;
			pMeshTmp->CloneMeshFVF(pMeshTmp->GetOptions(), pMeshTmp->GetFVF() | D3DFVF_NORMAL,
				CDirect3D::Create()->GetDirect3DDevice(), &m_Mesh);
			SAFE_RELEASE(pMeshTmp);
			D3DXComputeNormals(m_Mesh, NULL);
		}

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		m_Materials = new D3DMATERIAL9[m_NumMaterials];
		if( m_Materials == NULL ) return false;
		m_Textures = new LPDIRECT3DTEXTURE9[m_NumMaterials];
		if( m_Textures == NULL ) return false;

		for( int i = 0; i < (int)m_NumMaterials; i++ ){
			// マテリアルのコピー
			m_Materials[i] = d3dxMaterials[i].MatD3D;
			// アンビエント色の設定
			m_Materials[i].Ambient = m_Materials[i].Diffuse;
			
			// 固定のパスにテクスチャ名を結合
			char TexturePath[256];
			lstrcpyA(TexturePath, ModelTextureFolderPath);
			lstrcatA(TexturePath, d3dxMaterials[i].pTextureFilename);

			// 読み込み実行
			if( d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 ){
					if( FAILED( D3DXCreateTextureFromFileA( m_pD3DDevice, 
						TexturePath, &m_Textures[i] ) ) ){
					MessageBox( NULL, _T("There is no TextureFile that the pTextureFilename"), _T("3D Lib"), MB_OK );
					return false;
				}
			}
			else { // テクスチャは設定されていないのでm_Textureは解放しておく
				m_Textures[i] = nullptr;
			}
		}

		m_dwAttr = 0;
		m_Mesh->GetAttributeTable(nullptr, &m_dwAttr);
		m_pAttr = new D3DXATTRIBUTERANGE[m_dwAttr];
		m_Mesh->GetAttributeTable(m_pAttr,&m_dwAttr);

		pD3DXMtrlBuffer->Release();
		
#ifdef DEBUG
		std::cout << "スキンメッシュなしのモデルを読み込みました" << std::endl;
#endif

	}
	else{
		// ボーンの加工
		m_Allocater.CreateBone( m_pRootFrame, (LPD3DXFRAME)m_pRootFrame );

		// アニメーションを60FPSに調整
		if( m_pMainAnimationController )
			m_pMainAnimationController->SetTrackSpeed( 0, 60.0F/4800.0F);
		
#ifdef DEBUG
		std::cout << "スキンメッシュありのモデルを読み込みました" << std::endl;
#endif
	}

	return true;
}

// モデルせっと
void CModel::RenderModel( const D3DXMATRIXA16* pMtx, const bool bShadow, D3DXCOLOR MaterialColor ){

	D3DMATERIAL9 matDef;

	// 現在のマテリアル情報を取得
	m_pD3DDevice->GetMaterial( &matDef );

	std::list<D3DXCOLOR> Color = GetMaterialColor();	//	保存
	SetMaterialColor(MaterialColor);	// 変更
	
	if( m_pMainAnimationController ) {
		//m_pAnimationController->AdvanceTime( m_fAnimSpeed, NULL );
		m_FMTransformer.Run( m_pRootFrame, pMtx );
		m_AMDrawer.Draw( m_pRootFrame, m_pD3DDevice );
	}
	
	else {
		if( bShadow )
			DrawShadow();
		else
			SetModel();
	}

	// 元に戻す
	SetMaterialColor(Color);
	m_pD3DDevice->SetMaterial( &matDef );
	m_pD3DDevice->SetTexture(0,NULL);
}

void CModel::SetModel() {
	
	if( !m_Materials ) return;
	if( !m_Mesh ) return;

	for( DWORD i = 0; i < m_dwAttr; i++ ) {

		DWORD dwID = m_pAttr[i].AttribId;

		m_pD3DDevice->SetMaterial( &m_Materials[dwID] );
		
		if( m_Textures[i] )
			m_pD3DDevice->SetTexture( 0, m_Textures[dwID] );
		
		m_Mesh->DrawSubset(dwID);
	}
}

void CModel::DrawShadow(){
	if( !m_Mesh ) return;

	for( DWORD i = 0; i < m_NumMaterials; i++ )
		m_Mesh->DrawSubset(i);
}

// 色セット
void CModel::SetMaterialColor( const D3DXCOLOR Color ){
	
	for( DWORD i = 0; i < m_NumMaterials; i++ )
		m_Materials[i].Diffuse = Color;
}

void CModel::SetMaterialColor( std::list<D3DXCOLOR> Color ){
	
	DWORD i = 0;
	for( auto Ite = Color.begin(); Ite != Color.end(); i++, Ite++ ) {
		m_Materials[i].Diffuse = *(Ite);
	}
}

// 色ゲット
std::list<D3DXCOLOR> CModel::GetMaterialColor(){
	
	std::list<D3DXCOLOR> MaterialColor;

	for( DWORD i = 0; i < m_NumMaterials; i++ )
		MaterialColor.push_back(m_Materials[i].Diffuse);

	return MaterialColor;
}

LPD3DXANIMATIONCONTROLLER CModel::GetMainAnimationController() {

	if( !m_pMainAnimationController )
		return nullptr;

	LPD3DXANIMATIONCONTROLLER pCopyAnimationController;

	m_pMainAnimationController->CloneAnimationController(
	m_pMainAnimationController->GetMaxNumAnimationOutputs(),
	m_pMainAnimationController->GetMaxNumAnimationSets(),
	m_pMainAnimationController->GetMaxNumTracks(),
	m_pMainAnimationController->GetMaxNumEvents(),
	&pCopyAnimationController);

	return pCopyAnimationController;
}

D3DXMATRIX* CModel::GetBoneMatrixWithName(const LPSTR BoneName, eBonePlace BonePlace, SkinMesh::TMyD3DXFRAME* pRootFrame) {
	
	// 最初は頭を格納
	if(!pRootFrame) {
		pRootFrame = m_pRootFrame;
	}

   // 比較
   if( strcmp(BoneName, pRootFrame->Name) == 0 ) {

	   D3DXMATRIX mat;

	   switch (BonePlace) {
		  
	   case Place_Tip:	// 先端
		   if(pRootFrame->pFrameFirstChild) {
			   SkinMesh::TMyD3DXFRAME* child = (SkinMesh::TMyD3DXFRAME*)pRootFrame->pFrameFirstChild;
			   mat = child->mtxWorld;
			   break;
		   }
		   // なければ根元を返す
	   case Place_Center:	// 中心
		   if(pRootFrame->pFrameFirstChild) {
			   mat = pRootFrame->mtxWorld;
			   SkinMesh::TMyD3DXFRAME* child = (SkinMesh::TMyD3DXFRAME*)pRootFrame->pFrameFirstChild;
			   mat += (child->mtxWorld - pRootFrame->mtxWorld) / 2.0f;
			   break;
		   }
		   // なければ根元を返す
	   case Place_Root:	// 根元
		   mat = pRootFrame->mtxWorld;
		   break;
	   }

	   return &mat;
   }

   D3DXMATRIX* pTmp = nullptr;
   // 子フレームを検索
   if( pRootFrame->pFrameFirstChild ) {
		pTmp = GetBoneMatrixWithName( BoneName, BonePlace, (SkinMesh::TMyD3DXFRAME*)pRootFrame->pFrameFirstChild );
		if(pTmp)
			return pTmp;
   }

   // 兄弟フレームを検索
   if( pRootFrame->pFrameSibling ) {
		pTmp = GetBoneMatrixWithName( BoneName, BonePlace, (SkinMesh::TMyD3DXFRAME*)pRootFrame->pFrameSibling );
		if(pTmp)
			return pTmp;
   }

   // 見つからなかった
   return nullptr;
}