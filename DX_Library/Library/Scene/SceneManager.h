//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [SceneManager.h]
// author : �哴�ˑ�
//
// �V�[���ŕK�v�ȃI�u�W�F�N�g���A�N�e�B�u�ɁA
// ���̑����A�N�e�B�u�ɂ��邱�ƂŃV�[�����Ǘ��B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____SCENE_H_____
#define _____SCENE_H_____

#include <iostream>
#include "../Task/GameObject.h"
#include "../Task/TaskManager.h"

// ---- ��{�V�[��
#include "../Scene/SceneTitle.h"
#include "../Scene/SceneStageSelect.h"
#include "../Scene/SceneGameMain.h"
#include "../Scene/SceneResult.h"

// ---- ��
enum eScene {

	SCENE_TITLE = 0,
	SCENE_STAGESELECT,
	SCENE_GAMEMAIN,
	SCENE_RESULT,

	SCENE_MAX,
};

class SceneManager {

private:
	static SceneManager* m_pSceneManager;

	eScene m_eNowScene;
	eScene m_eNextScene;

	TaskManager* m_pCreator;
	std::list<GameObject*>* m_pAllObj;
	
	CSceneTitle* m_pTitle;
	CSceneStageSelect* m_pStageSelect;
	CSceneGameMain* m_pGameMain;
	CSceneResult* m_pResult;
	
private:
	SceneManager();
	
	// ---- �V�[���Ǘ��֐�
	void Title();		// �^�C�g��
	void StageSelect();	// �X�e�[�W�Z���N�g
	void GameMain();	// �Q�[�����C��
	void Result();		// ���U���g
	void ReInit();		// �s�K�v�ɂȂ����I�u�W�F�N�g��S�폜

public:
	~SceneManager();
	
	static SceneManager* Create() { 	
		if( !m_pSceneManager )
			m_pSceneManager = new SceneManager;
		return m_pSceneManager;
	}
	static SceneManager* Instance() { return m_pSceneManager; }

	// �V�[���ύX�v�������Ă��Ȃ������`�F�b�N
	void Update();

	// ������object�𐶐�
	void SetObject();

	// �V�[���ύX��\��
	void SetScene(eScene Scene) { m_eNextScene = Scene; }

	// ���݂̃V�[����Ԃ�
	GameObject* GetNowScene();
};

#endif