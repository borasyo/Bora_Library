//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Collision2D.cpp]
// author : �哴�ˑ�
//
// ��GetCollisionCubePlusSize�͍�����W�n�ɂ����鎲�̃v���X�̌����̑傫��
// ��GetCollisionCubeMinusSize�͍�����W�n�ɂ����鎲�̃}�C�i�X�̌����̑傫��
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Collision2D.h"

// �_�Ɠ_
bool Collision2D::CollisionPointandPoint( GameObject* pPoint, GameObject* pPoint2 ) {

	if( !pPoint->GetCollisionFlg() || !pPoint2->GetCollisionFlg() ) {
		pPoint->OnCollision(pPoint2, false);
		pPoint2->OnCollision(pPoint, false);
		return false;
	}

	if( *(pPoint->GetPosition()) == *(pPoint2->GetPosition()) ) {
		pPoint->OnCollision(pPoint2, true);
		pPoint2->OnCollision(pPoint, true);
		return true;
	}
	
	pPoint->OnCollision(pPoint2, false);
	pPoint2->OnCollision(pPoint, false);
	return false;
}

// �_�Ɖ~
bool Collision2D::CollisionPointandCircle( GameObject* pPoint, GameObject* pCircle ){
	
	if( !pPoint->GetCollisionFlg() || !pCircle->GetCollisionFlg() ) {
		pPoint->OnCollision(pCircle, false);
		pCircle->OnCollision(pPoint, false);
		return false;
	}
	
	float fDistanceX = pCircle->GetPosition()->x - pPoint->GetPosition()->x;
	float fDistanceY = pCircle->GetPosition()->y - pPoint->GetPosition()->y;
	
	// 2�_�Ԃ̋������Q�̃I�u�W�F�N�g�̔��a�̍��v���߂���
	if( sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY ) <= pCircle->GetCollisionCircleSize() / 2.0f ) {
		pPoint->OnCollision(pCircle, true);
		pCircle->OnCollision(pPoint, true);
		return true;
	}
	
	pPoint->OnCollision(pCircle, false);
	pCircle->OnCollision(pPoint, false);
	return false;
}

// �~�Ɖ~
bool Collision2D::CollisionCircleandCircle( GameObject* pCircle, GameObject* pCircle2 ){
	
	if( !pCircle->GetCollisionFlg() || !pCircle2->GetCollisionFlg() ) {
		pCircle->OnCollision(pCircle2, false);
		pCircle2->OnCollision(pCircle, false);
		return false;
	}

	float fDistanceX = pCircle2->GetPosition()->x - pCircle->GetPosition()->x;
	float fDistanceY = pCircle2->GetPosition()->y - pCircle->GetPosition()->y;

	// 2�_�Ԃ̋������Q�̃I�u�W�F�N�g�̔��a�̍��v���߂���
	if( sqrt( fDistanceX*fDistanceX + fDistanceY*fDistanceY ) 
		<= pCircle->GetCollisionCircleSize() / 2.0f + pCircle2->GetCollisionCircleSize() / 2.0f ) {
		pCircle->OnCollision(pCircle2, true);
		pCircle2->OnCollision(pCircle, true);
		return true;
	}
	
	pCircle->OnCollision(pCircle2, false);
	pCircle2->OnCollision(pCircle, false);
	return false;
}

// ���Ɠ_
bool Collision2D::CollisionCubeandPoint( GameObject* pCube, GameObject* pPoint ) {
	
	if( !pPoint->GetCollisionFlg() || !pCube->GetCollisionFlg() ) {
		pCube->OnCollision(pPoint, false);
		pPoint->OnCollision(pCube, false);
		return false;
	}

	// �����ɓ_�����邩
	D3DXVECTOR3 ppos = *(pPoint->GetPosition());
	D3DXVECTOR3 cpos = *(pCube->GetPosition());
	D3DXVECTOR3 ccolplus = pCube->GetCollisionCubePlusSize() / 2.0f;
	D3DXVECTOR3 ccolminus = pCube->GetCollisionCubeMinusSize() / 2.0f;
	if( ppos.x < cpos.x + ccolplus.x  &&
		ppos.x > cpos.x + ccolminus.x && 
		ppos.y < cpos.y + ccolplus.y  &&
		ppos.y > cpos.y + ccolminus.y ) 
	{
		pCube->OnCollision(pPoint, true);
		pPoint->OnCollision(pCube, true);
		return true;
	}
	
	pCube->OnCollision(pPoint, false);
	pPoint->OnCollision(pCube, false);
	return false;
}

