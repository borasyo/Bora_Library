//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Object3D.h]
// author : 大洞祥太
// 
// GameObjectが3DModelオブジェクトの場合、これを合成する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____OBJECT_3D_MODEL_H_____
#define _____OBJECT_3D_MODEL_H_____

#include "d3dx9.h"
#include "../ObjectData/ModelManager.h"
#include "../Task/GameObject.h"
#include "../ObjectData/AnimationController.h"

class CObject3DModel {

private:
	LPCWSTR m_FileName;
	D3DXMATRIXA16 m_mtxWorld;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	CModelManager* m_pModelManager;
	CAnimationController m_AnimationManager;
	float m_fAnimSpeed;
	bool m_bAnim;
	D3DXCOLOR m_MaterialColor;
	
	static bool	m_bColDraw;
	LPD3DXMESH		m_pBBox;		// 境界ボックス メッシュ
	LPD3DXMESH		m_pBSphere;		// 境界球メッシュ
	D3DXVECTOR3		m_OldColSize;   // 過去コリジョンサイズ

public:
	CObject3DModel();
	virtual ~CObject3DModel();
	
	void SetMatrix( GameObject* pObj );
	void SetMatrix( const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const D3DXVECTOR3 Rot );
	void SetOffset( const D3DXVECTOR3 Pos );

	void Draw( GameObject* pObj, const bool bShadow = false );
	void Draw( GameObject* pObj, const D3DXVECTOR3 Pos, const D3DXVECTOR3 Size, const D3DXVECTOR3 Rot, const bool bShadow = false );
	void ColDraw(GameObject* pObj, D3DXCOLOR Color = D3DXCOLOR(0,1,1,0.25f));
	const LPCWSTR GetFileName();
	void SetFileName( const LPCWSTR& filename );

	D3DXCOLOR GetMaterialColor() { return m_MaterialColor; }
	void SetMaterialColor( const D3DXCOLOR Color );

	// アニメーションありの時のみ使う
	bool UpdateAnim();
	void SetAnimationController();
	void SetAnimSpeed( const float fAnimSpeed );
	void SetAnimFlg( const bool bFlg );
	CAnimationController* GetAnimationManager();
	
	D3DXMATRIX* GetBoneMatrixWithName(const LPSTR Name, eBonePlace BonePlace);
	
	// ---- Debug
	void SetMesh(GameObject* pObj);
	void DrawOBB(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color);
	void DrawAABB(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color);
	void DrawSphere(GameObject* pObj, D3DXMATRIX& world, D3DXCOLOR Color);
	static bool GetColDrawFlg() {return m_bColDraw;}
	static void SetColDrawFlg(bool bFlg) {m_bColDraw = bFlg;}
	static void ChangeColDrawFlg() {m_bColDraw = !m_bColDraw;}
};

#endif