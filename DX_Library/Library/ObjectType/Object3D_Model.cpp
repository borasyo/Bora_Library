
#include "Object3D_Model.h"
#include "../DirectX/Direct3D.h"

// -- ���̒�`
bool CObject3DModel::m_bColDraw = false;

CObject3DModel::CObject3DModel(){
	// �f�o�C�X�擾
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	// �}�l�[�W���[�擾
	m_pModelManager = CModelManager::Create();

	// ���O������
	m_FileName = nullptr;

	// ��l���i�[
	m_fAnimSpeed = 1.0f;

	// �A�j���[�V�������邩
	m_bAnim = true;
	
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxWorld );

	// �}�e���A���J���[������
	m_MaterialColor = D3DXCOLOR(1,1,1,1);

	//m_bColDraw = true;
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();
	m_OldColSize = D3DXVECTOR3_ZERO;
	
	// ���E�\���p���b�V������
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

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity( &m_mtxWorld );

	// �X�P�[���Z�b�g
	D3DXMatrixScaling( &mtxSize, Size.x, Size.y, Size.z );
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxSize);

	// ��]�Z�b�g
	D3DXMatrixRotationYawPitchRoll( &mtxRotation, Rot.y, Rot.x, Rot.z );
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRotation);
	
	// �|�W�V�����Z�b�g
	D3DXMatrixTranslation( &mtxTranslate, Pos.x, Pos.y, Pos.z );
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
}

void CObject3DModel::SetOffset( const D3DXVECTOR3 Pos ) {

	m_mtxWorld._41 = Pos.x;
	m_mtxWorld._42 = Pos.y;
	m_mtxWorld._43 = Pos.z;
}

// �`��֐�
void CObject3DModel::Draw( GameObject* pObj, const bool bShadow ) {
	
	D3DXVECTOR3 Pos = *(pObj->GetPosition());
	D3DXVECTOR3 Size = *(pObj->GetSize());
	D3DXVECTOR3 Rot = *(pObj->GetRotation());

	Draw(pObj, Pos, Size, Rot, bShadow);
}

void CObject3DModel::Draw( GameObject* pObj, const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const D3DXVECTOR3 Rot, const bool bShadow ) {

	// �A�j���[�V��������̂Ŏ��ԍX�V
	if( m_bAnim && m_AnimationManager.GetAnimationController() )
		UpdateAnim();

	// ����transform���ύX����Ă���Ȃ�΃}�g���N�X�X�V
	if( *(pObj->GetOldRotation()) != Rot || 
		*(pObj->GetOldSize())     != Size ) {

		SetMatrix(Pos,Size,Rot);
	} 
	else if (*(pObj->GetOldPosition()) != Pos ) {
		SetOffset(Pos);
	}

	// �`����Z�b�g
	m_pD3DDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );
	
	// ���f���`��
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
		// ��]�Z�b�g
		D3DXMATRIX mtxRotation;
		D3DXMatrixRotationYawPitchRoll( &mtxRotation, pObj->GetRotation()->y, pObj->GetRotation()->x, pObj->GetRotation()->z );
		D3DXMatrixMultiply(&mtx, &mtx, &mtxRotation);
	}

	mtx._41 = m_mtxWorld._41;
	mtx._42 = m_mtxWorld._42;
	mtx._43 = m_mtxWorld._43;

	//	�R���W�����̌`�ɍ��킹�ĕ`��؂�ւ�
	if(pObj->GetCollisionCircleSize() > 0.0f) {
		DrawSphere(pObj, mtx, Color);
	} else if(*(pObj->GetRotation()) > D3DXVECTOR3_ZERO) {
		DrawOBB(pObj, mtx, Color);
	} else {
		DrawAABB(pObj, mtx, Color);
	}
	
	//m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// �Q�b�^�[
const LPCWSTR CObject3DModel::GetFileName(){
	return m_FileName;
}

