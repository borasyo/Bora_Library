//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Model.h]
// author : �哴�ˑ�
// 
// ���f����ǂݍ��݂��̃f�[�^��ێ�����
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MODEL_H_____
#define _____MODEL_H_____

#include <map>
#include <list>
#include "d3dx9.h"
#include <string>
#include <tchar.h>
#include "D3DXAllocateHierarchy.h"
#include "FrameMatrixTransformer.h"
#include "AnimationMeshDrawer.h"

enum eBonePlace {

	Place_Tip = 0,	// ��[
	Place_Center,	// ���S
	Place_Root,		// ����

	PLACE_MAX
};

// 1���f���ɕK�v�ȏ��
class CModel {

public:
	CModel();
	~CModel();

	// 3D���f���֌W
	bool LoadModel( const std::wstring& filename );
	void RenderModel( const D3DXMATRIXA16* pMtx, const bool bShadow, D3DXCOLOR MaterialColor );
	void Uninit();
	LPD3DXANIMATIONCONTROLLER GetMainAnimationController();
	D3DXMATRIX* GetBoneMatrixWithName(const LPSTR BoneName, eBonePlace BonePlace, SkinMesh::TMyD3DXFRAME* pRootFrame = nullptr);

private:
	void SetMaterialColor( const D3DXCOLOR Color );
	void SetMaterialColor( const std::list<D3DXCOLOR> Color );
	std::list<D3DXCOLOR> GetMaterialColor();

private:

	// �A�j���[�V�����Ȃ�
	LPD3DXMESH				m_Mesh;
	D3DMATERIAL9*			m_Materials;
	LPDIRECT3DTEXTURE9*		m_Textures;
	DWORD					m_NumMaterials;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	D3DXATTRIBUTERANGE*		m_pAttr;	// �����e�[�u��
	DWORD					m_dwAttr;	// ������
	
	// �A�j���[�V��������
	SkinMesh::TMyD3DXFRAME*	m_pRootFrame;
	SkinMesh::CD3DXAllocateHierarchy m_Allocater;
	SkinMesh::CAnimationMeshDrawer m_AMDrawer;
	SkinMesh::CFrameMatrixTransformer m_FMTransformer;
	LPD3DXANIMATIONCONTROLLER m_pMainAnimationController;
	
	void SetModel();
	void DrawShadow();
};

#endif