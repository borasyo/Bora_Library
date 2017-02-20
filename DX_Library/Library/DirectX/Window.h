//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//[Window.h]
// author : 大洞祥太
// 
// Window生成プログラム。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WINDOW_H_____
#define _____WINDOW_H_____

#include <Windows.h>	// ウィンドウ作成用
#include <tchar.h>		// Unicode
#include "../Function/Define.h"

class CWindow {

public:
	static CWindow* Instance() { return m_pWindow; }				// WindowClassのインスタンス取得

	~CWindow(){};

	// Window作成(デフォルトサイズに800×600を指定)
	HRESULT MakeWindow(	LPTSTR WindowName, HINSTANCE& hInstance,
						const int& ClientWidth = 800, const int& ClientHeight = 600 );

	// Window表示
	HRESULT Show();

	// ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc( HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam );
	
	// メッセージの処理関数
	bool HandleMessage();

	// ----- ゲッター -----
	int	GetExitValue() const { return m_MessageInfo.wParam; }												// 終了コードの取得関数
	HWND GetWindowHandle() const { return m_WindowHandle; }													// ウィンドウハンドルの取得関数
	LPTSTR GetName() const { return m_WindowName; }															// ウィンドウの名前取得関数

	float GetClientWidth() { return (float)m_ClientWidth; }													// クライアント領域の幅取得関数
	float GetClientHeight() { return (float)m_ClientHeight; }												// クライアント領域の高さ取得関数
	D3DXVECTOR3 GetClientSize() { return D3DXVECTOR3((float)m_ClientWidth,(float)m_ClientHeight,0.0f); }	// クライアント領域取得
	
	float GetWindowWidth() const { return (float)m_WindowWidth; }											// ウィンドウの幅取得関数
	float GetWindowHeight() const { return (float)m_WindowHeight; }											// ウィンドウの高さ取得関数
	D3DXVECTOR3 GetWindowSize() { return D3DXVECTOR3((float)m_WindowWidth,(float)m_WindowHeight,0.0f); }	// ウィンドウ領域取得
	
	float WindowAspect() const { return (float)m_ClientWidth/(float)m_ClientHeight; }						// アスペクト比を取得
	
//	float GetWidthMag() { return (float)(1920/1.5f) / fWindowWidth; }										// フルスクリーン時の幅拡大率
//	float GetHeightMag() { return (float)(1080/1.5f) / fWindowHeight; }										// フルスクリーン時の高さ拡大率
	float GetWidthMag() { return (float)m_WindowWidth / fWindowWidth; }										// フルスクリーン時の幅拡大率
	float GetHeightMag() { return (float)m_WindowHeight / fWindowHeight; }									// フルスクリーン時の高さ拡大率

	// ---- セッター ----
	void SetWidth(int nWidth){ m_ClientWidth = m_WindowWidth = nWidth; }
	void SetHeight(int nHeight){ m_ClientHeight = m_WindowHeight = nHeight; }

private:
	// コンストラクタ
	CWindow();

	//===== メンバ変数 =====
private:
	static CWindow* m_pWindow;

	HWND		m_WindowHandle;		// ウィンドウハンドル
	MSG			m_MessageInfo;		// メッセージ情報
	WNDCLASSEX	m_Wcex;				// ウィンドウクラス
	LPTSTR		m_WindowName;		// ウィンドウの名前
	int			m_ClientWidth;		// クライアント領域の幅
	int			m_ClientHeight;		// クライアント領域の高さ
	int			m_WindowWidth;		// ウィンドウの幅
	int			m_WindowHeight;		// ウィンドウの高さ
};

#endif