//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Particle3D.cpp]
// author : 大洞祥太
// 
// 3Dパーティクル基本クラス。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____PARTICLE3D_H_____
#define _____PARTICLE3D_H_____

#include "d3dx9.h"
#include <list>
#include "../Function/Define.h"
#include "../ObjectData/TextureManager.h"
#include "../Task/TaskManager.h"
#include "../DirectX/Direct3D.h"
#include "Particle2D.h"

struct TVertex {
	D3DVECTOR	m_pos;
	D3DVECTOR	m_normal;
	D3DCOLOR	m_diffuse;
	float		m_u, m_v;
};

class CParticle3D {

private:
	IDirect3DVertexBuffer9 		*pTopVerTex;	//頂点バッファ
	IDirect3DIndexBuffer9 		*pIndex;		//頂点インデックス

	D3DXVECTOR3			m_pos;
	TParticleParam		m_pp;	
	float				m_fTime;			// パーティクル生成時間
	float				m_fRate;			// パーティクル生成数ワーク
	UINT				m_uParticles;		// 残りパーティクル数
	ESynthetic			m_synthetic;
	
	float m_fStartAngle;	// 開始角
	float m_fEndAngle;		// 終了角

	TGrain*		m_pGrain;
	TGrain*		m_pUse;
	TGrain*		m_pUnused;
	UINT		m_uUse;
	TVertex*	m_pVertex;
	DWORD*		m_pIndex;
	
	std::wstring		m_FileName;
	CTextureManager*	m_pTextureManager; // 
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	
	bool m_bPlay;
	bool m_bPause;
	bool m_bStop;

public:
	CParticle3D();
	CParticle3D(TParticleParam* ppp);
	virtual ~CParticle3D();

	// 基本関数
	bool Start();
	void Update(GameObject* pObj);
	void Draw();
	void Clear();
	
	void SetParam(TParticleParam& pp);
	void GetDefaultParam(TParticleParam& pp);
	
	void SetFileName( const std::wstring& filename );
	// 
	void Play();
	void Simulate();
	void Pause();
	void Stop();
	void Emit(int nParticle);
	void AddParticle(int nParticle);

	// パーティクルの使用状況を取得
	bool GetPlay() { return m_bPlay; }
	bool GetPause() { return m_bPause; }
	bool GetStop() { return m_bStop; }
	
	// --- レートチェンジ
	void SetLoop(bool bLoop) { m_pp.bLooping = bLoop; }
	void ChangeRate(UINT uRate) { m_pp.uRate = uRate; }
	
	// --- カラーチェンジ
	void ChangeColorLifetimeStart(D3DXCOLOR Start) { ChangeColorLifetime(Start,m_pp.cOverLifetime[1]); }
	void ChangeColorLifetimeEnd(D3DXCOLOR End) { ChangeColorLifetime(m_pp.cOverLifetime[0],End); }
	void ChangeColorLifetime(D3DXCOLOR Start, D3DXCOLOR End) { 
		m_pp.cOverLifetime[0] = Start;
		m_pp.cOverLifetime[1] = End;
		m_pp.bColorOverLifetime = true;
	}

	void ChangeColorStart(D3DXCOLOR Start) { ChangeColor(Start, m_pp.cStartColor2); }
	void ChangeColorEnd(D3DXCOLOR End) { ChangeColor(m_pp.cStartColor, End); }
	void ChangeColor(D3DXCOLOR Start, D3DXCOLOR End) {
		m_pp.cStartColor = Start;
		m_pp.cStartColor2 = End;
		m_pp.bColorOverLifetime = false;
	}
	
	// --- スピードチェンジ
	void ChangeSpeedStart(float fStart) { m_pp.fStartSpeed = fStart; }
	void ChangeSpeedEnd(float fEnd) { m_pp.fStartSpeed2 = fEnd; }
	void ChangeSpeed(float fStart, float fEnd) {
		m_pp.fStartSpeed = fStart;
		m_pp.fStartSpeed2 = fEnd;
	}
	
	// --- サイズチェンジ
	void ChangeSizeLifetimeStart(float fStart) { ChangeSizeLifetime(fStart, m_pp.fOverLifetime[1]); }
	void ChangeSizeLifetimeEnd(float fEnd) { ChangeSizeLifetime(m_pp.fOverLifetime[0], fEnd); }
	void ChangeSizeLifetime(float fStart, float fEnd) {
		m_pp.fOverLifetime[0] = fStart;
		m_pp.fOverLifetime[1] = fEnd;
		m_pp.bSizeOverLifetime = true;
	}

	void ChangeSizeStart(float fStart) { ChangeSize(fStart, m_pp.fStartSize2); }
	void ChangeSizeEnd(float fEnd) { ChangeSize(m_pp.fStartSize, fEnd); }
	void ChangeSize(float fStart, float fEnd) {
		m_pp.fStartSize = fStart;
		m_pp.fStartSize2 = fEnd;
		m_pp.bSizeOverLifetime = false;
	}
	
	// --- 範囲チェンジ
	void ChangeRangeStart(D3DXVECTOR3 Start) { ChangeRange(Start, m_pp.StartRange2); }
	void ChangeRangeEnd(D3DXVECTOR3 End) { ChangeRange(m_pp.StartRange, End); }
	void ChangeRange(D3DXVECTOR3 Start, D3DXVECTOR3 End) { 
		m_pp.StartRange = Start;
		m_pp.StartRange2 = End;
	}

private:
	TGrain* New();
	void Delete(TGrain* p);
	void DrawLast();

	D3DXVECTOR3 GetRandomAngle(float fAngle);
};

#endif