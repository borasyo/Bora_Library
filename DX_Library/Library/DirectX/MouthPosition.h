//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MouthPosition.h]
// author : �哴�ˑ�
//
// �}�E�X�̍��W���擾����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MousePosition_H_____
#define _____MousePosition_H_____

#include "../ObjectType/Object2D.h"

class CMouthPosition {

public:
	typedef struct{
		float x;
		float y;
	} Position_2D;

	CObject2D m_Object2D;
	D3DXVECTOR3 m_Scale;

public:
	~CMouthPosition(){};
	
	static CMouthPosition* Create() { 	
		if( !m_pMouthPosition )
			m_pMouthPosition = new CMouthPosition;
		return m_pMouthPosition;
	}
	static CMouthPosition* Instance() { return m_pMouthPosition; }

	bool Init();
	void Update();
	void Draw();
	bool UnInit();

	Position_2D* GetMouthScreenPosition(); // Position_2D�\���̂�Ԃ�(�X�N���[�����W)
	Position_2D* GetMouthScreenPosition( float* PositionX ); // �|�C���^�ɏ����Z�b�g(�X�N���[�����W)
	Position_2D* GetMouthScreenPosition( float* PositionX , float* PositionY );

	Position_2D* GetMouthClientPosition(); // Position_2D�\���̂�Ԃ�(�N���C�A���g���W)
	Position_2D* GetMouthClientPosition( float* PositionX ); // �|�C���^�ɏ����Z�b�g(�N���C�A���g���W)
	Position_2D* GetMouthClientPosition( float* PositionX , float* PositionY );

	void SetMouthClientPosition( float PositionX , float PositionY ); // �w��N���C�A���g���W�ɃJ�[�\�����ړ�������

	D3DXVECTOR3 GetScale() { return m_Scale; }
	GameObject* GetMouthObj() { return m_pMouth; }
	void ChangeDrawFlg() { m_bDraw = !m_bDraw; }	// �}�E�X��`�悷�邩�𔽓]
	void SetDrawFlg(bool bFlg) { m_bDraw = bFlg; }	// �}�E�X��`�悷�邩��ύX
	bool GetDrawFlg() { return m_bDraw; }			// �}�E�X��`�悷�邩���擾

protected:
private:
	CMouthPosition();

private:
	static CMouthPosition* m_pMouthPosition;

	GameObject* m_pMouth;	// �I�u�W�F�N�g�Ƃ��ĕێ�
	bool m_bDraw;

	Position_2D* m_tScreenPosition; // �X�N���[�����W
	Position_2D* m_tClientPosition; // �N���C�A���g���W

	bool m_bInitialized;
	bool m_ShowMouthFlag;
};

#endif