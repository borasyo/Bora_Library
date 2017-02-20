//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.h]
// author : �哴�ˑ�
// 
// �T�v : �S�ẴQ�[���I�u�W�F�N�g�̐e�N���X
//
// �uObjectType�v
// Object3DModel, Object3DPolygon, Object2D, ObjectCamera, 
// ObjectLight, Collision2D, Collision3D, Particle2D, Particle3D
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GAMEOBJECT_H_____
#define _____GAMEOBJECT_H_____

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>
#include "d3dx9.h"
#include "DepthData.h"
#include "../Function/Define.h"
#include "../Function/Time.h"
#include "../Function/Math.h"
#include "../DirectX/Window.h"
#include "../DirectX/Direct3D.h"
#include "../DirectX/DirectInputManager.h"

// 
class GameObject;

// -- �\���̒�`
struct Collision {
	bool bCollision;							// �����蔻����s���Ă��悢��
	D3DXVECTOR3 CollisionCube;					// ���̑傫��(�e�ӂ̒���)
	float fCollisionCircle;						// ���̂̑傫��(���a)
	std::map<GameObject*, bool> OnCollision;	// �����蔻�蒆��
//	bool bOnCollision;				// �����蔻�蒆��
};

struct Transform {
	// ---- ��{�ϐ�
	std::string Name;				// ���O
	std::string Tag;				// �^�O
	std::string Layer;				// ���C���[

	D3DXVECTOR3 Position;			// ���W
	D3DXVECTOR3 Rotation;			// �p�x
	D3DXVECTOR3 Size;				// �T�C�Y
	D3DXVECTOR3 MoveAmount;			// �ǂꂾ���ړ�������
	D3DXVECTOR3 RotationAmount;		// �ǂꂾ����]������
	D3DXVECTOR3 SizeAmount;			// �ǂꂾ���g��k��������
	D3DXVECTOR3 OldPosition;		// �ߋ����W
	D3DXVECTOR3 OldRotation;		// �ߋ��p�x
	D3DXVECTOR3 OldSize;			// �ߋ��T�C�Y
};

// -- �N���X��`
class GameObject {

protected:
	Transform m_Transform;
	Collision m_Collision;
	
	int m_nSortingLayer;
	int m_nOrderinLayer;
	//int m_nDepth;				// �[�x (����Z-�ŕ`�揇���\�[�g)

	bool m_bActive;				// �A�N�e�B�u���ǂ���
	bool m_bNotChangeActive;	// �A�N�e�B�u��Ԃ̕ύX�������Ă��悢��
	bool m_bUpdate;				// �X�V�����邩
	bool m_bNotChangeUpdate;	// �X�V�ۂ̕ύX�������Ă��悢��
	bool m_bDestroy;			// ���̃I�u�W�F�N�g�͎��R�ɔj��ł��邩
	std::string m_Message;		// ���b�Z�[�W�ɉ����ē���̏��������s
	int m_nLife; 
	
	// ---- �e�q�֌W
	GameObject* m_Parent;			  // �e�N���X
	std::list<GameObject*> m_Child;	  // �q�N���X

	// ---- �ύX�A�Q�Ƃ͂��Ȃ�
	D3DXVECTOR3 m_BaseCube;			// m_Size��1(�)�̎��̓�����͈͂�ێ�
	float m_fBaseCircle;			// m_Size��1(�)�̎��̓�����͈͂�ێ�
	
protected:
	// ---- �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ύX�����ۂ̃C�x���g�֐�(�O������͌Ăяo���s��)
	virtual void OnEnable() {}
	virtual void OnDisable() {}

public:
	GameObject();
	virtual ~GameObject();

	// ---- ��{�֐�
	virtual void Awake();		// �R���X�g���N�^�Ŏ��s
	virtual bool Start();		// �Q�[�����[�v1�t���[���ڂ�1�x�������s

	virtual void FastUpdate();	// �D�悵��Update	(���O�������Ȃǂ̏����������B���̃I�u�W�F�N�g�͐G��Ȃ�)
	virtual void Update();		// ���ʂ�Update		(��{����)
	virtual void LateUpdate();	// �Ō��Update		(�R���W�����Ȃ�)

	virtual void FastDraw();	// �D�悵��Draw		(�J�����Ȃ�)
	virtual void Draw();		// ���ʂ�Draw()		(���f���Ȃ�)
	virtual void LateDraw();	// �Ō��Draw		(UI�A�f�o�b�O�R���W�����Ȃ�)

	virtual void Clear(){}		// �㏈��

	virtual GameObject* CreateChild(){ return nullptr; } // Particle�Ȃ�new�̐����c��ɂȂ�I�u�W�F�g�����������悭�쐬����
	
	// ---- �_�E���L���X�g
	virtual GameObject* GetDownCastClass(GameObject* Obj) = 0; // �_�E���L���X�g�̂��߂ɂ͕K�{�f�X

	// ---- ��O�`�F�b�N
	void ExceptionCheck();
	
	// ---- �ď�����
	void ReInit();
	
	// ---- �X�V�O����
	void Preparation();
	
	// ---- �Q�b�^�[�֐�
	const std::string GetName() { return m_Transform.Name; }	// ���O�擾
	const std::string GetTag() { return m_Transform.Tag; }		// �^�O�擾
	const std::string GetLayer() { return m_Transform.Layer; }	// ���C���[�擾