// ���Ɣ�
bool Collision2D::CollisionCubeandCube( GameObject* pCube, GameObject* pCube2 ) {
	
	if( !pCube->GetCollisionFlg() || !pCube2->GetCollisionFlg() ) {
		pCube->OnCollision(pCube2, false);
		pCube2->OnCollision(pCube, false);
		return false;
	}
	
	// ���܂�ɉ����I�u�W�F�N�g�͔���O��
	float fDistanceX = abs(pCube2->GetPosition()->x - pCube->GetPosition()->x);
	float fDistanceY = abs(pCube2->GetPosition()->y - pCube->GetPosition()->y);
	
	D3DXVECTOR3 ccolplus[2] = {pCube->GetCollisionCubePlusSize()/2.0f, pCube2->GetCollisionCubePlusSize()/2.0f};
	//D3DXVECTOR3 ccolminus[2] = {pCube->GetCollisionCubeMinusSize()/2.0f, pCube2->GetCollisionCubeMinusSize()/2.0f};
	if( ccolplus[0].x + ccolplus[1].x >= fDistanceX && 
		ccolplus[0].y + ccolplus[1].y >= fDistanceY )  {
		pCube->OnCollision(pCube2, true);
		pCube2->OnCollision(pCube, true);
		return true;
	}

	pCube->OnCollision(pCube2, false);
	pCube2->OnCollision(pCube, false);
	return false;
}

// ���Ɖ~
bool Collision2D::CollisionCubeandCircle( GameObject* pCube, GameObject* pCircle ) {

	//return CollisionCubeandCube(pCube,pCircle); 

	if( !pCube->GetCollisionFlg() || !pCircle->GetCollisionFlg() ) {
		pCube->OnCollision(pCircle, false);
		pCircle->OnCollision(pCube, false);
		return false;
	}
	
	// ���܂�ɉ����I�u�W�F�N�g�͔���O��
	float fCircleSize = sinf(Pai/4.0f);
	float fDistanceX = abs(pCircle->GetPosition()->x - pCube->GetPosition()->x);
	float fDistanceY = abs(pCircle->GetPosition()->y - pCube->GetPosition()->y);
	
	D3DXVECTOR3 circle = D3DXVECTOR3(pCircle->GetCollisionCircleSize()/2.0f, pCircle->GetCollisionCircleSize()/2.0f, pCircle->GetCollisionCircleSize()/2.0f);
	D3DXVECTOR3 ccolplus[2] = {pCube->GetCollisionCubePlusSize()/2.0f, circle * fCircleSize};
	//D3DXVECTOR3 ccolminus[2] = {pCube->GetCollisionCubeMinusSize()/2.0f, -circle * fCircleSize};
	if( ccolplus[0].x + ccolplus[1].x >= fDistanceX && 
		ccolplus[0].y + ccolplus[1].y >= fDistanceY )  {
		pCube->OnCollision(pCircle, true);
		pCircle->OnCollision(pCube, true);
		return true;
	}

	pCube->OnCollision(pCircle, false);
	pCircle->OnCollision(pCube, false);
	return false;
}

