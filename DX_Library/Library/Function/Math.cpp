//=======================================================================================
//
//	  MathŠÖŒW©ìŠÖ”
//
//=======================================================================================
#include "Math.h"

// --- Sin,Cos,Tan
float fSin[360];
float fCos[360];
float fTan[360];

// Sin,Cos,Tan‚ğŒvZ‚µ•Û‚·‚é
void SetMath() {
	
	for(int i = 0; i < 360; i++) {
		fSin[i] = sinf(i/360.0f*(Pai*2.0f));
		fCos[i] = cosf(i/360.0f*(Pai*2.0f));
		fTan[i] = tanf(i/360.0f*(Pai*2.0f));
	}
}

float GetSin(int nDegree) { 
	while(nDegree >= 360) {
		nDegree -= 360;
	}
	while(nDegree < 0) {
		nDegree += 360;
	}
	return fSin[nDegree];
}

float GetSin(float fRadian) { 
	while(fRadian >= Pai*2.0f) {
		fRadian -= Pai*2.0f;
	}
	while(fRadian < 0) {
		fRadian += Pai*2.0f;
	}
	// •ÏŠ·
	int nDegree = (int)(fRadian/6.28f * 360);
	return fSin[nDegree];
}

float GetCos(int nDegree) { 
	while(nDegree >= 360) {
		nDegree -= 360;
	}
	while(nDegree < 0) {
		nDegree += 360;
	}
	return fCos[nDegree];
}

float GetCos(float fRadian) { 
	while(fRadian >= Pai*2.0f) {
		fRadian -= Pai*2.0f;
	}
	while(fRadian < 0) {
		fRadian += Pai*2.0f;
	}
	// •ÏŠ·
	int nDegree = (int)(fRadian/6.28f * 360);
	return fCos[nDegree];
}

float GetTan(int nDegree) { 
	while(nDegree >= 360) {
		nDegree -= 360;
	}
	while(nDegree < 0) {
		nDegree += 360;
	}
	return fTan[nDegree];
}

float GetTan(float fRadian) { 
	while(fRadian >= Pai*2.0f) {
		fRadian -= Pai*2.0f;
	}
	while(fRadian < 0) {
		fRadian += Pai*2.0f;
	}
	// •ÏŠ·
	int nDegree = (int)(fRadian/6.28f * 360);
	return fTan[nDegree];
}
