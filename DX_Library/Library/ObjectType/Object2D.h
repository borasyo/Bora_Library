//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object2D.h]
// author : �哴�ˑ�
//
// GameObject��2D�I�u�W�F�N�g�̏ꍇ�A�������������B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____TEXTURE_DRAW_H_____
#define _____TEXTURE_DRAW_H_____

#include "d3dx9.h"
#include "../Task/GameObject.h"
#include "../ObjectData/TextureManager.h"
#include "../Function/Define.h"

// ---- Class
class CObject2D {

private:
	std::wstring m_FileName;
	VERTEX_2D m_Vertex[NUM_VERTEX]; // ���_���
	LPDIRECT3DDEVICE9 m_pD3DDevice; // DirectXDevice
	CTextureManager* m_pTextureManager; // 
	D3DXVECTOR2 m_Divide;
	ESynthetic m_Synthetic; // �`����@

public:	
	CObject2D();
	~CObject2D();

	// �`��֐�
	void Draw( GameObject* pObj );
	void Draw( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const float fRot = 0.0f );

	// ���W�X�V
	void SetVertexPolygon( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Scale, const float fRot );
	void SetVertexColor( const D3DCOLOR Color );
	void SetVertexTexture( const D3DXVECTOR2 Pattern ); // �������A���p�^�[���ڂ�
	void SetDivide( const D3DXVECTOR2 Divide ){ m_Divide = Divide; }

	void ChangeAlpha(float fAlpha);
	void ChangeAlpha(int nAlpha);

	// ���_��񏉊���
	void MakeVertexPolygon();

	// �`����@�Z�b�g
	void SetSynthetic(ESynthetic Synthetic) { m_Synthetic = Synthetic; }

	// �Q�b�^�[�Z�b�^�[
	const std::wstring GetFileName() { return m_FileName; }
	void SetFileName( const std::wstring& filename );
};

#endif;