// �Z�b�^�[
void CObject3DModel::SetFileName( const LPCWSTR& filename ){
	m_FileName = filename;

	// �t�@�C�������w�肳�ꂽ���A�}�b�v�ɒǉ�������
	m_pModelManager->RenderModel( &m_mtxWorld, m_FileName, false, m_MaterialColor );
}

void CObject3DModel::SetMaterialColor( const D3DXCOLOR Color ){
	
	m_MaterialColor = Color;
	//CModel* pModel = m_pModelManager->GetModel( m_FileName );
	//pModel->SetMaterialColor( Color );
}

// �R�s�[�����A�j���[�V�����R���g���[���[���擾���A�ۑ�
void CObject3DModel::SetAnimationController(){

	// ���O��������Ȃ��̂Ƀ��f���̃A�j���[�V�����R���g���[���[���擾�ł���킯�Ȃ�
	if( !m_FileName )
		return;

	LPD3DXANIMATIONCONTROLLER pCopyAnimationController = m_pModelManager->GetModel( m_FileName )->GetMainAnimationController();

	// �擾���s
	if( !pCopyAnimationController )
		return;

	// �擾����
	m_AnimationManager.SetAnimationController( pCopyAnimationController );
}

bool CObject3DModel::UpdateAnim(){
	
	// �A�j���[�V�����R���g���[���[�������āA�A�j���[�V�������Đ����Ă��悢�Ȃ�
	//if( m_AnimationManager.GetAnimationController() || m_bAnim )
	return m_AnimationManager.AdvanceTime( m_fAnimSpeed );

	//return false;
}

void CObject3DModel::SetAnimSpeed( const float fAnimSpeed ) {

	if( !m_bAnim )
		return;

	// �w�肵���X�s�[�h�Ɋi�[
	m_fAnimSpeed = fAnimSpeed;
}

// �A�j���[�V�������邩�ǂ����̃t���O�𔽓]����
void CObject3DModel::SetAnimFlg( const bool bFlg ){
	m_bAnim = bFlg;
}

// �A�j���[�V�����R���g���[���[���擾
CAnimationController* CObject3DModel::GetAnimationManager() {
	return &m_AnimationManager;
}

D3DXMATRIX* CObject3DModel::GetBoneMatrixWithName(const LPSTR Name, eBonePlace BonePlace) {
	return m_pModelManager->GetModel(m_FileName)->GetBoneMatrixWithName(Name,BonePlace);
}

// ---- Debug

void CObject3DModel::SetMesh(GameObject* pObj) {
	
	// ���E�\���p���b�V���Đ���
	D3DXVECTOR3 Cube = pObj->GetCollisionCubePlusSize();
	D3DXCreateBox(m_pD3DDevice, Cube.x, Cube.y, Cube.z, &m_pBBox, NULL);
	D3DXCreateSphere(m_pD3DDevice, pObj->GetCollisionCircleSize() / 2.0f, 16, 8, &m_pBSphere, NULL);
}
	
void CObject3DModel::DrawOBB(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color) {
	
	// ���[���h�}�g���b�N�X�ݒ�
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	// �}�e���A���ݒ�
	m_pD3DDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = Color;
	m_pD3DDevice->SetMaterial(&mtrl);

	// �`��
	m_pBBox->DrawSubset(0);
}

void CObject3DModel::DrawAABB(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color) {
	
	// ���[���h�}�g���b�N�X�ݒ�
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	// �}�e���A���ݒ�
	m_pD3DDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = Color;
	m_pD3DDevice->SetMaterial(&mtrl);

	// �`��
	m_pBBox->DrawSubset(0);
}

void CObject3DModel::DrawSphere(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color) {

	// ���[���h�}�g���b�N�X�ݒ�
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

	// �}�e���A���ݒ�
	m_pD3DDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = Color;
	m_pD3DDevice->SetMaterial(&mtrl);

	// �`��
	m_pBSphere->DrawSubset(0);
}

//#endif
