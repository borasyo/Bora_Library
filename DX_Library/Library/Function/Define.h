//=======================================================================================
//
//	  �萔��`�A�}�N����`
//
//=======================================================================================

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DEFINE_H_____
#define _____DEFINE_H_____

// --- �C���N���[�h�錾
#include <tchar.h>
#include <string>
#include "d3dx9.h"

// --- �萔
const float Pai = 3.141592653589793f;
const D3DXVECTOR3 LimitPos = D3DXVECTOR3( 140.0f, 0.0f, 140.0f ); // �ړ��͈͐���

const float fWindowWidth = 1920/2.0f;
const float fWindowHeight = 1080/2.0f;

const int nDefaultFrameRate = 60;

// Debug
#if _DEBUG
#define DEBUG
#endif

// --- �E�B���h�E�l�[��
const LPTSTR WindowName = _T("�A�E��i");

// --- �t�H���_�p�X
const LPSTR TextureFolderPath = "data/Texture/";
const LPSTR ModelTextureFolderPath = "data/Texture/ModelTexture/";
const std::wstring ModelFolderPath = _T("data/Model/");

// --- �}�E�X���
const bool bStartMouthDraw = true;
const std::wstring MouthTextureName = _T("MouthPoint.png");
const D3DXVECTOR3 MouthTextureSize = D3DXVECTOR3(17.5f,25.0f,1.0f) * 1.3f;
const D3DXVECTOR3 MouthPosRivision = D3DXVECTOR3(-5.0f,-5.0f,0.0f) * 1.3f;

// --- ON�EOFF
//#define LIMIT_MOUTH				//	�}�E�X�̈ړ����E�B���h�E���ɐ������邩
const bool bWindowMode = true;	// Window���[�h�ɂ��邩�ǂ���

// --- �}�N��
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x)			if(x){ x->Release(); x=NULL; }
#endif
#ifndef SAFE_DELETE
#define SAFE_DELETE(x)			if(x){ delete x; x=NULL; }
#endif
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(x)	if(x){ delete[] x; x=NULL; }
#endif

#define D3DXVECTOR3_ZERO	D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) 
#define D3DXVECTOR3_ONE		D3DXVECTOR3( 1.0f, 1.0f, 1.0f ) 
#define D3DXVECTOR3_UP		D3DXVECTOR3( 0.0f, 1.0f, 0.0f ) 
#define D3DXVECTOR3_DOWN	D3DXVECTOR3( 0.0f,-1.0f, 0.0f ) 
#define D3DXVECTOR3_FORWARD	D3DXVECTOR3( 0.0f, 0.0f, 1.0f ) 
#define D3DXVECTOR3_BACK	D3DXVECTOR3( 0.0f, 0.0f,-1.0f ) 
#define D3DXVECTOR3_LEFT	D3DXVECTOR3(-1.0f, 0.0f, 0.0f ) 
#define D3DXVECTOR3_RIGHT	D3DXVECTOR3( 1.0f, 0.0f, 0.0f ) 
 
#define D3DXVECTOR3_UP_2D	D3DXVECTOR3( 0.0f,-1.0f, 0.0f )	//	2D���W�ɂ�����y�A�b�v
#define D3DXVECTOR3_DOWN_2D	D3DXVECTOR3( 0.0f, 1.0f, 0.0f )	//	2D���W�ɂ�����y�_�E�� 

#define D3DXVECTOR2_ZERO	D3DXVECTOR2( 0.0f, 0.0f ) 
#define D3DXVECTOR2_ONE		D3DXVECTOR2( 1.0f, 1.0f ) 

#define D3DXCOLOR_WHITE		D3DXCOLOR(1.0f,1.0f,1.0f,1.0f)
#define D3DXCOLOR_RED		D3DXCOLOR(1.0f,0.0f,0.0f,1.0f)
#define D3DXCOLOR_GREEN		D3DXCOLOR(0.0f,1.0f,0.0f,1.0f)
#define D3DXCOLOR_BLUE		D3DXCOLOR(0.0f,0.0f,1.0f,1.0f)
#define D3DXCOLOR_MAGENTA	D3DXCOLOR(1.0f,0.0f,1.0f,1.0f)
#define D3DXCOLOR_CYAN		D3DXCOLOR(0.0f,1.0f,1.0f,1.0f)
#define D3DXCOLOR_YELLOW	D3DXCOLOR(1.0f,1.0f,0.0f,1.0f)
#define D3DXCOLOR_BLACK		D3DXCOLOR(0.0f,0.0f,0.0f,1.0f)
#define D3DXCOLOR_GRAY		D3DXCOLOR(0.5f,0.5f,0.5f,1.0f)

// --- �ėp�񋓌^
enum ESynthetic {
	eNone = 0,		// �ʏ�`��
	eAdditive,		// ���Z����
	eAlphaBlend,	// ����������
	eSubtractive,	// ���Z����

	eMaxSynthetic
};

#define NUM_VERTEX  (4) // ���_��(�Œ�)
#define NUM_POLYGON (2) // �|���S����(�Œ�)
#define	FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 ) // ���_�t�H�[�}�b�g( ���_���W[2D] / ���_�J���[ / �e�N�X�`�� )

// --- 2DTexture�\����
typedef struct _VERTEX_2D	// ���_�t�H�[�}�b�g�ɍ��킹���\����
{
	D3DXVECTOR3	pos;			// ���_���W
	float		rhw;			// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR	col;			// ���_�J���[
	D3DXVECTOR2 tex;			// �e�N�X�`�����W
} VERTEX_2D;


//	---- DebugLog�֌W
#define DebugLog(String) std::cout << String << std::endl;
#define DebugLogVec2(Name, Vec2) std::cout << Name << "(" << Vec2.x << "," << Vec2.y << ")" << std::endl;
#define DebugLogVec3(Name, Vec3) std::cout << Name << "(" << Vec3.x << "," << Vec3.y << "," << Vec3.z << ")" << std::endl;
#define DebugLogColor(Name, Col) std::cout << Name << "(" << Col.r << "," << Col.g << "," << Col.b << "," << Col.a << ")" << std::endl;


#endif