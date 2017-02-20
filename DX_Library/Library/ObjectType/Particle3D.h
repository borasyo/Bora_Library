//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Particle3D.cpp]
// author : �哴�ˑ�
// 
// 3D�p�[�e�B�N����{�N���X�B
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
	IDirect3DVertexBuffer9 		*pTopVerTex;	//���_�o�b�t�@
	IDirect3DIndexBuffer9 		*pIndex;		//���_�C���f�b�N�X

	D3DXVECTOR3			m_pos;
	TParticleParam		m_pp;	
	float				m_fTime;			// �p�[�e�B�N����������
	float				m_fRate;			// �p�[�e�B�N�����������[�N
	UINT				m_uParticles;		// �c��p�[�e�B�N����
	ESynthetic			m_synthetic;
	
	float m_fStartAngle;	// �J�n�p
	float m_fEndAngle;		// �I���p

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

	// ��{�֐�
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

	// �p�[�e�B�N���̎g�p�󋵂��擾
	bool GetPlay() { return m_bPlay; }
	bool GetPause() { return m_bPause; }
	bool GetStop() { return m_bStop; }
	
	// --- ���[�g�`�F���W
	void SetLoop(bool bLoop) { m_pp.bLooping = bLoop; }
	void ChangeRate(UINT uRate) { m_pp.uRate = uRate; }
	
	// --- �J���[�`�F���W
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
	
	// --- �X�s�[�h�`�F���W
	void ChangeSpeedStart(float fStart) { m_pp.fStartSpeed = fStart; }
	void ChangeSpeedEnd(float fEnd) { m_pp.fStartSpeed2 = fEnd; }
	void ChangeSpeed(float fStart, float fEnd) {
		m_pp.fStartSpeed = fStart;
		m_pp.fStartSpeed2 = fEnd;
	}
	
	// --- �T�C�Y�`�F���W
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
	
	// --- �͈̓`�F���W
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