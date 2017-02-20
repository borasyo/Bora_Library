//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MouthPosition.h]
// author : �哴�ˑ�
//
// �}�E�X�̍��W���擾����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Window.h"
#include "MouthPosition.h"
#include <iostream>
#include "../Task/Empty.h"
#include "../Task/TaskManager.h"

// ���̒�`
CMouthPosition* CMouthPosition::m_pMouthPosition = nullptr;


CMouthPosition::CMouthPosition() : m_bInitialized(0)
								 , m_tScreenPosition(0)
								 , m_tClientPosition(0){

}

bool CMouthPosition::Init(){
	// ���d�������֎~(UnInit�K�{)
	if(m_bInitialized){
		return !m_bInitialized;
	}

	// �m��
	m_tScreenPosition = new Position_2D;
	m_tClientPosition = new Position_2D;
	
	// 0���Z�b�g
	m_tScreenPosition->x = 0;
	m_tScreenPosition->y = 0;
	m_tClientPosition->x = 0;
	m_tClientPosition->y = 0;

	// �ŏ��̓}�E�X���\������Ă���
	m_ShowMouthFlag = true;

	// �E�B���h�E�O�ł��}�E�X�̋������Ď�����
	//SetCapture( CWindow::Create()->GetWindowHandle() );

	// ������������t���O
	m_bInitialized = true;

	// �ݒ���i�[
	m_bDraw = bStartMouthDraw;
	m_Object2D.SetFileName(MouthTextureName);
	m_Scale = MouthTextureSize * CWindow::Instance()->GetWidthMag();

	// �}�E�X�p�擾
	m_pMouth = TaskManager::Instance()->CreateObject(new Empty("MouthPosition"));
	m_pMouth->SetCollisionCubeSize(m_Scale); // �R���W�����ݒ�

	return m_bInitialized;
}

bool CMouthPosition::UnInit(){
	
	if( !m_bInitialized ){
		// ����������Ă��Ȃ�
		return m_bInitialized;
	}

	if( m_tScreenPosition != NULL ){
		delete m_tScreenPosition;
	}
	if( m_tClientPosition != NULL ){
		delete m_tClientPosition;
	}

	m_tScreenPosition	= NULL;
	m_tClientPosition	= NULL;
	m_bInitialized		= false;

	ShowCursor( 1 );

	return true;
}

void CMouthPosition::Update(){

	if( !m_bInitialized ){
		return ;
	}

	// ���W�擾
	POINT  Pos;
	Pos.x = 0;
	Pos.y = 0;
	GetCursorPos( &Pos );
	
	// �X�N���[�����W
	m_tScreenPosition->x = (FLOAT)Pos.x;
	m_tScreenPosition->y = (FLOAT)Pos.y;

	// �N���C�A���g���W
	ScreenToClient( CWindow::Instance()->GetWindowHandle() , &Pos );	//�X�N���[�����W���N���C�A���g���W�ɕϊ�
	
	m_tClientPosition->x = (FLOAT)Pos.x;
	m_tClientPosition->y = (FLOAT)Pos.y;

	float	fWidth;
	float	fHeight;
	bool	bMouthShowFlag;
	
	fWidth	= (float)CWindow::Instance()->GetClientWidth();
	fHeight	= (float)CWindow::Instance()->GetClientHeight();

	// �E�B���h�E�O�ɂ��邩
	bMouthShowFlag = (  m_tClientPosition->x <   0.0f || m_tClientPosition->y <    0.0f ||
						m_tClientPosition->x > fWidth || m_tClientPosition->y > fHeight );

	// �\���؂�ւ�
	if( bMouthShowFlag != m_ShowMouthFlag ){
		ShowCursor( bMouthShowFlag );
		m_ShowMouthFlag = bMouthShowFlag;
	}
	
	// MouthPos�i�[
	m_pMouth->GetPosition()->x = m_tClientPosition->x;
	m_pMouth->GetPosition()->y = m_tClientPosition->y;
}

void CMouthPosition::Draw(){

	if(!m_bDraw)
		return;

	D3DXVECTOR3 Pos = D3DXVECTOR3(m_tClientPosition->x,m_tClientPosition->y,0) + (m_Scale/2.0f) + MouthPosRivision;
	Pos.z = -1.0f;
	m_Object2D.Draw(Pos, m_Scale);
}

// Position_2D�\���̂�Ԃ�(�X�N���[�����W)
CMouthPosition::Position_2D* CMouthPosition::GetMouthScreenPosition(){
	return m_tScreenPosition;
}

// �|�C���^�ɏ����Z�b�g(�X�N���[�����W)
// X�̂�(�X�N���[�����W)
CMouthPosition::Position_2D* CMouthPosition::GetMouthScreenPosition( float *PositionX ){
	*PositionX = m_tScreenPosition->x;
	return m_tScreenPosition;
}
// XY(�X�N���[�����W)
CMouthPosition::Position_2D* CMouthPosition::GetMouthScreenPosition( float *PositionX , float *PositionY ){
	*PositionX = m_tScreenPosition->x;
	*PositionY = m_tScreenPosition->y;
	return m_tScreenPosition;
}

// Position_2D�\���̂�Ԃ�(�N���C�A���g���W)
CMouthPosition::Position_2D* CMouthPosition::GetMouthClientPosition(){
	return m_tClientPosition;
}

// �|�C���^�ɏ����Z�b�g(�N���C�A���g���W)
// X�̂�(�N���C�A���g���W)
CMouthPosition::Position_2D* CMouthPosition::GetMouthClientPosition( float *PositionX ){
	*PositionX = m_tClientPosition->x;
	return m_tClientPosition;
}
// XY(�N���C�A���g���W)
CMouthPosition::Position_2D* CMouthPosition::GetMouthClientPosition( float *PositionX , float *PositionY ){
	*PositionX = m_tClientPosition->x;
	*PositionY = m_tClientPosition->y;
	return m_tClientPosition;
}


// �}�E�X���ړ�������(�N���C�A���g���W)
void CMouthPosition::SetMouthClientPosition( float PositionX , float PositionY ){
	POINT  Pos;
	Pos.x = 0;
	Pos.y = 0;
	GetCursorPos( &Pos );
	
	Pos.x = Pos.x + (LONG)(PositionX - m_tClientPosition->x);
	Pos.y = Pos.y + (LONG)(PositionY - m_tClientPosition->y);

	SetCursorPos( (int)Pos.x , (int)Pos.y );

	//--	�N���C�A���g���W
	ScreenToClient( CWindow::Instance()->GetWindowHandle() , &Pos );	//�X�N���[�����W���N���C�A���g���W�ɕϊ�
	
	m_tClientPosition->x = (float)Pos.x;
	m_tClientPosition->y = (float)Pos.y;
}