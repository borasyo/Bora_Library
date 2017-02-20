//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [Particle3D.cpp]
// author : 大洞祥太
// 
// 3Dパーティクル基本クラス。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "Particle3D.h"
#include "../Debug/ParticleCnt.h"

// ---- マクロ
#define FVF_PVERTEX			(D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)
#define frand()				(rand()/(float)RAND_MAX)
const float fRangeRivision = 1000.0f;  
const float fAngleRivision = 0.8f;

// デフォルト パラメータ取得
void CParticle3D::GetDefaultParam(TParticleParam& pp) {
	pp.fDuration = 10.0f;
	pp.uMaxParticles = 10000;
	pp.eShape = eBox;
	pp.synthetic = eAlphaBlend;
	pp.bLooping = true;
	pp.fGravity = 9.8f;
	pp.fStartSpeed = 25.0f;
	pp.fStartSpeed2 = 35.0f;
	pp.fStartSize = 1.0f;
	pp.fStartSize2 = 1.0f;
	pp.fStartRotation = 0.0f;
	pp.fStartRotation2 = pp.fStartRotation;
	pp.cStartColor = D3DCOLOR_ARGB(127, 191, 255, 255);
	pp.cStartColor2 = pp.cStartColor;
	pp.fStartLifetime = 5.0f;
	pp.fStartLifetime2 = pp.fStartLifetime;
	pp.StartRange = D3DXVECTOR3_ZERO;
	pp.StartRange2 = D3DXVECTOR3_ZERO;
	pp.NowRange = D3DXVECTOR3_ZERO;
	pp.uRate = 600;
	pp.fCornAngle = 20.0f;
	pp.fRadius = 0.0f;
	pp.bColorOverLifetime = true;
	pp.cOverLifetime[0] = D3DCOLOR_ARGB(127, 191, 255, 255);
	pp.cOverLifetime[1] = D3DCOLOR_ARGB(0, 255, 255, 255);
	pp.bSizeOverLifetime = true;
	pp.fOverLifetime[0] = 1.0f;
	pp.fOverLifetime[1] = 10.0f;
}

// コンストラクタ
CParticle3D::CParticle3D() {

	GetDefaultParam(m_pp);
	m_synthetic = m_pp.synthetic;
	m_fTime = 0.0f;
	m_fRate = 0.0f;
	m_uParticles = m_pp.uMaxParticles;

	m_pGrain = nullptr;
	m_pUse = nullptr;
	m_uUse = 0;
	m_pUnused = nullptr;

	m_pVertex = nullptr;
	m_pIndex = nullptr;
	
	m_pos = D3DXVECTOR3(0,0,0);
}

CParticle3D::CParticle3D(TParticleParam* ppp) {

	GetDefaultParam(m_pp);
	m_synthetic = m_pp.synthetic;
	m_fTime = 0.0f;
	m_fRate = 0.0f;
	m_uParticles = m_pp.uMaxParticles;

	m_pGrain = nullptr;
	m_pUse = nullptr;
	m_uUse = 0;
	m_pUnused = nullptr;

	m_pVertex = nullptr;
	m_pIndex = nullptr;

	if (ppp) {
		SetParam(*ppp);
	}
	
	m_pos = D3DXVECTOR3(0,0,0);
}

// デストラクタ
CParticle3D::~CParticle3D() {
	Clear();
}

