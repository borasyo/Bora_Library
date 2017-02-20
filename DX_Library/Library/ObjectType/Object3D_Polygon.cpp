//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D_Polygon.h]
// author : �哴�ˑ�
// 
// GameObject��3DPolygon�I�u�W�F�N�g�̏ꍇ�A�������������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Object3D_Polygon.h"

CObject3DPolygon::CObject3DPolygon():m_bBillboard(true)
									,m_Divide(D3DXVECTOR3_ONE) {
	// �f�o�C�X�擾
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// �}�l�[�W���[�擾
	m_pTextureManager = CTextureManager::Create();
	
	// ���_���̍쐬
	MakeVertexPolygon();
	
	// �F�̓f�t�H���g�ɏ�����
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
	
	// �s��錾
	D3DXMATRIX mtxTranslate, mtxRotation, mtxScale;
 	
	// �X�P�[���Z�b�g
	D3DXMatrixScaling( &mtxScale, Size.x, Size.y, Size.z );
	D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxScale);

	// ��]�Z�b�g���܂�
	// �r���{�[�h�Ȃ�
	if( m_bBillboard ) { 

		// ���W�X�V
		SetVertexBillBoard(Size);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &m_mtxWorld );
		
		// �t�s������߂�
		D3DXMATRIX mtxView;
		m_pD3DDevice->GetTransform( D3DTS_VIEW, &mtxView);
		D3DXMatrixInverse( &m_mtxWorld, NULL, &mtxView );

		m_mtxWorld._41 = 0.0f;
		m_mtxWorld._42 = 0.0f;
		m_mtxWorld._43 = 0.0f;
	}
	// �ʏ�Ȃ�
	else {
		// ���W�X�V
		SetVertexPolygon(Size);

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity( &m_mtxWorld );
		
		// ��]�Z�b�g
		D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotation);
	}

	// �|�W�V�����Z�b�g
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
	
	// ���C�e�B���O�𖳌��ɂ���
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	// ����transform���ύX����Ă���Ȃ�΃}�g���N�X�X�V
	D3DXMATRIX mtxView;
	m_pD3DDevice->GetTransform( D3DTS_VIEW, &mtxView);
	if( *(pObj->GetOldRotation()) != Rot || 
		*(pObj->GetOldSize()) != Size || 
		mtxView != m_OldView ) {

		// �X�V
		SetMatrix(Pos,Size,Rot);
	}
	else if (*(pObj->GetOldPosition()) != Pos ) {
		SetOffset(Pos);
	}
		
	m_OldView = mtxView;
	
	// �`��
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );
	
	switch (m_Synthetic) {
	case eSubtractive:		// ���Z����
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ���C�e�B���O���Ȃ�
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	case eAdditive:			// ���Z����
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ���C�e�B���O���Ȃ�
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	default:
		break;
	}
	
	m_pD3DDevice->SetFVF( FVF_VERTEX_3D ); // ���_�t�H�[�}�b�g�̐ݒ�
	m_pD3DDevice->SetTexture( 0, m_pTextureManager->LoadTexture(m_FileName) ); // �e�N�X�`���̃Z�b�g
	m_pD3DDevice->DrawPrimitiveUP( D3DPT_TRIANGLESTRIP, NUM_POLYGON, m_Vertex, sizeof( VERTEX_3D ) ); // �|���S���̕`��

	m_pD3DDevice->SetTexture( 0, nullptr ); // �e�N�X�`����񏉊���
	
	// ���C�e�B���O��L���ɂ���
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	
	// �ʏ�u�����h
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z�o�b�t�@�X�V��L����
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);				// ���C�e�B���O����
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

HRESULT CObject3DPolygon::MakeVertexPolygon(){

	if( m_bBillboard ) {

		// �e�N�X�`�����W
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	
		// �@���̐ݒ�
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 0.0f, -1.0f );
	} 
	else {

		// �e�N�X�`�����W
		m_Vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		m_Vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		m_Vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		m_Vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		// �@���̐ݒ�
		m_Vertex[0].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[1].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[2].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		m_Vertex[3].normal = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	}

	return S_OK;
}

void CObject3DPolygon::SetVertexPolygon( const D3DXVECTOR3 Scale ){
	
	// ���_���W�̐ݒ�
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[1].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f,  Scale.z/2 );
	m_Vertex[2].vtx = D3DXVECTOR3( -Scale.x/2, 0.0f, -Scale.z/2 );
	m_Vertex[3].vtx = D3DXVECTOR3(  Scale.x/2, 0.0f, -Scale.z/2 );
}

void CObject3DPolygon::SetVertexBillBoard( const D3DXVECTOR3 Scale ){
	
	// ���_���W�̐ݒ�
	m_Vertex[0].vtx = D3DXVECTOR3( -Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[1].vtx = D3DXVECTOR3( -Scale.x/2 , +Scale.y/2 , 0.0f );
	m_Vertex[2].vtx = D3DXVECTOR3( +Scale.x/2 , -Scale.y/2 , 0.0f );
	m_Vertex[3].vtx = D3DXVECTOR3( +Scale.x/2 , +Scale.y/2 , 0.0f );
}

void CObject3DPolygon::SetVertexColor( const D3DCOLOR Color ){
	
	// ���_�J���[�̐ݒ�( 0 �` 255 )
	m_Vertex[0].diffuse = Color;
	m_Vertex[1].diffuse = Color;
	m_Vertex[2].diffuse = Color;
	m_Vertex[3].diffuse = Color;
}

// �@���ς������Ȃ�
void CObject3DPolygon::SetVertexNormal( const D3DXVECTOR3 Normal ){
	
	// �@���̐ݒ�
	m_Vertex[0].normal = Normal;
	m_Vertex[1].normal = Normal;
	m_Vertex[2].normal = Normal;
	m_Vertex[3].normal = Normal;
}

// �e�N�X�`���A�j���[�V��������Ȃ�
void CObject3DPolygon::SetVertexTexture( const D3DXVECTOR3 Pattern ){

	if( m_bBillboard ) {
		// Texture�̐ݒ�
		m_Vertex[0].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
		m_Vertex[1].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
		m_Vertex[2].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
		m_Vertex[3].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
	}
	else {
		// Texture�̐ݒ�
		m_Vertex[0].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
		m_Vertex[1].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, Pattern.y * 1.0f/m_Divide.y);
		m_Vertex[2].tex = D3DXVECTOR2(Pattern.x * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
		m_Vertex[3].tex = D3DXVECTOR2((Pattern.x + 1) * 1.0f/m_Divide.x, (Pattern.y + 1) * 1.0f/m_Divide.y);
	}
}

// �Q�b�^�[
const LPCWSTR CObject3DPolygon::GetFileName(){
	return m_FileName;
}

// �Z�b�^�[
void CObject3DPolygon::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;
	
	// �ǂݍ��ݎ��s
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