// OBB��OBB�̓����蔻��
bool Collision2D::CollisionOBBandOBB( GameObject* pObb, GameObject* pObb2 ) {
	
	if( !pObb->GetCollisionFlg() || !pObb2->GetCollisionFlg() ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}

	// OBB������
	OBB Obb  = SetOBB( pObb  );
	OBB Obb2 = SetOBB( pObb2 );

	// �e�����x�N�g���̊m��
	D3DXVECTOR3 NAe1 = Obb.Vec[0], Ae1 = NAe1 * Obb.Length[0];
	D3DXVECTOR3 NAe2 = Obb.Vec[1], Ae2 = NAe2 * Obb.Length[1];
	D3DXVECTOR3 NAe3 = Obb.Vec[2], Ae3 = NAe3 * Obb.Length[2];
	D3DXVECTOR3 NBe1 = Obb2.Vec[0], Be1 = NBe1 * Obb2.Length[0];
	D3DXVECTOR3 NBe2 = Obb2.Vec[1], Be2 = NBe2 * Obb2.Length[1];
	D3DXVECTOR3 NBe3 = Obb2.Vec[2], Be3 = NBe3 * Obb2.Length[2];
	D3DXVECTOR3 Interval = Obb.Pos - Obb2.Pos;

	// ������ : Ae1
	FLOAT rA = D3DXVec3Length( &Ae1 );
	FLOAT rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	FLOAT L = fabs(D3DXVec3Dot( &Interval, &NAe1 ));
	if( L > rA + rB )  {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}

	// ������ : Ae2
	rA = D3DXVec3Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NAe2 ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : Ae3
	rA = D3DXVec3Length( &Ae3 );
	rB = LenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NAe3 ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be1 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe1 ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe2 ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : Be3
	rA = LenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &NBe3 ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross( &Cross, &NAe1, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C12
	D3DXVec3Cross( &Cross, &NAe1, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C13
	D3DXVec3Cross( &Cross, &NAe1, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C21
	D3DXVec3Cross( &Cross, &NAe2, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C22
	D3DXVec3Cross( &Cross, &NAe2, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C23
	D3DXVec3Cross( &Cross, &NAe2, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C31
	D3DXVec3Cross( &Cross, &NAe3, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C32
	D3DXVec3Cross( &Cross, &NAe3, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// ������ : C33
	D3DXVec3Cross( &Cross, &NAe3, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs(D3DXVec3Dot( &Interval, &Cross ));
	if( L > rA + rB ) {
		pObb->OnCollision(pObb2, false);
		pObb2->OnCollision(pObb, false);
		return false;
	}
	
	// �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
	pObb->OnCollision(pObb2, true);
	pObb2->OnCollision(pObb, true);
	return true;
}


// �������ɓ��e���ꂽ���������瓊�e���������Z�o
FLOAT Collision2D::LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 )
{
   // 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
   // ������Sep�͕W��������Ă��邱��
   FLOAT r1 = fabs(D3DXVec3Dot( Sep, e1 ));
   FLOAT r2 = fabs(D3DXVec3Dot( Sep, e2 ));
   FLOAT r3 = e3 ? (fabs(D3DXVec3Dot( Sep, e3 ))) : 0;
   return r1 + r2 + r3;
}	

// OBB�ɕK�v�ȏ����Z�b�g
OBB Collision2D::SetOBB( GameObject* pObb ) {
	
	// �ϐ��錾
    D3DXMATRIX matRot;
	OBB SetOBB;

    // ���S�_�擾
	SetOBB.Pos = *(pObb->GetPosition());

    // �����x�N�g���擾
	D3DXVECTOR3* rot = pObb->GetRotation();
	D3DXMatrixRotationYawPitchRoll(&matRot, rot->y, rot->x, rot->z);
	SetOBB.Vec[0] = D3DXVECTOR3(matRot._11,matRot._12,matRot._13);
    SetOBB.Vec[1] = D3DXVECTOR3(matRot._21,matRot._22,matRot._23);
    SetOBB.Vec[2] = D3DXVECTOR3(matRot._31,matRot._32,matRot._33);

    // �����擾
	D3DXVECTOR3 pSize = pObb->GetCollisionCubePlusSize();
	SetOBB.Length.x = pSize.x / 2.0f;
	SetOBB.Length.y = pSize.y / 2.0f;
	SetOBB.Length.z = pSize.z / 2.0f;

	return SetOBB;
}