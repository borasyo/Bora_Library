//=======================================================================================
//
//	  Math関係自作関数
//
//=======================================================================================

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MATH_H_____
#define _____MATH_H_____

#include <math.h>
#include "Define.h"

// ポジション、タイム、始点、中点、終点
#define BEZ_X(p,t,b0,b1,b2) ((1-t)*(1-t)*b0.x + 2*(1-t)*t*b1.x + t*t*b2.x - p.x)
#define BEZ_Y(p,t,b0,b1,b2) ((1-t)*(1-t)*b0.y + 2*(1-t)*t*b1.y + t*t*b2.y - p.y)
#define BEZ_Z(p,t,b0,b1,b2) ((1-t)*(1-t)*b0.z + 2*(1-t)*t*b1.z + t*t*b2.z - p.z)
#define BEZ(b) (D3DXVECTOR3(BEZ_X(b.p,b.t,b.b0,b.b1,b.b2), BEZ_Y(b.p,b.t,b.b0,b.b1,b.b2), BEZ_Z(b.p,b.t,b.b0,b.b1,b.b2)) )

struct tBez {
	D3DXVECTOR3 p;
	float t;
	D3DXVECTOR3 b0,b1,b2;
};

void SetMath();
float GetSin(int nDegree);
float GetSin(float fRadian);
float GetCos(int nDegree);
float GetCos(float fRadian);
float GetTan(int nDegree);
float GetTan(float fRadian);

#endif