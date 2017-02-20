//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.cpp]
// author : �哴�ˑ�
// 
// �T�v : �S�ẴQ�[���I�u�W�F�N�g�̐e�N���X
//		  ObjectType��3DModel,3DPolygon,2D,Camera,Light,Particle2D,Particle3D������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/_/_/_/

#include "GameObject.h"
#include <math.h>
#include "../Function/Define.h"

#include "../DirectX/DirectInputManager.h"
#include "../DirectX/Direct3D.h"

GameObject::GameObject()
	:m_nLife(1)
	,m_bActive(true)
	,m_bUpdate(true)
	,m_bDestroy(true)
	,m_Parent(nullptr)
	,m_bNotChangeActive(false)
	,m_bNotChangeUpdate(false)
	//,m_nSortingLayer(0)
	,m_nSortingLayer(0)
	,m_nOrderinLayer(0) 
{
		
	m_Collision.CollisionCube = D3DXVECTOR3_ZERO;
	m_Collision.fCollisionCircle = 0.0f;
	m_Collision.bCollision = true;
//	m_Collision.bOnCollision = false; 
		
	m_Transform.Position = D3DXVECTOR3_ZERO;
	m_Transform.Rotation  = D3DXVECTOR3_ZERO;
	m_Transform.Size = D3DXVECTOR3_ONE;
	m_Transform.MoveAmount = D3DXVECTOR3_ZERO;
	m_Transform.RotationAmount = D3DXVECTOR3_ZERO;
	m_Transform.SizeAmount = D3DXVECTOR3_ZERO;
	m_Transform.OldPosition = m_Transform.Position;
	m_Transform.OldRotation  = m_Transform.Rotation;
	m_Transform.OldSize = m_Transform.Size;
}

GameObject::~GameObject(){

}

void GameObject::Awake() {

}

bool GameObject::Start() {

	return true;
}

void GameObject::FastUpdate(){
	
}

void GameObject::Update(){

}

void GameObject::LateUpdate(){

}

void GameObject::FastDraw(){

}

void GameObject::Draw(){

}

void GameObject::LateDraw(){

}

// ---- �ď�����
void GameObject::ReInit(){
	
	m_nLife = 1;
	m_bActive = true;
	m_bUpdate = true;

	m_Collision.CollisionCube = D3DXVECTOR3_ZERO;
	m_Collision.fCollisionCircle = 0.0f;
	m_Collision.bCollision = true;
	//m_Collision.bOnCollision = false; 
	m_BaseCube = D3DXVECTOR3_ZERO;
		
	m_Transform.Position = D3DXVECTOR3_ZERO;
	m_Transform.Rotation  = D3DXVECTOR3_ZERO;
	m_Transform.Size = D3DXVECTOR3_ONE;
	m_Transform.MoveAmount = D3DXVECTOR3_ZERO;
	m_Transform.RotationAmount = D3DXVECTOR3_ZERO;
	m_Transform.SizeAmount = D3DXVECTOR3_ZERO;
	m_Transform.OldPosition = m_Transform.Position;
	m_Transform.OldRotation  = m_Transform.Rotation;
	m_Transform.OldSize = m_Transform.Size;
}

// ---- �X�V�O����
void GameObject::Preparation(){
	m_Transform.OldPosition = m_Transform.Position;
	m_Transform.OldRotation = m_Transform.Rotation;
	m_Transform.OldSize = m_Transform.Size;

	m_Transform.MoveAmount = D3DXVECTOR3_ZERO;
	m_Transform.RotationAmount = D3DXVECTOR3_ZERO;
	m_Transform.SizeAmount = D3DXVECTOR3_ZERO;
}

// ---- �Q�b�^�[�֐�	

// ����̎q�I�u�W�F�N�g���擾
GameObject* GameObject::FindChild(const std::string Name){
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() )
			return *Ite;
	return nullptr;
}

// ����̎q�I�u�W�F�N�g�S�Ă��擾
std::list<GameObject*> GameObject::FindChildAll(const std::string Name){	
	std::list<GameObject*> findchild;
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() ) findchild.push_back(*Ite);
	return findchild; 
}

// ---- �Z�b�^�[�֐�

// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗂�
void GameObject::SendForMessage(std::string msg){ 
	m_Message = msg;
}	

// �I�u�W�F�N�g���ړ�
void GameObject::Move(D3DXVECTOR3 move){
	m_Transform.Position += move;
	m_Transform.MoveAmount = move;
	
	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Move(move);
}

// �I�u�W�F�N�g����]
void GameObject::Rotation(D3DXVECTOR3 rot){
	m_Transform.Rotation += rot;
	m_Transform.RotationAmount = rot;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Rotation(rot);
}

