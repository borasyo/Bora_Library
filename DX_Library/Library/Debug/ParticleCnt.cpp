#include "particlecnt.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include "d3dx9.h"
#include "../DirectX/Direct3D.h"
#include "../DirectX/Window.h"

int			g_nCnt = 0;
LPD3DXFONT	g_pFont = NULL;		// D3DXFont �I�u�W�F�N�g

void SetFont() {

	D3DXCreateFont(CDirect3D::Create()->GetDirect3DDevice(), 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &g_pFont);
}

void SetCnt(int nCnt) {
	g_nCnt += nCnt;
}

void CntDraw()
{
	TCHAR szDebug[1024];
	szDebug[0] = _T('\0');	// �f�o�b�O�����񏉊���

	// FPS ����ʂɕ`�悷�邽�߂̕�������쐬
	char str[256];
	wsprintfA(str, "Particle : %d\n", g_nCnt);
	//lstrcat(szDebug, str);

	// �f�o�b�O������`��
	
	RECT rect = {0, 30, (LONG)CWindow::Instance()->GetClientWidth(), (LONG)CWindow::Instance()->GetClientHeight()};
	g_pFont->DrawTextA(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));

	g_nCnt = 0;
}

void DelFont() {
	
	if( g_pFont )
	{// ���\���p�t�H���g�̊J��
		g_pFont->Release();
		g_pFont = nullptr;
	}
}
