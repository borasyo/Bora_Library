//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameBase.cpp]
// author : 大洞祥太
// 
// ここでゲームループを回す。
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

// コンストラクタ
CGameBase::CGameBase()
	:m_pWindow(nullptr)
	,m_pDirect3D(nullptr)
	,m_pTextureManager(nullptr)
	,m_pInputManager(nullptr) 
	,m_pModelManager(nullptr)
	,m_pSceneManager(nullptr)
	,m_pFPSController(nullptr) {
}

// デストラクタ
CGameBase::~CGameBase(){
	Clear();
}

// ---- ゲームを走らせる
int CGameBase::Run()
{
	// システム初期化
	if( !Awake() ){
		return 0; //エラー
	}
	
	// ゲーム初期化
	if( !Start() ){
		Clear();
		return 0; //エラー
	}

	HRESULT hr;
	// ---- メインループ ----
	while( m_pWindow->HandleMessage() )
	{
		if( !m_pFPSController->CheckExec() )
			continue;

		// ---- 更新
		Update();

		// ---- 描画
		m_pDirect3D->Clear();
		hr = m_pDirect3D->BeginScene();
		Draw();
		m_pDirect3D->EndScene();
		m_pDirect3D->Present();
	}

	return m_pWindow->GetExitValue();
}

// システム初期化
bool CGameBase::Awake(){

	// ウインドウ作成
	m_pWindow = CWindow::Instance();

	// HINSTANCE取得
	HINSTANCE hInstance = GetModuleHandle(nullptr);

	// ウインドウ作成
	//m_pWindow->MakeWindow( WindowName, hInstance, (int)1920/1.5f, (int)1080/1.5f );
	m_pWindow->MakeWindow( WindowName, hInstance, (int)fWindowWidth, (int)fWindowHeight );
	
	// ウインドウの表示
	//m_pWindow->Show();
	
	// Task生成
	m_pTaskManager = TaskManager::Instance();

	// DirectX9生成初期化
	m_pDirect3D = CDirect3D::Create(m_pWindow);

	// DirectX9の初期化
	if( m_pDirect3D->InitDirect3D() ){
		return false;
	}
	
	// InputManager生成初期化
	m_pInputManager = CDirectInputManager::Instance();
	if( FAILED( m_pInputManager->Init(GetWindowHandle()) ) )
		return false;
	
	// TextureManager生成初期化
	m_pTextureManager = CTextureManager::Create();
	if( FAILED( m_pTextureManager->Init() ) )
		return false;

	// ModelManager生成初期化
	m_pModelManager = CModelManager::Create();
	if( FAILED( m_pModelManager->Init() ) )
		return false;

	// LightIndex生成
	m_pLightIndex = CLightIndex::Create();

	// MouthPos
	m_pMouthPosition = CMouthPosition::Create();
	m_pMouthPosition->Init();

	// シーンマネージャー生成
	m_pSceneManager = SceneManager::Create();

	// Sound初期化
	InitSound(m_pWindow->GetWindowHandle());

	// FPSコントローラ初期化
	m_pFPSController = FPSController::Create();
	m_pFPSController->Init();

	// DelayFunctionManager生成
	m_pDelayFunctionManager = CDelayFunctionManager::Instance();

	// Math関係を初期化
	SetMath();

	// Time初期化
	CTime::Init();
	
#ifdef DEBUG
	SetFont(); // debug
#endif

	return true;
}

// 初期化処理
bool CGameBase::Start(){

	// リソース読み込み
	LoadResources();
	
	// TaskManager初期化
	m_pSceneManager->SetObject();
	
	// 全てのオブジェクトを初期化
	if( !m_pTaskManager->Start() )
		return false;
	
	// ウインドウの表示
	m_pWindow->Show();

	// タイトル表示
	m_pSceneManager->SetScene(SCENE_TITLE);

	return true;
}

// 更新処理
void CGameBase::Update(){
	
	// ウィンドウ終了判定
	if(m_pInputManager->GetJoyTrigger(0, 8) || m_pInputManager->GetKeyboardTrigger(DIK_ESCAPE)) {
		DestroyWindow(m_pWindow->GetWindowHandle());
		return;
	}

	// Time更新
	CTime::Update();

	// MouthPos更新
	m_pMouthPosition->Update();

	// DirectInput更新
	m_pInputManager->Update();

	// Scene変更チェック
	m_pSceneManager->Update();

	// オブジェクト更新
	m_pTaskManager->Update();
	
	// こいつはゲームループ中、毎フレーム実行しないといけない
	m_pDelayFunctionManager->CheckStoreFunc();
}

// 描画処理
void CGameBase::Draw(){

	// オブジェクト描画
	m_pTaskManager->Draw();
	
#ifdef DEBUG
	// FPS表示
	m_pFPSController->DrawFPS();
	
	CntDraw(); // debug
#endif

	m_pMouthPosition->Draw();
}

// 後処理
void CGameBase::Clear(){

	m_pModelManager->AllRelease();
	m_pMouthPosition->UnInit();
	UninitSound();
	m_pInputManager->Uninit();
	
#ifdef DEBUG
	DelFont(); // debug
#endif

	// SingletonClassをdelete
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

// Direct3D取得
CDirect3D* CGameBase::GetDirect3D(){
	return m_pDirect3D;
}

// DirectX9device取得
LPDIRECT3DDEVICE9 CGameBase::GetDirectXDevice(){
	return m_pDirect3D->GetDirect3DDevice();
}

// Window取得
CWindow* CGameBase::GetWindow(){
	return m_pWindow;
}

// Handle取得
HWND CGameBase::GetWindowHandle(){
	return m_pWindow->GetWindowHandle();
}