// �I�u�W�F�N�g�̑傫����ύX
void GameObject::SizeChange(D3DXVECTOR3 size){
	m_Transform.Size += size;
	m_Transform.SizeAmount = size;

	// Collision�͈͕ύX (��l�ƂȂ�Base�ɕύX��̃X�P�[�����|�����l��V���ȓ�����͈͂Ƃ��Ďw��)
	D3DXVECTOR3 basesize = m_Transform.Size;
	m_Collision.CollisionCube = D3DXVECTOR3( m_BaseCube.x*basesize.x, m_BaseCube.y*basesize.y, m_BaseCube.z*basesize.z );
	m_Collision.fCollisionCircle = m_fBaseCircle*basesize.x; // ���Ȃ̂ŁAScale�͑S�ē����Ȃ͂�

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->SizeChange(size);
}

// �I�u�W�F�N�g�̑傫����ύX�i�X�Ɋg��j
void GameObject::ScaleChange(D3DXVECTOR3 scale){
	
	D3DXVECTOR3 temp = m_Transform.Size;
	m_Transform.Size.x *= scale.x;
	m_Transform.Size.y *= scale.y;
	m_Transform.Size.z *= scale.z;
	m_Transform.SizeAmount = m_Transform.Size - temp;

	// Collision�͈͕ύX (��l�ƂȂ�Base�ɕύX��̃X�P�[�����|�����l��V���ȓ�����͈͂Ƃ��Ďw��)
	D3DXVECTOR3 size = m_Transform.Size;
	m_Collision.CollisionCube = D3DXVECTOR3( m_BaseCube.x*size.x, m_BaseCube.y*size.y, m_BaseCube.z*size.z );
	m_Collision.fCollisionCircle = m_fBaseCircle*size.x; // ���Ȃ̂ŁAScale�͑S�ē����Ȃ͂�
	
	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ScaleChange(scale);
}

// �I�u�W�F�N�g�̑傫����ύX�i�S�ē���Ŋg��j
void GameObject::ScaleChange(float scale){
	
	D3DXVECTOR3 temp = m_Transform.Size;
	m_Transform.Size *= scale;
	m_Transform.SizeAmount = m_Transform.Size - temp;

	// Collision�͈͕ύX (��l�ƂȂ�Base�ɕύX��̃X�P�[�����|�����l��V���ȓ�����͈͂Ƃ��Ďw��)
	D3DXVECTOR3 size = m_Transform.Size;
	m_Collision.CollisionCube = D3DXVECTOR3( m_BaseCube.x*size.x, m_BaseCube.y*size.y, m_BaseCube.z*size.z );
	m_Collision.fCollisionCircle = m_fBaseCircle*size.x; // ���Ȃ̂ŁAScale�͑S�ē����Ȃ͂�

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ScaleChange(scale);
}

// �ړ������̂�߂�
void GameObject::ReturnMove() {
	m_Transform.Position -= m_Transform.MoveAmount;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMove();
}

// �ړ������̂�߂�
void GameObject::ReturnMoveX() {
	m_Transform.Position.x -= m_Transform.MoveAmount.x;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveX();
}

// �ړ������̂�߂�
void GameObject::ReturnMoveY() {
	m_Transform.Position.y -= m_Transform.MoveAmount.y;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveY();
}

// �ړ������̂�߂�
void GameObject::ReturnMoveZ() {
	m_Transform.Position.z -= m_Transform.MoveAmount.z;

	// �q�ɂ����f 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveZ();
}

// ��]�����̂�߂� 
void GameObject::ReturnRot() {
	m_Transform.Rotation -= m_Transform.RotationAmount;

	// �q�ɂ����f 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnRot();
}

// �g�債���̂�߂�
void GameObject::ReturnSize() {
	m_Transform.Size -= m_Transform.SizeAmount;

	// �q�ɂ����f 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnSize();
}

// �I�u�W�F�N�g�����R�ɔj��ł��Ȃ�����
void GameObject::BanDestroy(){ 
	m_bDestroy = false;
}

// ���C�t��ϓ�
void GameObject::SetLife( int nLife ) {
	m_nLife += nLife;
	if( m_nLife < 0 )
		m_nLife = 0;
}

// �A�N�e�B�u��Ԃ�ύX
void GameObject::SetActive(bool bFlg) {

	if(m_bNotChangeActive)
		return;
	
	if(m_bActive != bFlg) {

		// Enable
		if(bFlg) {
			OnEnable();
		} 
		// Disable
		else {
			OnDisable();
		}
	}

	// �ύX�Ȃ̂ŕύX
	m_bActive = m_bUpdate = bFlg;
	
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ ) 
		(*Ite)->SetActive(bFlg);
}