	bool GetActive() { return m_bActive; }			// ���̃I�u�W�F�N�g�̓A�N�e�B�u���ǂ���
	bool GetUpdateFlg() { return m_bUpdate; }		// ���̃I�u�W�F�N�g�͍X�V���邩
	const bool GetDestory() { return m_bDestroy; }	// ���̃I�u�W�F�N�g�͔j��\��
	int GetLife() { return m_nLife; }				// ���̃I�u�W�F�N�g�̃��C�t���擾

	// --- Free�֐� ����{�I�ɂ͎g�p���Ȃ��I
	virtual void FreeFunction(){}
	virtual int* GetInt() { return nullptr; }
	virtual float* GetFloat() { return nullptr; }
	virtual bool* GetBool() { return nullptr; }
	virtual D3DXVECTOR3* GetVec() { return nullptr; }
	virtual D3DXCOLOR* GetColor(){ return nullptr; }
	virtual D3DXMATRIX* GetMatrix(){ return nullptr; }

	// �e�q
	GameObject* GetParent() { return m_Parent; }					// �e�̃I�u�W�F�N�g�擾
	std::list<GameObject*>* GetChild() { return &m_Child; }			// �q�̃I�u�W�F�N�g�擾
	GameObject* FindChild(const std::string Name);					// ����̎q�I�u�W�F�N�g���擾
	std::list<GameObject*> FindChildAll(const std::string Name);	// ����̎q�I�u�W�F�N�g���擾

	GameObject* SetParent(GameObject* Parent);  // �e�q�֌W��ݒ�
	void DetachParent();
	
	void SetActive(bool bFlg);
	void SetUpdateFlg(bool bFlg);
	void BanDestroy();  // ���̃I�u�W�F�N�g��j��ł��Ȃ�����
	void SendForMessage(std::string msg);	// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗂�
	void SetLife(int nLife); // ���C�t��ϓ�����
	void Death() { m_nLife = 0; }	// ���C�t��0�ɂ���

	// ---- �R���W����
	const D3DXVECTOR3 GetCollisionCubePlusSize() { return m_Collision.CollisionCube; }
	const D3DXVECTOR3 GetCollisionCubeMinusSize() { return -m_Collision.CollisionCube; }
	float GetCollisionCircleSize() { return m_Collision.fCollisionCircle; }
	bool GetCollisionFlg() { return m_Collision.bCollision; }
	
	void SetCollisionCubeSize(D3DXVECTOR3 Size);
	void SetCollisionCircleSize(float size);
	
	void SetCollisionFlg(bool bFlg);
	
	void OnCollision(GameObject* pObj, bool bOnCollision); // ����I�u�W�F�N�g�Ɣ��茋�ʂ𑗂�
	bool GetOnCollisionFlg(GameObject* pObj);
	virtual void OnCollisionEnter(GameObject* pObj) {}
	virtual void OnCollisionStay(GameObject* pObj) {}
	virtual void OnCollisionExit(GameObject* pObj) {}
	
	// ---- �g�����X�t�H�[��
	D3DXVECTOR3* GetPosition() { return &m_Transform.Position; }			// ���W���擾
	D3DXVECTOR3* GetRotation() { return &m_Transform.Rotation; }			// �p�x���擾
	D3DXVECTOR3* GetSize() { return &m_Transform.Size; }					// �T�C�Y���擾

	D3DXVECTOR3* GetOldPosition() { return &m_Transform.OldPosition; }		// �ߋ����W���擾
	D3DXVECTOR3* GetOldRotation() { return &m_Transform.OldRotation; }		// �ߋ��p�x���擾
	D3DXVECTOR3* GetOldSize() { return &m_Transform.OldSize; }				// �ߋ��T�C�Y���擾
	
	D3DXVECTOR3* GetMoveAmount() { return &m_Transform.MoveAmount; }		// �ړ��ʂ��擾
	D3DXVECTOR3* GetRotAmount() { return &m_Transform.RotationAmount; }		// ��]�ʂ��擾
	D3DXVECTOR3* GetSizeAmount() { return &m_Transform.SizeAmount;  }		// �g��k�����ʂ��擾
	
	void Move(D3DXVECTOR3 move);			// �I�u�W�F�N�g���ړ�(�q������Ύq��)
	void Rotation(D3DXVECTOR3 rot);			// �I�u�W�F�N�g����](�q������Ύq��)
	void SizeChange(D3DXVECTOR3 size);		// �I�u�W�F�N�g�T�C�Y�ύX(�q������Ύq��)
	void ScaleChange(D3DXVECTOR3 scale);	// �I�u�W�F�N�g�X�P�[���ύX(�q������Ύq��)
	void ScaleChange(float scale);			// �I�u�W�F�N�g�X�P�[���ύX(�q������Ύq��)
	void ReturnMove();		// �ړ������̂�߂�
	void ReturnMoveX();		// �ړ�����X��߂�
	void ReturnMoveY();		// �ړ�����Y��߂�
	void ReturnMoveZ();		// �ړ�����Z��߂�
	void ReturnRot();		// ��]�����̂�߂�
	void ReturnSize();		// �g�債���̂�߂�

	// �[�x�\�[�g(����ɌĂ΂Ȃ�)
	//int GetDepth() { return m_nSortingLayer; }
	int GetSortingLayer() { return m_nSortingLayer; }
	int GetOrderinLayer() { return m_nOrderinLayer; }
};

#endif