// パラメータ更新
void CParticle3D::SetParam(TParticleParam& pp) {
	m_pp = pp;
	if (m_pp.fStartSpeed > m_pp.fStartSpeed2) {
		float fSpeed = m_pp.fStartSpeed;
		m_pp.fStartSpeed = m_pp.fStartSpeed2;
		m_pp.fStartSpeed2 = fSpeed;
	}
	if (m_pp.fStartSize > m_pp.fStartSize2) {
		float fSize = m_pp.fStartSize;
		m_pp.fStartSize = m_pp.fStartSize2;
		m_pp.fStartSize2 = fSize;
	}
	if (m_pp.fStartRotation > m_pp.fStartRotation2) {
		float fRotation = m_pp.fStartRotation;
		m_pp.fStartRotation = m_pp.fStartRotation2;
		m_pp.fStartRotation2 = fRotation;
	}
	if (m_pp.fStartLifetime > m_pp.fStartLifetime2) {
		float fLifetime = m_pp.fStartLifetime;
		m_pp.fStartLifetime = m_pp.fStartLifetime2;
		m_pp.fStartLifetime2 = fLifetime;
	}
	/*if (m_pp.StartRange > m_pp.StartRange2) {
		D3DXVECTOR3 Erea = m_pp.StartRange;
		m_pp.StartRange = m_pp.StartRange2;
		m_pp.StartRange2 = Erea;
	}*/
	m_pp.NowRange = m_pp.StartRange; // 初期範囲格納
	UINT uA = HIBYTE(HIWORD(m_pp.cStartColor));
	UINT uR = LOBYTE(HIWORD(m_pp.cStartColor));
	UINT uG = HIBYTE(LOWORD(m_pp.cStartColor));
	UINT uB = LOBYTE(m_pp.cStartColor);
	UINT uA2 = HIBYTE(HIWORD(m_pp.cStartColor2));
	UINT uR2 = LOBYTE(HIWORD(m_pp.cStartColor2));
	UINT uG2 = HIBYTE(LOWORD(m_pp.cStartColor2));
	UINT uB2 = LOBYTE(m_pp.cStartColor2);
	bool bChange = false;
	if (uA > uA2) {UINT u = uA; uA = uA2; uA2 = u;bChange = true;}
	if (uR > uR2) {UINT u = uR; uR = uR2; uR2 = u;bChange = true;}
	if (uG > uG2) {UINT u = uG; uG = uG2; uG2 = u;bChange = true;}
	if (uB > uB2) {UINT u = uB; uB = uB2; uB2 = u;bChange = true;}
	if (bChange) {
		m_pp.cStartColor = D3DCOLOR_ARGB(uA, uR, uG, uB);
		m_pp.cStartColor2 = D3DCOLOR_ARGB(uA2, uR2, uG2, uB2);
	}
	m_fTime = 0.0f;
	m_fRate = 0.0f;
	m_uParticles = m_pp.uMaxParticles;
	m_synthetic = m_pp.synthetic;

	m_fStartAngle = cosf(0.0f);									// 開始角
	m_fEndAngle = cosf(D3DXToRadian(m_pp.fCornAngle / 2.0f));	// 終了角
}

bool CParticle3D::Start() {
	
	m_pTextureManager = CTextureManager::Create();
	m_pD3DDevice = CDirect3D::Create()->GetDirect3DDevice();

	SAFE_DELETE_ARRAY(m_pIndex);
	SAFE_DELETE_ARRAY(m_pVertex);
	SAFE_DELETE_ARRAY(m_pGrain);
	m_pUse = m_pUnused = nullptr;

	m_pGrain = new TGrain[m_pp.uMaxParticles];
	m_pGrain[0].m_pBack = nullptr;
	m_pGrain[0].m_pNext = &m_pGrain[1];
	for (UINT i = 1; i < m_pp.uMaxParticles - 1; ++i) {
		m_pGrain[i].m_pNext = &m_pGrain[i + 1];
		m_pGrain[i].m_pBack = &m_pGrain[i - 1];
	}
	m_pGrain[m_pp.uMaxParticles - 1].m_pBack = &m_pGrain[m_pp.uMaxParticles - 2];
	m_pGrain[m_pp.uMaxParticles - 1].m_pNext = nullptr;
	m_pUse = nullptr;
	m_uUse = 0;
	m_pUnused = &m_pGrain[0];

	m_pVertex = new TVertex[m_pp.uMaxParticles * 4];
	m_pIndex = new DWORD[m_pp.uMaxParticles * 6];
	
	m_bPlay = true;
	m_bPause = false;
	m_bStop = false;

	return true;
}

void CParticle3D::Clear() {
	SAFE_DELETE_ARRAY(m_pIndex);
	SAFE_DELETE_ARRAY(m_pVertex);
	SAFE_DELETE_ARRAY(m_pGrain);
	m_pUse = m_pUnused = nullptr;
}

void CParticle3D::Delete(TGrain* p) {
	if (p->m_pBack) {
		p->m_pBack->m_pNext = p->m_pNext;
	} else {
		m_pUse = p->m_pNext;
	}
	if (p->m_pNext) {
		p->m_pNext->m_pBack = p->m_pBack;
	}

	p->m_pBack = nullptr;
	p->m_pNext = m_pUnused;
	if (m_pUnused) {
		m_pUnused->m_pBack = p;
	}
	m_pUnused = p;

	--m_uUse;
}

