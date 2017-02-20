//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
//[Window.h]
// author : �哴�ˑ�
// 
// Window�����v���O�����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____WINDOW_H_____
#define _____WINDOW_H_____

#include <Windows.h>	// �E�B���h�E�쐬�p
#include <tchar.h>		// Unicode
#include "../Function/Define.h"

class CWindow {

public:
	static CWindow* Instance() { return m_pWindow; }				// WindowClass�̃C���X�^���X�擾

	~CWindow(){};

	// Window�쐬(�f�t�H���g�T�C�Y��800�~600���w��)
	HRESULT MakeWindow(	LPTSTR WindowName, HINSTANCE& hInstance,
						const int& ClientWidth = 800, const int& ClientHeight = 600 );

	// Window�\��
	HRESULT Show();

	// �E�B���h�E�v���V�[�W��
	static LRESULT CALLBACK WindowProc( HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam );
	
	// ���b�Z�[�W�̏����֐�
	bool HandleMessage();

	// ----- �Q�b�^�[ -----
	int	GetExitValue() const { return m_MessageInfo.wParam; }												// �I���R�[�h�̎擾�֐�
	HWND GetWindowHandle() const { return m_WindowHandle; }													// �E�B���h�E�n���h���̎擾�֐�
	LPTSTR GetName() const { return m_WindowName; }															// �E�B���h�E�̖��O�擾�֐�

	float GetClientWidth() { return (float)m_ClientWidth; }													// �N���C�A���g�̈�̕��擾�֐�
	float GetClientHeight() { return (float)m_ClientHeight; }												// �N���C�A���g�̈�̍����擾�֐�
	D3DXVECTOR3 GetClientSize() { return D3DXVECTOR3((float)m_ClientWidth,(float)m_ClientHeight,0.0f); }	// �N���C�A���g�̈�擾
	
	float GetWindowWidth() const { return (float)m_WindowWidth; }											// �E�B���h�E�̕��擾�֐�
	float GetWindowHeight() const { return (float)m_WindowHeight; }											// �E�B���h�E�̍����擾�֐�
	D3DXVECTOR3 GetWindowSize() { return D3DXVECTOR3((float)m_WindowWidth,(float)m_WindowHeight,0.0f); }	// �E�B���h�E�̈�擾
	
	float WindowAspect() const { return (float)m_ClientWidth/(float)m_ClientHeight; }						// �A�X�y�N�g����擾
	
//	float GetWidthMag() { return (float)(1920/1.5f) / fWindowWidth; }										// �t���X�N���[�����̕��g�嗦
//	float GetHeightMag() { return (float)(1080/1.5f) / fWindowHeight; }										// �t���X�N���[�����̍����g�嗦
	float GetWidthMag() { return (float)m_WindowWidth / fWindowWidth; }										// �t���X�N���[�����̕��g�嗦
	float GetHeightMag() { return (float)m_WindowHeight / fWindowHeight; }									// �t���X�N���[�����̍����g�嗦

	// ---- �Z�b�^�[ ----
	void SetWidth(int nWidth){ m_ClientWidth = m_WindowWidth = nWidth; }
	void SetHeight(int nHeight){ m_ClientHeight = m_WindowHeight = nHeight; }

private:
	// �R���X�g���N�^
	CWindow();

	//===== �����o�ϐ� =====
private:
	static CWindow* m_pWindow;

	HWND		m_WindowHandle;		// �E�B���h�E�n���h��
	MSG			m_MessageInfo;		// ���b�Z�[�W���
	WNDCLASSEX	m_Wcex;				// �E�B���h�E�N���X
	LPTSTR		m_WindowName;		// �E�B���h�E�̖��O
	int			m_ClientWidth;		// �N���C�A���g�̈�̕�
	int			m_ClientHeight;		// �N���C�A���g�̈�̍���
	int			m_WindowWidth;		// �E�B���h�E�̕�
	int			m_WindowHeight;		// �E�B���h�E�̍���
};

#endif