// �X�V�t���O�ύX
void GameObject::SetUpdateFlg(bool bFlg) {

	// object���̂���~���Ȃ̂ŕύX�ł��Ȃ�
	if(!m_bActive)
		return;
	
	if(m_bNotChangeUpdate)
		return;

	m_bUpdate = bFlg;

	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->SetUpdateFlg(bFlg);
}

// �e�q�֌W��ݒ�
GameObject* GameObject::SetParent(GameObject* Parent){ 
	m_Parent = Parent; // �e�ɐݒ�
	Parent->GetChild()->push_back(this); // ���̃I�u�W�F�N�g��Parent�̎q�ɐݒ�
	return Parent;
}

// �S�ĉ���
void GameObject::DetachParent() {

	if(!m_Parent)
		return;

	std::list<GameObject*>* m_ParentChild = m_Parent->GetChild();
	m_ParentChild->remove(this);
	m_Parent = nullptr;
}

// �����蔻��֌W�Z�b�^�[
void GameObject::SetCollisionCubeSize( D3DXVECTOR3 Size ) {
	
	D3DXVECTOR3 size = m_Transform.Size;

	// �T�C�Y���i�[
	m_Collision.CollisionCube = Size;
	m_BaseCube =  D3DXVECTOR3( Size.x/size.x, Size.y/size.y, Size.z/size.z );
}

void GameObject::SetCollisionCircleSize( float size ) { // ���a���i�[
	// ���a���i�[
	m_Collision.fCollisionCircle = size;
	m_fBaseCircle = size/m_Transform.Size.x;

	// OBB�Ƃ̓����蔻��ŕK�v
	if(m_Collision.CollisionCube == D3DXVECTOR3_ZERO) {
		float fCubeSize = size*0.85f;
		SetCollisionCubeSize( D3DXVECTOR3( fCubeSize,fCubeSize,fCubeSize ) );
	}
}

// ��O�`�F�b�N
void GameObject::ExceptionCheck(){
	
	D3DXVECTOR3 Rot = m_Transform.Rotation;

	// �p�x�̗�O�`�F�b�N
	if( Rot.x < 0.0f )
		Rotation( D3DXVECTOR3( Pai*2.0f,0,0 ) );
	else if( Rot.x > Pai*2.0f )
		Rotation( D3DXVECTOR3( -Pai*2.0f,0,0 ) );
	if( Rot.y < 0.0f )
		Rotation( D3DXVECTOR3( 0,Pai*2.0f,0 ) );
	else if( Rot.y > Pai*2.0f )
		Rotation( D3DXVECTOR3( 0,-Pai*2.0f,0 ) );
	if( Rot.z < 0.0f )
		Rotation( D3DXVECTOR3( 0,0,Pai*2.0f ) );
	else if( Rot.z > Pai*2.0f )
		Rotation( D3DXVECTOR3( 0,0,-Pai*2.0f ) );

	// �q������Ύq�ɂ����{
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ExceptionCheck();
}

// �R���W��������(Unity�̃V�X�e��������)
void GameObject::OnCollision(GameObject* pObj, bool bOnCollision) {

	// �ΏۂƂ̏����擾
	auto ColObj = m_Collision.OnCollision.find(pObj);

	// ���߂ē������Ă����ꍇ�A�V�K�ɓo�^
	if(ColObj == m_Collision.OnCollision.end()) {
		m_Collision.OnCollision.insert(std::make_pair(pObj, false));
		ColObj = m_Collision.OnCollision.find(pObj);
	}

	// �������Ă��Ȃ�
	if(!ColObj->second && !bOnCollision) {
		
	}

	// �����蒆
	else if(ColObj->second && bOnCollision) {
		OnCollisionStay(pObj);
	}

	// ������n��
	else if(!ColObj->second && bOnCollision) {
		OnCollisionEnter(pObj);
	}

	// ������I���
	else if(ColObj->second && !bOnCollision) {
		OnCollisionExit(pObj);
	}
	
	ColObj->second = bOnCollision;
}

// �R���W��������擾
bool GameObject::GetOnCollisionFlg(GameObject* pObj) {
	auto Ite = m_Collision.OnCollision.find(pObj);

	if(Ite != m_Collision.OnCollision.end()) {
		return Ite->second;
	}

	// ��������������Ȃ�
	return false;
}

void GameObject::SetCollisionFlg(bool bFlg){
	m_Collision.bCollision = bFlg;
}