TGrain* CParticle3D::New() {
	
	if (!m_pUnused) {
		return nullptr;
	}

	TGrain* p = m_pUnused;
	m_pUnused = m_pUnused->m_pNext;
	if (m_pUnused) {
		m_pUnused->m_pBack = nullptr;
	}
	p->m_pNext = m_pUse;
	if (m_pUse) {
		m_pUse->m_pBack = p;
	}
	m_pUse = p;

	// 初期値設定
	p->m_pos = m_pos;
	p->m_pos.y += m_pp.fStartSize2 * 0.5f;
	p->m_accel = D3DXVECTOR3(0.0f, -m_pp.fGravity, 0.0f);
	float theta = acosf(m_fStartAngle - frand() * (m_fStartAngle - m_fEndAngle));
	float r = sinf(theta);
	float eta = frand() * 2.0f * D3DX_PI;
	p->m_velocity.x = r * cosf(eta);
	p->m_velocity.y = cosf(theta);
	p->m_velocity.z = r * sinf(eta);
	D3DXVec3Normalize(&p->m_velocity, &p->m_velocity);
	//p->m_pos += p->m_velocity * m_pp.fRadius;
	float fAngle = 0.0f;
	float fRange = 0.0f;
	D3DXVECTOR3 Range = D3DXVECTOR3_ZERO;
	switch (m_pp.eShape) {
	
	case eBox:
		Range.x = rand()%(int)(m_pp.NowRange.x*fRangeRivision) / fRangeRivision - (m_pp.NowRange.x/2.0f);
		Range.y = rand()%(int)(m_pp.NowRange.y*fRangeRivision) / fRangeRivision - (m_pp.NowRange.y/2.0f);
		Range.z = rand()%(int)(m_pp.NowRange.z*fRangeRivision) / fRangeRivision - (m_pp.NowRange.z/2.0f);
		p->m_pos.x += Range.x;
		p->m_pos.y += Range.y;
		p->m_pos.z += Range.z; 
		break;

	case eCircleXY:
		fAngle = rand()%(int)(6.28f*fRangeRivision) / fRangeRivision;
		p->m_pos.x += sinf(fAngle) * m_pp.NowRange.x;
		p->m_pos.y += cosf(fAngle) * m_pp.NowRange.y;
		break;

	case eCircleYZ:
		fAngle = rand()%(int)(6.28f*fRangeRivision) / fRangeRivision;
		p->m_pos.y += sinf(fAngle) * m_pp.NowRange.y;
		p->m_pos.z += cosf(fAngle) * m_pp.NowRange.z;
		break;

	case eCircleXZ:
		fAngle = rand()%(int)(6.28f*fRangeRivision) / fRangeRivision;
		p->m_pos.x += cosf(fAngle) * m_pp.NowRange.x;
		p->m_pos.z += sinf(fAngle) * m_pp.NowRange.z;
		break;
		
	case eBall:
		fRange = (m_pp.NowRange.x/2.0f)*(m_pp.NowRange.x/2.0f);

		if(fRange <= 0.0f)
			break;
		
		Range.x = rand()%(int)(m_pp.NowRange.x*fRangeRivision) / fRangeRivision - (m_pp.NowRange.x/2.0f);
		fRange -= Range.x * Range.x;
		if(fRange <= 0.0f) {
			Range.y = 0.0f;
			Range.z = 0.0f;
		} else {
			Range.y = rand()%(int)(m_pp.NowRange.x*fRangeRivision) / fRangeRivision - (m_pp.NowRange.x/2.0f);
			if(fRange - (Range.y * Range.y) <= 0.0f) {
				if(rand()%2) {
					Range.y = sqrt(fRange);
				} else {
					Range.y = -sqrt(fRange);
				}
				Range.z = 0.0f;
			} else {
				fRange -= Range.y * Range.y;
				if(rand()%2) {
					Range.z = sqrt(fRange);
				} else {
					Range.z = -sqrt(fRange);
				}
			}
		}
		p->m_pos += Range;
		break;

	case eCircle:
	default:
		break;
	}
	p->m_startPos = p->m_pos;
	p->m_velocity *= m_pp.fStartSpeed + (m_pp.fStartSpeed2 - m_pp.fStartSpeed) * frand();
	p->m_size = m_pp.fStartSize + (m_pp.fStartSize2 - m_pp.fStartSize) * frand();
	p->m_startSize = p->m_size;
	p->m_angle = m_pp.fStartRotation + (m_pp.fStartRotation2 - m_pp.fStartRotation) * frand();
	UINT uA = HIBYTE(HIWORD(m_pp.cStartColor));
	UINT uR = LOBYTE(HIWORD(m_pp.cStartColor));
	UINT uG = HIBYTE(LOWORD(m_pp.cStartColor));
	UINT uB = LOBYTE(m_pp.cStartColor);
	UINT uA2 = HIBYTE(HIWORD(m_pp.cStartColor2));
	UINT uR2 = LOBYTE(HIWORD(m_pp.cStartColor2));
	UINT uG2 = HIBYTE(LOWORD(m_pp.cStartColor2));
	UINT uB2 = LOBYTE(m_pp.cStartColor2);
	uA += (uA2 - uA) * rand() / RAND_MAX;
	uR += (uR2 - uR) * rand() / RAND_MAX;
	uG += (uG2 - uG) * rand() / RAND_MAX;
	uB += (uB2 - uB) * rand() / RAND_MAX;
	p->m_color = D3DCOLOR_ARGB(uA, uR, uG, uB);
	p->m_startColor = p->m_color;
	p->m_lifetime = m_pp.fStartLifetime + (m_pp.fStartLifetime2 - m_pp.fStartLifetime) * frand();
	p->m_startLifetime = p->m_lifetime;

	++m_uUse;
	return p;	
}

