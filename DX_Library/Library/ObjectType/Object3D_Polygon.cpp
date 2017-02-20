//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D_Polygon.h]
// author : 大洞祥太
// 
// GameObjectが3DPolygonオブジェクトの場合、これを合成する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Object3D_Polygon.h"

CObject3DPolygon::CObject3DPolygon():m_bBillboard(true)
									,m_Divide(D3DXVECTOR3_ONE) {
	// デバイス取得
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// マネージャー取得
	m_pTextureManager = CTextureManager::Create();
	
	// 頂点情報の作成
	MakeVertexPolygon();
	
	// 色はデフォルトに初期化
	SetVertexColor( D3DXCOLOR(1.0f,1.0f,1.0f,1.0f) );
	
	m_Synthetic = eNone;
}

CObject3DPolygon::~CObject3DPolygon(){

}

void CObject3DPolygon::SetOffset( const D3DXVECTOR3 Pos ) {

	m_mtxWorld._41 = Pos.x;
	m_mtxWorld._42 = Pos.y;
	m_mtxWorld._43 = Pos.z;
}

void CObject3DPolygon::SetMatrix( GameObject* pObj ) {
	
	D3DXVECTOR3 Pos = *(pObj->GetPosition());
	D3DXVECTOR3 Size = *(pObj->GetSize());
	D3DXVECTOR3 Rot = *(pObj->GetRotation());

	SetMatrix(Pos,Size,Rot);
}

void CObject3DPolygon::SetMatrix( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const D3DXVECTOR3 Rot) {
	
	// 行列宣言
	D3DXMATRIX mtxTranslate, mtxRotation, mtxScale;
 	
	// スケールセット
	D3DXMatrixScaling( &mtxScale, Size.x, Size.y, Size.z );
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxScale);

	// 回転セットします
	// ビルボードなら
	if( m_bBillboard ) { 

		// 座標更新
		SetVertexBillBoard(Size);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &m_mtxWorld );
		
		// 逆行列を求める
		D3DXMATRIX mtxView;
		m_pD3DDevice->GetTransform( D3DTS_VIEW, &mtxView);
		D3DXMatrixInverse( &m_mtxWorld, NULL, &mtxView );

		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;
	}
	// 通常なら
	else {
		// 座標更新
		SetVertexPolygon(Size);

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity( &m_mtxWorld );
		
		// 回転セット
		D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotation);
	}

	// ポジションセット
	D3DXMatrixTranslation( &mtxTranslate, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
}

void CObject3DPolygon::Draw( GameObject* pObj ) {
	
	D3DXVECTOR3 Pos = *(pObj->GetPosition());
	D3DXVECTOR3 Size = *(pObj->GetSize());
	D3DXVECTOR3 Rot = *(pObj->GetRotation());

	Draw(pObj, Pos, Size, Rot);
}

void CObject3DPolygon::Draw( GameObject* pObj, const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const D3DXVECTOR3 Rot ) {
	
	// ライティングを無効にする
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	// もしtransformが変更されているならばマトリクス更新
	D3DXMATRIX mtxView;
	m_pD3DDevice->GetTransform( D3DTS_VIEW, &mtxView);
	if( *(pObj->GetOldRotation()) != Rot || 
		*(pObj->GetOldSize()) != Size || 
		mtxView != m_OldView ) {

		// 更新
		SetMatrix(Pos,Size,Rot);
	}
	else if (*(pObj->GetOldPosition()) != Pos ) {
		SetOffset(Pos);
	}
		
	m_OldView = mtxView;
	
	// 描画
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );
	
	switch (m_Synthetic) {
	case eSubtractive:		// 減算合成
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティングしない
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	case eAdditive:			// 加算合成
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティングしない
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	default:
		break;
	}
	
	m_pD3DDevice->SetFVF( FVF_VERTEX_3D ); // 頂点フォーマットの設定
	m_pD3DDevice->SetTexture( 0, m_pTextureManager->LoadTexture(m_FileName) ); // テクスチャのセット
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, m_Vertex, sizeof( VERTEX_3D ) ); // ポリゴンの描画

	m_pD3DDevice->SetTexture( 0, nullptr ); // テクスチャ情報初期化
	
	// ライティングを有効にする
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	// 通常ブレンド
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);				// ライティングする
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

HRESULT CObject3DPolygon::MakeVertexPolygon(){

	if( m_bBillboard ) {

		// テクスチャ座標
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	
		// 法線の設定
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	} 
	else {

		// テクスチャ座標
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		// 法線の設定
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	}

	return S_OK;
}

void CObject3DPolygon::SetVertexPolygon( const D3DXVECTOR3 Scale ){
	
	// 頂点座標の設定
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[1].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[2].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f, -Scale.z/2 );
	m_Vertex[3].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f, -Scale.z/2 );
}

void CObject3DPolygon::SetVertexBillBoard( const D3DXVECTOR3 Scale ){
	
	// 頂点座標の設定
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[1].vtx = D3DXVECTOR3( -Scale.x/2 , +Scale.y/2 , 0.0f );
	m_Vertex[2].vtx = D3DXVECTOR3( +Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[3].vtx = D3DXVECTOR3( +Scale.x/2 , +Scale.y/2 , 0.0f );
}

void CObject3DPolygon::SetVertexColor( const D3DCOLOR Color ){
	
	// 頂点カラーの設定( 0 ～ 255 )
	m_Vertex[0].diffuse = Color;
	m_Vertex[1].diffuse = Color;
	m_Vertex[2].diffuse = Color;
	m_Vertex[3].diffuse = Color;
}

// 法線変えたいなら
void CObject3DPolygon::SetVertexNormal( const D3DXVECTOR3 Normal ){
	
	// 法線の設定
	m_Vertex[0].normal = Normal;
	m_Vertex[1].normal = Normal;
	m_Vertex[2].normal = Normal;
	m_Vertex[3].normal = Normal;
}

// テクスチャアニメーションするなら
void CObject3DPolygon::SetVertexTexture( const D3DXVECTOR3 Pattern ){

	if( m_bBillboard ) {
		// Textureの設定
		m_Vertex[0].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
		m_Vertex[1].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
		m_Vertex[2].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
		m_Vertex[3].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
	}
	else {
		// Textureの設定
		m_Vertex[0].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
		m_Vertex[1].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
		m_Vertex[2].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
		m_Vertex[3].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
	}
}

// ゲッター
const LPCWSTR CObject3DPolygon::GetFileName(){
	return m_FileName;
}

// セッター
void CObject3DPolygon::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;
	
	// 読み込み実行
	m_pTextureManager->LoadTexture(m_FileName);
}

void CObject3DPolygon::SetBillFlg( const bool bFlg ){
	m_bBillboard = bFlg;
	MakeVertexPolygon();
}

void CObject3DPolygon::SetDivide( const D3DXVECTOR3 Divide ){
	m_Divide = Divide;
}

void CObject3DPolygon::SetSynthetic(ESynthetic Synthetic) {
	m_Synthetic = Synthetic;
}