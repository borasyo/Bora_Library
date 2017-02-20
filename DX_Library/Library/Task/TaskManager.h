//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [TaskManager.h]
// author : �哴�ˑ�
// 
// Scene��̑S�ẴI�u�W�F�N�g���Ǘ�����B
//
// ex)std::vector<GameObject*> Vec = ....FindWithNameAll(...); 
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TaskManager_H_____
#define _____TaskManager_H_____

#include <iostream>
#include "GameObject.h"
#include <list>
#include <string>
#include <vector>

class TaskManager {

private:
	static TaskManager* m_pTaskManager;
	std::list<GameObject*> AllGameObject; // �V�[����̑S�ẴQ�[���I�u�W�F�N�g��ێ�
	int nOldTaskSize;
	
private:
	TaskManager();

public:
	~TaskManager();

	// �C���X�^���X�擾
	static TaskManager* Instance() { return m_pTaskManager; }

	// �Q�[���I�u�W�F�N�g�V�K�쐬
	GameObject* CreateObject(GameObject* Obj);

	// �Q�[���I�u�W�F�N�g���폜	
	bool DestroyObject(GameObject* pObj, bool bParentErase = true);
	
	// �J�n����
	bool Start();

	// �X�V����
	void Update();

	// �`�揈��
	void Draw();

	// �폜����
	void Clear();

	// null�̃|�C���^�����X�g�������
	void NullObjectErase();
	
	// �S�ẴI�u�W�F�N�g��Ԃ�
	std::list<GameObject*>* FindAllObject();
	
	// �S�ẴI�u�W�F�N�g�̒�����A�N�e�B�u�ȃI�u�W�F�N�g��S�ĕԂ�
	std::list<GameObject*> FindWithActive(bool bActive = true);

	// �S�ẴI�u�W�F�N�g�̒����疼�O�̈�v����I�u�W�F�N�g��S�ĕԂ�
	std::vector<GameObject*> FindWithNameAll(const std::string name, bool bActive = true);

	// �S�ẴI�u�W�F�N�g�̒����疼�O�̈�v����I�u�W�F�N�g��1�Ԃ�(name��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
	GameObject* FindWithName(const std::string name, bool bActive = true);

	// �S�ẴI�u�W�F�N�g�̒�����^�O�̈�v����I�u�W�F�N�g��S�ĕԂ�
	std::vector<GameObject*> FindWithTagAll(const std::string tag, bool bActive = true);

	// �S�ẴI�u�W�F�N�g�̒�����^�O�̈�v����I�u�W�F�N�g��1�Ԃ�(tag��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
	GameObject* FindWithTag(const std::string tag, bool bActive = true);
	
	// �S�ẴI�u�W�F�N�g�̒����烌�C���[�̈�v����I�u�W�F�N�g��S�ĕԂ�
	std::vector<GameObject*> FindWithLayerAll(const std::string layer, bool bActive = true);

	// �S�ẴI�u�W�F�N�g�̒����烌�C���[�̈�v����I�u�W�F�N�g��1�Ԃ�(layer��unique�ł͂Ȃ��ꍇ�g�p���Ȃ�)
	GameObject* FindWithLayer(const std::string layer, bool bActive = true);

	// �S�ẴI�u�W�F�N�g��Active�ύX
	void SetAllActive(bool bActive);

	// �S�ẴI�u�W�F�N�g��UpdateFlg��ύX
	void SetAllUpdateFlg(bool bUpdate);

	// �[�x�\�[�g�����{
	void DepthSort();

	// ���݂̃V�[���̌Œ�I�u�W�F�N�g����T������(����̏󋵂ŏ������y���ł���)
	GameObject* FindWithNameForScene(const std::string name);
	GameObject* FindWithTagForScene(const std::string tag);
	GameObject* FindWithLayerForScene(const std::string layer);
};

#endif