// 更新
void CParticle3D::Update(GameObject* pObj) {

	if(m_bPause || m_bStop) {
		SetCnt((int)m_uUse);
		return;
	}
	
	// 座標更新	
	m_pos = *(pObj->GetPosition());

	// デルタタイム取得
	float fDeltaTime = (float)CTime::GetDeltaTime();

	// 生成
	if (m_uParticles) {
		m_fRate += m_pp.uRate * fDeltaTime;
		while (m_fRate >= 1.0f) {
			m_fRate -= 1.0f;
			--m_uParticles;		
			if(!New())
				break; // 生成できないならbreak
		}
	}
	
	GameObject* pCamera = TaskManager::Instance()->FindWithTag("Camera");
	D3DXMATRIX& mView = *(pCamera->GetMatrix());
	D3DXMATRIX mBB(mView._11, mView._21, mView._31, 0.0f,
				   mView._12, mView._22, mView._32, 0.0f,
				   mView._13, mView._23, mView._33, 0.0f,
				   0.0f, 0.0f, 0.0f, 1.0f);
	D3DXMATRIX mRZ, mtx;
	TGrain* pNext = nullptr;
	TVertex* pV = m_pVertex;
	DWORD* pI = m_pIndex;
	DWORD wIndex = 0;
	for (TGrain* p = m_pUse; p; p = pNext) {
		pNext = p->m_pNext;
		// 更新
		p->m_lifetime -= fDeltaTime;
		if (p->m_lifetime <= 0.0f) {
			Delete(p);
			continue;
		}
		p->m_velocity += p->m_accel * fDeltaTime;
		p->m_pos += p->m_velocity * fDeltaTime;
		//if (p->m_pos.y <= -p->m_size * 2.0f) {
		//	Delete(p);
		//	continue;
		//}
		float delta;
		if (m_pp.bColorOverLifetime || m_pp.bSizeOverLifetime) {
			delta = p->m_lifetime / p->m_startLifetime;
		}
		if (m_pp.bColorOverLifetime) {
			int nA = HIBYTE(HIWORD(m_pp.cOverLifetime[0]));
			int nR = LOBYTE(HIWORD(m_pp.cOverLifetime[0]));
			int nG = HIBYTE(LOWORD(m_pp.cOverLifetime[0]));
			int nB = LOBYTE(m_pp.cOverLifetime[0]);
			int nA2 = HIBYTE(HIWORD(m_pp.cOverLifetime[1]));
			int nR2 = LOBYTE(HIWORD(m_pp.cOverLifetime[1]));
			int nG2 = HIBYTE(LOWORD(m_pp.cOverLifetime[1]));
			int nB2 = LOBYTE(m_pp.cOverLifetime[1]);
			nA = (int)(nA2 + (nA - nA2) * delta);
			nR = (int)(nR2 + (nR - nR2) * delta);
			nG = (int)(nG2 + (nG - nG2) * delta);
			nB = (int)(nB2 + (nB - nB2) * delta);
			p->m_color = D3DCOLOR_ARGB(nA, nR, nG, nB);
		}
		if (m_pp.bSizeOverLifetime) {
			p->m_size = m_pp.fOverLifetime[1] + (m_pp.fOverLifetime[0] - m_pp.fOverLifetime[1]) * delta;
		}
		// 頂点構築
		D3DXMatrixRotationZ(&mRZ, D3DXToRadian(p->m_angle));
		mBB._41 = p->m_pos.x;
		mBB._42 = p->m_pos.y;
		mBB._43 = p->m_pos.z;
		mtx = mRZ * mBB;
		D3DXVECTOR3 pos;
		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * -0.5f, p->m_size * 0.5f, 0.0f), &mtx);
		pV[0].m_pos = pos;
		D3DXVec3TransformNormal(&pos, &D3DXVECTOR3(0.0f, 0.0f, -1.0f), &mtx);
		pV[0].m_normal = pos;
		pV[0].m_diffuse = p->m_color;
		pV[0].m_u = 0.0f, pV[0].m_v = 0.0f;
		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * 0.5f, p->m_size * 0.5f, 0.0f), &mtx);
		pV[1].m_pos = pos;
		pV[1].m_normal = pV[0].m_normal;
		pV[1].m_diffuse = p->m_color;
		pV[1].m_u = 1.0f, pV[1].m_v = 0.0f;
		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * -0.5f, p->m_size * -0.5f, 0.0f), &mtx);
		pV[2].m_pos = pos;
		pV[2].m_normal = pV[0].m_normal;
		pV[2].m_diffuse = p->m_color;
		pV[2].m_u = 0.0f, pV[2].m_v = 1.0f;
		D3DXVec3TransformCoord(&pos, &D3DXVECTOR3(p->m_size * 0.5f, p->m_size * -0.5f, 0.0f), &mtx);
		pV[3].m_pos = pos;
		pV[3].m_normal = pV[0].m_normal;
		pV[3].m_diffuse = p->m_color;
		pV[3].m_u = 1.0f, pV[3].m_v = 1.0f;
		pV += 4;
		// インデックス構築
		pI[0] = wIndex + 0;
		pI[1] = wIndex + 1;
		pI[2] = wIndex + 2;
		pI[3] = wIndex + 2;
		pI[4] = wIndex + 1;
		pI[5] = wIndex + 3;
		pI += 6;
		wIndex += 4;
	}

	// 時間を進める
	m_fTime += fDeltaTime;
	if (m_fTime >= m_pp.fDuration) {
		m_fRate = 0.0f;
		if (m_pp.bLooping) {
			m_fTime = 0.0f;
			m_uParticles = m_pp.uMaxParticles;
		} else {
			// Particleがすべて消えたら
			if((int)m_uUse <= 0) {
				m_bPlay = false;
			}
			m_fTime = m_pp.fDuration;
			m_uParticles = 0;
		}
	}
	m_pp.NowRange = m_pp.StartRange + (m_pp.StartRange2 - m_pp.StartRange) * (m_fTime/m_pp.fDuration);
	
