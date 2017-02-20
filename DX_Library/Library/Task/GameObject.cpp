//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_//_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.cpp]
// author : 大洞祥太
// 
// 概要 : 全てのゲームオブジェクトの親クラス
//		  ObjectTypeに3DModel,3DPolygon,2D,Camera,Light,Particle2D,Particle3Dがある。
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

// ---- 再初期化
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

// ---- 更新前準備
void GameObject::Preparation(){
	m_Transform.OldPosition = m_Transform.Position;
	m_Transform.OldRotation = m_Transform.Rotation;
	m_Transform.OldSize = m_Transform.Size;

	m_Transform.MoveAmount = D3DXVECTOR3_ZERO;
	m_Transform.RotationAmount = D3DXVECTOR3_ZERO;
	m_Transform.SizeAmount = D3DXVECTOR3_ZERO;
}

// ---- ゲッター関数	

// 特定の子オブジェクトを取得
GameObject* GameObject::FindChild(const std::string Name){
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() )
			return *Ite;
	return nullptr;
}

// 特定の子オブジェクト全てを取得
std::list<GameObject*> GameObject::FindChildAll(const std::string Name){	
	std::list<GameObject*> findchild;
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		if( Name == (*Ite)->GetName() ) findchild.push_back(*Ite);
	return findchild; 
}

// ---- セッター関数

// オブジェクトにメッセージを送る
void GameObject::SendForMessage(std::string msg){ 
	m_Message = msg;
}	

// オブジェクトを移動
void GameObject::Move(D3DXVECTOR3 move){
	m_Transform.Position += move;
	m_Transform.MoveAmount = move;
	
	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Move(move);
}

// オブジェクトを回転
void GameObject::Rotation(D3DXVECTOR3 rot){
	m_Transform.Rotation += rot;
	m_Transform.RotationAmount = rot;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->Rotation(rot);
}

// オブジェクトの大きさを変更
void GameObject::SizeChange(D3DXVECTOR3 size){
	m_Transform.Size += size;
	m_Transform.SizeAmount = size;

	// Collision範囲変更 (基準値となるBaseに変更後のスケールを掛けた値を新たな当たり範囲として指定)
	D3DXVECTOR3 basesize = m_Transform.Size;
	m_Collision.CollisionCube = D3DXVECTOR3( m_BaseCube.x*basesize.x, m_BaseCube.y*basesize.y, m_BaseCube.z*basesize.z );
	m_Collision.fCollisionCircle = m_fBaseCircle*basesize.x; // 球なので、Scaleは全て同じなはず

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->SizeChange(size);
}

// オブジェクトの大きさを変更（個々に拡大）
void GameObject::ScaleChange(D3DXVECTOR3 scale){
	
	D3DXVECTOR3 temp = m_Transform.Size;
	m_Transform.Size.x *= scale.x;
	m_Transform.Size.y *= scale.y;
	m_Transform.Size.z *= scale.z;
	m_Transform.SizeAmount = m_Transform.Size - temp;

	// Collision範囲変更 (基準値となるBaseに変更後のスケールを掛けた値を新たな当たり範囲として指定)
	D3DXVECTOR3 size = m_Transform.Size;
	m_Collision.CollisionCube = D3DXVECTOR3( m_BaseCube.x*size.x, m_BaseCube.y*size.y, m_BaseCube.z*size.z );
	m_Collision.fCollisionCircle = m_fBaseCircle*size.x; // 球なので、Scaleは全て同じなはず
	
	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ScaleChange(scale);
}

// オブジェクトの大きさを変更（全て統一で拡大）
void GameObject::ScaleChange(float scale){
	
	D3DXVECTOR3 temp = m_Transform.Size;
	m_Transform.Size *= scale;
	m_Transform.SizeAmount = m_Transform.Size - temp;

	// Collision範囲変更 (基準値となるBaseに変更後のスケールを掛けた値を新たな当たり範囲として指定)
	D3DXVECTOR3 size = m_Transform.Size;
	m_Collision.CollisionCube = D3DXVECTOR3( m_BaseCube.x*size.x, m_BaseCube.y*size.y, m_BaseCube.z*size.z );
	m_Collision.fCollisionCircle = m_fBaseCircle*size.x; // 球なので、Scaleは全て同じなはず

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ScaleChange(scale);
}

// 移動したのを戻す
void GameObject::ReturnMove() {
	m_Transform.Position -= m_Transform.MoveAmount;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMove();
}

// 移動したのを戻す
void GameObject::ReturnMoveX() {
	m_Transform.Position.x -= m_Transform.MoveAmount.x;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveX();
}

