//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object2D.cpp]
// author : 大洞祥太
//
// 2D描画を引き受けるクラス
// 回転には軸であるZの回転量を適用する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Object2D.h"
#include "../DirectX/Direct3D.h"

// アフィン変換
#define AFFINE_X(x,y,w,h,r,t1,t2) ( x+(w/2) + ( (t1*w)/2*cosf(r) - (t2*h)/2*sinf(r) ) )
#define AFFINE_Y(x,y,w,h,r,t1,t2) ( y+(h/2) + ( (t1*w)/2*sinf(r) + (t2*h)/2*cosf(r) ) )

CObject2D::CObject2D(){
	MakeVertexPolygon();
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_pTextureManager = CTextureManager::Create();
	m_Divide = D3DXVECTOR2_ONE;
	m_Synthetic = eNone;
}

// --- デストラクタ
CObject2D::~CObject2D(){

}

// 描画関数
void CObject2D::Draw( GameObject* pObj ){ 
	
	D3DXVECTOR3 Pos = *(pObj->GetPosition());
	D3DXVECTOR3 Size = *(pObj->GetSize());
	float fRot = pObj->GetRotation()->z;

	Draw(Pos, Size, fRot);
}

void CObject2D::Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const float fRot ){ 

	switch (m_Synthetic) {
	case eSubtractive:		// 減算合成
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティングしない
		//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		// THRU
	case eAdditive:			// 加算合成
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
		//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティングしない
		//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	default:
		break;
	}

	SetVertexPolygon( Pos, Size, fRot );	// VERTEX_2D更新
	
	m_pD3DDevice->SetFVF( FVF_VERTEX_2D ); // 頂点フォーマットの設定
	m_pD3DDevice->SetTexture( 0, m_pTextureManager->LoadTexture(m_FileName) ); // テクスチャのセット
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, m_Vertex, sizeof( VERTEX_2D ) ); // ポリゴンの描画
	
	m_pD3DDevice->SetTexture( 0, nullptr ); // テクスチャ情報初期化
	
	// 通常ブレンド
	//m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);			// Zバッファ更新を有効に
	//m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);				// ライティングする
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

// 座標更新
void CObject2D::SetVertexPolygon( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot ){
	
	if( fRot == 0.0f ) {
		m_Vertex[0].pos = D3DXVECTOR3( Pos.x - Scale.x/2 , Pos.y - Scale.y/2 , Pos.z );
		m_Vertex[1].pos = D3DXVECTOR3( Pos.x + Scale.x/2 , Pos.y - Scale.y/2 , Pos.z );
		m_Vertex[2].pos = D3DXVECTOR3( Pos.x - Scale.x/2 , Pos.y + Scale.y/2 , Pos.z );
		m_Vertex[3].pos = D3DXVECTOR3( Pos.x + Scale.x/2 , Pos.y + Scale.y/2 , Pos.z );
	}

	else {
		m_Vertex[0].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1,-1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1,-1), Pos.z );
		m_Vertex[1].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1,-1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1,-1), Pos.z );
		m_Vertex[2].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1, 1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot,-1, 1), Pos.z );
		m_Vertex[3].pos = D3DXVECTOR3( AFFINE_X(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1, 1), AFFINE_Y(Pos.x-Scale.x/2,Pos.y-Scale.y/2,Scale.x,Scale.y,fRot, 1, 1), Pos.z );
	}
}

void CObject2D::SetVertexColor( const D3DCOLOR Color ){
	
	// 頂点カラーの設定( 0 ～ 255 )
	m_Vertex[0].col = Color;
	m_Vertex[1].col = Color;
	m_Vertex[2].col = Color;
	m_Vertex[3].col = Color;
}

// テクスチャアニメーションするなら
void CObject2D::SetVertexTexture( const D3DXVECTOR2 Pattern ){

	// Textureの設定
	m_Vertex[0].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
	m_Vertex[1].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
	m_Vertex[2].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
	m_Vertex[3].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
}

void CObject2D::MakeVertexPolygon(){
	// rhwの設定( 1.0固定 )
	m_Vertex[0].rhw =  
	m_Vertex[1].rhw =   
	m_Vertex[2].rhw =  
	m_Vertex[3].rhw =  1.0f;

	// 頂点カラーの設定( 0 ～ 255 )
	m_Vertex[0].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	m_Vertex[1].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	m_Vertex[2].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );
	m_Vertex[3].col = D3DCOLOR_RGBA( 255, 255, 255, 255 );

	// テクスチャ座標
	m_Vertex[0].tex = D3DXVECTOR2( 0.0f, 0.0f );
	m_Vertex[1].tex = D3DXVECTOR2( 1.0f, 0.0f );
	m_Vertex[2].tex = D3DXVECTOR2( 0.0f, 1.0f );
	m_Vertex[3].tex = D3DXVECTOR2( 1.0f, 1.0f );
}

// セッター
void CObject2D::SetFileName( const std::wstring& filename ){
	m_FileName = filename;

	// 読み込み実行
	m_pTextureManager->LoadTexture(m_FileName);
}

void CObject2D::ChangeAlpha(float fAlpha) {
	
	int nAlpha = (int)(fAlpha * 255);
	ChangeAlpha(nAlpha);
}

void CObject2D::ChangeAlpha(int nAlpha) {
	
	D3DXCOLOR ChangeColor = D3DCOLOR_ARGB(nAlpha, 0, 0, 0);
	for(int i = 0; i < 4; i++) {
		m_Vertex[i].col += ChangeColor;
	}
}