#ifdef DEBUG
	SetCnt((int)m_uUse);
#endif
}

void CParticle3D::Draw() {
	DrawLast();
}

void CParticle3D::DrawLast() {
	
	if (!m_uUse || m_bStop) {
		return;
	}

	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	m_pD3DDevice->SetTransform(D3DTS_WORLD, &mWorld);
	
	switch (m_pp.synthetic) {
	case eSubtractive:		// 減算合成
		m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT );
		m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
		m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE );
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティングしない
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		// THRU
	case eAdditive:			// 加算合成
		m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE); 
		m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE); 
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					// ライティングしない
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	default:
		break;
	}
	
	m_pD3DDevice->SetFVF(FVF_PVERTEX);
	const D3DMATERIAL9 material = {
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		0.0f,
	};

	// マテリアルテクスチャセット
	m_pD3DDevice->SetMaterial(&material);
	m_pD3DDevice->SetTexture(0, m_pTextureManager->LoadTexture(m_FileName));									// テクスチャを登録

	// 描画実行
	m_pD3DDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, m_uUse * 4, m_uUse * 2, m_pIndex, D3DFMT_INDEX32, m_pVertex, sizeof(TVertex));

	// 通常ブレンド
	m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Zバッファ更新を有効に
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);				// ライティングする
	m_pD3DDevice->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
	m_pD3DDevice->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	m_pD3DDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
}

// ---- セッター
void CParticle3D::SetFileName( const std::wstring& filename ){
	m_FileName = filename;
}