// 移動したのを戻す
void GameObject::ReturnMoveY() {
	m_Transform.Position.y -= m_Transform.MoveAmount.y;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveY();
}

// 移動したのを戻す
void GameObject::ReturnMoveZ() {
	m_Transform.Position.z -= m_Transform.MoveAmount.z;

	// 子にも反映 
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnMoveZ();
}

// 回転したのを戻す 
void GameObject::ReturnRot() {
	m_Transform.Rotation -= m_Transform.RotationAmount;

	// 子にも反映 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnRot();
}

// 拡大したのを戻す
void GameObject::ReturnSize() {
	m_Transform.Size -= m_Transform.SizeAmount;

	// 子にも反映 
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ReturnSize();
}

// オブジェクトを自由に破壊できなくする
void GameObject::BanDestroy(){ 
	m_bDestroy = false;
}

// ライフを変動
void GameObject::SetLife( int nLife ) {
	m_nLife += nLife;
	if( m_nLife < 0 )
		m_nLife = 0;
}

// アクティブ状態を変更
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

	// 変更可なので変更
	m_bActive = m_bUpdate = bFlg;
	
	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ ) 
		(*Ite)->SetActive(bFlg);
}

// 更新フラグ変更
void GameObject::SetUpdateFlg(bool bFlg) {

	// object自体が停止中なので変更できない
	if(!m_bActive)
		return;
	
	if(m_bNotChangeUpdate)
		return;

	m_bUpdate = bFlg;

	for( auto Ite =  m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->SetUpdateFlg(bFlg);
}

// 親子関係を設定
GameObject* GameObject::SetParent(GameObject* Parent){ 
	m_Parent = Parent; // 親に設定
	Parent->GetChild()->push_back(this); // このオブジェクトをParentの子に設定
	return Parent;
}

// 全て解除
void GameObject::DetachParent() {

	if(!m_Parent)
		return;

	std::list<GameObject*>* m_ParentChild = m_Parent->GetChild();
	m_ParentChild->remove(this);
	m_Parent = nullptr;
}

// 当たり判定関係セッター
void GameObject::SetCollisionCubeSize( D3DXVECTOR3 Size ) {
	
	D3DXVECTOR3 size = m_Transform.Size;

	// サイズを格納
	m_Collision.CollisionCube = Size;
	m_BaseCube =  D3DXVECTOR3( Size.x/size.x, Size.y/size.y, Size.z/size.z );
}

void GameObject::SetCollisionCircleSize( float size ) { // 直径を格納
	// 直径を格納
	m_Collision.fCollisionCircle = size;
	m_fBaseCircle = size/m_Transform.Size.x;

	// OBBとの当たり判定で必要
	if(m_Collision.CollisionCube == D3DXVECTOR3_ZERO) {
		float fCubeSize = size*0.85f;
		SetCollisionCubeSize( D3DXVECTOR3( fCubeSize,fCubeSize,fCubeSize ) );
	}
}

// 例外チェック
void GameObject::ExceptionCheck(){
	
	D3DXVECTOR3 Rot = m_Transform.Rotation;

	// 角度の例外チェック
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

	// 子がいれば子にも実施
	for( auto Ite = m_Child.begin(); Ite != m_Child.end(); Ite++ )
		(*Ite)->ExceptionCheck();
}

// コリジョン処理(Unityのシステムを実装)
void GameObject::OnCollision(GameObject* pObj, bool bOnCollision) {

	// 対象との情報を取得
	auto ColObj = m_Collision.OnCollision.find(pObj);

	// 初めて当たっていた場合、新規に登録
	if(ColObj == m_Collision.OnCollision.end()) {
		m_Collision.OnCollision.insert(std::make_pair(pObj, false));
		ColObj = m_Collision.OnCollision.find(pObj);
	}

	// 当たっていない
	if(!ColObj->second && !bOnCollision) {
		
	}

	// 当たり中
	else if(ColObj->second && bOnCollision) {
		OnCollisionStay(pObj);
	}

	// 当たり始め
	else if(!ColObj->second && bOnCollision) {
		OnCollisionEnter(pObj);
	}

	// 当たり終わり
	else if(ColObj->second && !bOnCollision) {
		OnCollisionExit(pObj);
	}
	
	ColObj->second = bOnCollision;
}

// コリジョン判定取得
bool GameObject::GetOnCollisionFlg(GameObject* pObj) {
	auto Ite = m_Collision.OnCollision.find(pObj);

	if(Ite != m_Collision.OnCollision.end()) {
		return Ite->second;
	}

	// そもそも見つからない
	return false;
}

void GameObject::SetCollisionFlg(bool bFlg){
	m_Collision.bCollision = bFlg;
}
