//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Particle2D.cpp]
// author : 大洞祥太
// 
// 2Dパーティクル基本クラス。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____PARTICLE2D_H_____
#define _____PARTICLE2D_H_____

#include "d3dx9.h"
#include <list>
#include "../Function/Define.h"
#include "../ObjectData/TextureManager.h"
#include "../Task/TaskManager.h"
#include "../DirectX/Direct3D.h"
#include "../Function/Define.h"

enum EShape {
	eBox = 0,			// ボックス
	eCircle,			// サークル(中抜き)
	eCircleXY,			// サークル(xy軸、中抜き)
	eCircleXZ,			// サークル(xz軸、中抜き)
	eCircleYZ,			// サークル(yz軸、中抜き)
	eBall,				// ボール(中あり)

	eMaxParticleCoord
};

struct TParticleParam
{
	ESynthetic		synthetic;			// 描画方法
	EShape			eShape;				// 生成範囲
	float			fDuration;			// 生成周期
	UINT			uMaxParticles;		// 最大パーティクル数
	bool			bLooping;			// 繰り返し
	float			fGravity;			// 重力加速度
	float			fStartSpeed;		// 初速
	float			fStartSpeed2;		// 初速2
	float			fStartSize;			// 初期サイズ
	float			fStartSize2;		// 初期サイズ2
	float			fStartRotation;		// 初期角度
	float			fStartRotation2;	// 初期角度2
	D3DCOLOR		cStartColor;		// 初期カラー
	D3DCOLOR		cStartColor2;		// 初期カラー2
	float			fStartLifetime;		// 寿命
	float			fStartLifetime2;	// 寿命2
	D3DXVECTOR3		StartRange;			// 初期出現範囲  (eBallの場合はxのみしか使わない)
	D3DXVECTOR3		StartRange2;		// 初期出現範囲2 (eBallの場合はxのみしか使わない)
	D3DXVECTOR3		NowRange;			// 現在出現範囲　(eBallの場合はxのみしか使わない)
	UINT			uRate;				// 1秒あたりのパーティクル生成数
	float			fCornAngle;			// コーン角度
	float			fRadius;			// 半径(180:半球、360:球)
	bool			bColorOverLifetime;	// 生存時間で色を変更(初期カラーが無効になる)
	D3DCOLOR		cOverLifetime[2];	// [0]:開始色、[1]:終了色
	bool			bSizeOverLifetime;	// 生存時間でサイズを変更(初期サイズが無効になる)
	float			fOverLifetime[2];	// [0]:開始サイズ、[1]:終了サイズ
};

struct TGrain {
	TGrain*		m_pBack;
	TGrain*		m_pNext;
	D3DXVECTOR3	m_pos;
	D3DXVECTOR3	m_startPos;
	D3DXVECTOR3	m_velocity;
	D3DXVECTOR3	m_accel;
	float		m_size;
	float		m_startSize;
	float		m_angle;
	D3DCOLOR	m_color;
	D3DCOLOR	m_startColor;
	float		m_lifetime;
	float		m_startLifetime;
};

class CParticle2D {

private:
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
	VERTEX_2D*  m_pVertex;
	WORD*		m_pIndex;
	
	std::wstring		m_FileName;
	CTextureManager*	m_pTextureManager; // 
	LPDIRECT3DDEVICE9	m_pD3DDevice;

	bool m_bPlay;
	bool m_bPause;
	bool m_bStop;

public:
	CParticle2D();
	CParticle2D(TParticleParam* ppp);
	virtual ~CParticle2D();

	// 基本関数
	bool Start();
	void Update(GameObject* pObj);
	void Draw();
	void Clear();
	
	void SetParam(TParticleParam& pp);
	void GetDefaultParam(TParticleParam& pp);
	
	void SetFileName( const std::wstring& filename );
	
	void Play();
	void Simulate();
	void Pause();
	void Stop();
	void Emit(int nParticle);
	void AddParticle(int nParticle);
	
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
		m_pp.StartRange = End;
	}

private:
	TGrain* New();
	void Delete(TGrain* p);
	void DrawLast();
};

#endif