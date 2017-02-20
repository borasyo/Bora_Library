//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Particle2D.cpp]
// author : �哴�ˑ�
// 
// 2D�p�[�e�B�N����{�N���X�B
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
	eBox = 0,			// �{�b�N�X
	eCircle,			// �T�[�N��(������)
	eCircleXY,			// �T�[�N��(xy���A������)
	eCircleXZ,			// �T�[�N��(xz���A������)
	eCircleYZ,			// �T�[�N��(yz���A������)
	eBall,				// �{�[��(������)

	eMaxParticleCoord
};

struct TParticleParam
{
	ESynthetic		synthetic;			// �`����@
	EShape			eShape;				// �����͈�
	float			fDuration;			// ��������
	UINT			uMaxParticles;		// �ő�p�[�e�B�N����
	bool			bLooping;			// �J��Ԃ�
	float			fGravity;			// �d�͉����x
	float			fStartSpeed;		// ����
	float			fStartSpeed2;		// ����2
	float			fStartSize;			// �����T�C�Y
	float			fStartSize2;		// �����T�C�Y2
	float			fStartRotation;		// �����p�x
	float			fStartRotation2;	// �����p�x2
	D3DCOLOR		cStartColor;		// �����J���[
	D3DCOLOR		cStartColor2;		// �����J���[2
	float			fStartLifetime;		// ����
	float			fStartLifetime2;	// ����2
	D3DXVECTOR3		StartRange;			// �����o���͈�  (eBall�̏ꍇ��x�݂̂����g��Ȃ�)
	D3DXVECTOR3		StartRange2;		// �����o���͈�2 (eBall�̏ꍇ��x�݂̂����g��Ȃ�)
	D3DXVECTOR3		NowRange;			// ���ݏo���͈́@(eBall�̏ꍇ��x�݂̂����g��Ȃ�)
	UINT			uRate;				// 1�b������̃p�[�e�B�N��������
	float			fCornAngle;			// �R�[���p�x
	float			fRadius;			// ���a(180:�����A360:��)
	bool			bColorOverLifetime;	// �������ԂŐF��ύX(�����J���[�������ɂȂ�)
	D3DCOLOR		cOverLifetime[2];	// [0]:�J�n�F�A[1]:�I���F
	bool			bSizeOverLifetime;	// �������ԂŃT�C�Y��ύX(�����T�C�Y�������ɂȂ�)
	float			fOverLifetime[2];	// [0]:�J�n�T�C�Y�A[1]:�I���T�C�Y
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

	// ��{�֐�
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
		m_pp.StartRange = End;
	}

private:
	TGrain* New();
	void Delete(TGrain* p);
	void DrawLast();
};

#endif