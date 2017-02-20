//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameBase.cpp]
// author : �哴�ˑ�
// 
// �����ŃQ�[�����[�v���񂷁B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "GameBase.h"
#include "../Library/DirectX/DirectInputManager.h"
#include "../Library/DirectX/DirectSound.h"
#include "../Library/Function/Define.h"
#include "../Library/Debug/ParticleCnt.h"
#include "../Library/Function/Math.h"
#include "../Library/Function/Time.h"
#include "../Library/Function/LoadResource.h"

// �R���X�g���N�^
CGameBase::CGameBase()
	:m_pWindow(nullptr)
	,m_pDirect3D(nullptr)
	,m_pTextureManager(nullptr)
	,m_pInputManager(nullptr) 
	,m_pModelManager(nullptr)
	,m_pSceneManager(nullptr)
	,m_pFPSController(nullptr) {
}

// �f�X�g���N�^
CGameBase::~CGameBase(){
	Clear();
}

// ---- �Q�[���𑖂点��
int CGameBase::Run()
{
	// �V�X�e��������
	if( !Awake() ){
		return 0; //�G���[
	}
	
	// �Q�[��������
	if( !Start() ){
		Clear();
		return 0; //�G���[
	}

	HRESULT hr;
	// ---- ���C�����[�v ----
	while( m_pWindow->HandleMessage() )
	{
		if( !m_pFPSController->CheckExec() )
			continue;

		// ---- �X�V
		Update();

		// ---- �`��
		m_pDirect3D->Clear();
		hr = m_pDirect3D->BeginScene();
		Draw();
		m_pDirect3D->EndScene();
		m_pDirect3D->Present();
	}

	return m_pWindow->GetExitValue();
}

// �V�X�e��������
bool CGameBase::Awake(){

	// �E�C���h�E�쐬
	m_pWindow = CWindow::Instance();

	// HINSTANCE�擾
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	// �E�C���h�E�쐬
	//m_pWindow->MakeWindow( WindowName, hInstance, (int)1920/1.5f, (int)1080/1.5f );
	m_pWindow->MakeWindow( WindowName, hInstance, (int)fWindowWidth, (int)fWindowHeight );
	
	// �E�C���h�E�̕\��
	//m_pWindow->Show();
	
	// Task����
	m_pTaskManager = TaskManager::Instance();

	// DirectX9����������
	m_pDirect3D = CDirect3D::Create(m_pWindow);

	// DirectX9�̏�����
	if( m_pDirect3D->InitDirect3D() ){
		return false;
	}
	
	// InputManager����������
	m_pInputManager = CDirectInputManager::Instance();
	if( FAILED( m_pInputManager->Init(GetWindowHandle()) ) )
		return false;
	
	// TextureManager����������
	m_pTextureManager = CTextureManager::Create();
	if( FAILED( m_pTextureManager->Init() ) )
		return false;

	// ModelManager����������
	m_pModelManager = CModelManager::Create();
	if( FAILED( m_pModelManager->Init() ) )
		return false;

	// LightIndex����
	m_pLightIndex = CLightIndex::Create();

	// MouthPos
	m_pMouthPosition = CMouthPosition::Create();
	m_pMouthPosition->Init();

	// �V�[���}�l�[�W���[����
	m_pSceneManager = SceneManager::Create();

	// Sound������
	InitSound(m_pWindow->GetWindowHandle());

	// FPS�R���g���[��������
	m_pFPSController = FPSController::Create();
	m_pFPSController->Init();

	// DelayFunctionManager����
	m_pDelayFunctionManager = CDelayFunctionManager::Instance();

	// Math�֌W��������
	SetMath();

	// Time������
	CTime::Init();
	
#ifdef DEBUG
	SetFont(); // debug
#endif

	return true;
}

// ����������
bool CGameBase::Start(){

	// ���\�[�X�ǂݍ���
	LoadResources();
	
	// TaskManager������
	m_pSceneManager->SetObject();
	
	// �S�ẴI�u�W�F�N�g��������
	if( !m_pTaskManager->Start() )
		return false;
	
	// �E�C���h�E�̕\��
	m_pWindow->Show();

	// �^�C�g���\��
	m_pSceneManager->SetScene(SCENE_TITLE);

	return true;
}

// �X�V����
void CGameBase::Update(){
	
	// �E�B���h�E�I������
	if(m_pInputManager->GetJoyTrigger(0, 8) || m_pInputManager->GetKeyboardTrigger(DIK_ESCAPE)) {
		DestroyWindow(m_pWindow->GetWindowHandle());
		return;
	}

	// Time�X�V
	CTime::Update();

	// MouthPos�X�V
	m_pMouthPosition->Update();

	// DirectInput�X�V
	m_pInputManager->Update();

	// Scene�ύX�`�F�b�N
	m_pSceneManager->Update();

	// �I�u�W�F�N�g�X�V
	m_pTaskManager->Update();
	
	// �����̓Q�[�����[�v���A���t���[�����s���Ȃ��Ƃ����Ȃ�
	m_pDelayFunctionManager->CheckStoreFunc();
}

// �`�揈��
void CGameBase::Draw(){

	// �I�u�W�F�N�g�`��
	m_pTaskManager->Draw();
	
#ifdef DEBUG
	// FPS�\��
	m_pFPSController->DrawFPS();
	
	CntDraw(); // debug
#endif

	m_pMouthPosition->Draw();
}

// �㏈��
void CGameBase::Clear(){

	m_pModelManager->AllRelease();
	m_pMouthPosition->UnInit();
	UninitSound();
	m_pInputManager->Uninit();
	
#ifdef DEBUG
	DelFont(); // debug
#endif

	// SingletonClass��delete
	delete m_pModelManager;
	delete m_pInputManager;
	delete m_pTextureManager;
	delete m_pTaskManager;
	delete m_pDirect3D;
	delete m_pWindow;
	delete m_pLightIndex;
	delete m_pMouthPosition;
	delete m_pSceneManager;
	delete m_pFPSController;
	delete m_pDelayFunctionManager;
}

// Direct3D�擾
CDirect3D* CGameBase::GetDirect3D(){
	return m_pDirect3D;
}

// DirectX9device�擾
LPDIRECT3DDEVICE9 CGameBase::GetDirectXDevice(){
	return m_pDirect3D->GetDirect3DDevice();
}

// Window�擾
CWindow* CGameBase::GetWindow(){
	return m_pWindow;
}

// Handle�擾
HWND CGameBase::GetWindowHandle(){
	return m_pWindow->GetWindowHandle();
}
