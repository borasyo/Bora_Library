//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameBase.h]
// author : �哴�ˑ�
// 
// �����ŃQ�[�����[�v�����񂷁B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GAMEBASE_H_____
#define _____GAMEBASE_H_____

#include "../Library/DirectX/Window.h"
#include "../Library/DirectX/Direct3D.h"
#include "../Library/Debug/FPSController.h"
#include "../Library/Task/TaskManager.h"
#include "../Library/ObjectData/TextureManager.h"
#include "../Library/ObjectData/ModelManager.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/ObjectData/LightIndex.h"
#include "../Library/DirectX/MouthPosition.h"
#include "../Library/Scene/SceneManager.h"
#include "../Library/Function/DelayFunction.h"

class CGameBase {

public:
	CGameBase();
	~CGameBase();

	// ���s
	int Run();
		
	// ---- �Q�b�^�[
	CDirect3D* GetDirect3D();			  // DirectX9�擾
	LPDIRECT3DDEVICE9 GetDirectXDevice(); // Device�擾
	CWindow* GetWindow();				  // Window�擾
	HWND GetWindowHandle();				  // WindowHandle�擾

private:
	
	bool Awake();	// �V�X�e��������
	bool Start();	// �Q�[��������
	void Update();	// �X�V
	void Draw();	// �`��
	void Clear();	// �I��

private:
	TaskManager* m_pTaskManager;
	CWindow* m_pWindow;
	FPSController* m_pFPSController;
	CTextureManager* m_pTextureManager;
	CDirectInputManager* m_pInputManager;
	CModelManager* m_pModelManager;
	CLightIndex* m_pLightIndex;
	CMouthPosition* m_pMouthPosition;
	SceneManager* m_pSceneManager;
	CDirect3D* m_pDirect3D;
	CDelayFunctionManager* m_pDelayFunctionManager;
};

#endif