D3DXVECTOR3 CParticle3D::GetRandomAngle(float fAngle) {
	D3DXVECTOR3 random;
	float cos = cosf(fAngle);
	float sin = sinf(fAngle);

	switch(rand()%4) {
		
	case 0:
		random = D3DXVECTOR3(cos,0,cos); 
		break;
	case 1:
		random = D3DXVECTOR3(sin,0,cos); 
		break;
	case 2:
		random = D3DXVECTOR3(cos,0,sin); 
		break;
	case 3:
		random = D3DXVECTOR3(sin,0,sin); 
		break;
	}

	return random;
}

// ---- パーティクルシステムONOFF管理	

// 初めから再生
void CParticle3D::Play() {
	
	m_fTime = 0.0f;
	m_uParticles = m_pp.uMaxParticles;
	
	m_bPlay = true;
	m_bPause = false;
	m_bStop = false;
	
	if(!m_pUse) 
		return;
	
	// すべて削除
	TGrain* pNext = nullptr;
	for (TGrain* p = m_pUse; p; p = pNext) {
		pNext = p->m_pNext;
		Delete(p);
	}
}

// 再生再開
void CParticle3D::Simulate() {
	
	m_bPlay = true;
	m_bPause = false;
	m_bStop = false;
}

/// 更新だけを止める
void CParticle3D::Pause() {

	m_bPlay = false;
	m_bPause = true;
	m_bStop = false;
}

// パーティクルシステム自体を完全停止
void CParticle3D::Stop() {
	
	m_bPlay = false;
	m_bPause = false;
	m_bStop = true;
	
	if(!m_pUse) 
		return;
	
	// すべて削除
	TGrain* pNext = nullptr;
	for (TGrain* p = m_pUse; p; p = pNext) {
		pNext = p->m_pNext;
		Delete(p);
	}
}

// 指定した個数分パーティクルを臨時に生成
void CParticle3D::Emit(int nParticle) {

	for(int i = 0; i < nParticle; i++) {
		New();
	}
}

// 残りパーティクル数を増やす
void CParticle3D::AddParticle(int nParticle) {

	m_uParticles += nParticle;
}

	/*
	//--------------------------------------------------------
	//頂点インデックス
	DWORD indexList[4]={0,1,2,3};

	//頂点インデックス作成
	m_pDevice->CreateIndexBuffer(
		sizeof( DWORD ) * m_uUse * 6,
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&pIndex,
		NULL);

	//頂点のメモリを直でコピーする
	DWORD* vIndex;
	pIndex->Lock( 0,0, (void**)&vIndex, 0);
	memcpy( vIndex, m_pIndex, sizeof( m_pIndex ) ); 
	pIndex->Unlock();

	//--------------------------------------------------------
	//頂点登録(pTopVerTexの作成)
	m_pDevice->CreateVertexBuffer(
		sizeof( TVertex ) * m_uUse * 4,	//頂点数 * サイズ
		0,
		FVF_PVERTEX,
		D3DPOOL_MANAGED,
		&pTopVerTex,
		0 );
	
	//頂点のメモリを直でコピーする
	TVertex *vTop;
	pTopVerTex->Lock( 0,0, (void**)&vTop, 0);
	memcpy( vTop, m_pVertex, sizeof( m_pVertex ) ); 
	pTopVerTex->Unlock();

	//--------------------------------------------------------
	//頂点宣言(FVFみたいなもの)
	m_pDevice->SetFVF(FVF_PVERTEX);

	//頂点インデックス指定
	m_pDevice->SetIndices( pIndex );
	//使用ストリーム指定と頂点バッファ設定
	m_pDevice->SetStreamSource( 0, pTopVerTex, 0, sizeof( TVertex ) );
	
	const D3DMATERIAL9 material = {
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{0.1f, 0.1f, 0.1f, 1.0f},
		{0.0f, 0.0f, 0.0f, 1.0f},
		0.0f,
	};

	// マテリアルテクスチャセット
	m_pDevice->SetMaterial(&material);
	m_pDevice->SetTexture(0, m_pTextureManager->LoadTexture(m_FileName));		

	//描画(面二つと０から始まる頂点と指定)
	HRESULT hr = m_pDevice->DrawIndexedPrimitive( 
		D3DPT_TRIANGLELIST, 
		0,	//開始地点からの相対位置
		0,	//最小インデックス番号
		m_uUse*6,	//最大インデックス番号
		0,	//インデックス配列の読み取り位置	
		m_uUse*2	//面の数
		 );
	*/