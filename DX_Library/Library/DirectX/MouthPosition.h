//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [MouthPosition.h]
// author : 大洞祥太
//
// マウスの座標を取得する。
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____MousePosition_H_____
#define _____MousePosition_H_____

#include "../ObjectType/Object2D.h"

class CMouthPosition {

public:
	typedef struct{
		float x;
		float y;
	} Position_2D;

	CObject2D m_Object2D;
	D3DXVECTOR3 m_Scale;

public:
	~CMouthPosition(){};
	
	static CMouthPosition* Create() { 	
		if( !m_pMouthPosition )
			m_pMouthPosition = new CMouthPosition;
		return m_pMouthPosition;
	}
	static CMouthPosition* Instance() { return m_pMouthPosition; }

	bool Init();
	void Update();
	void Draw();
	bool UnInit();

	Position_2D* GetMouthScreenPosition(); // Position_2D構造体を返す(スクリーン座標)
	Position_2D* GetMouthScreenPosition( float* PositionX ); // ポインタに情報をセット(スクリーン座標)
	Position_2D* GetMouthScreenPosition( float* PositionX , float* PositionY );

	Position_2D* GetMouthClientPosition(); // Position_2D構造体を返す(クライアント座標)
	Position_2D* GetMouthClientPosition( float* PositionX ); // ポインタに情報をセット(クライアント座標)
	Position_2D* GetMouthClientPosition( float* PositionX , float* PositionY );

	void SetMouthClientPosition( float PositionX , float PositionY ); // 指定クライアント座標にカーソルを移動させる

	D3DXVECTOR3 GetScale() { return m_Scale; }
	GameObject* GetMouthObj() { return m_pMouth; }
	void ChangeDrawFlg() { m_bDraw = !m_bDraw; }	// マウスを描画するかを反転
	void SetDrawFlg(bool bFlg) { m_bDraw = bFlg; }	// マウスを描画するかを変更
	bool GetDrawFlg() { return m_bDraw; }			// マウスを描画するかを取得

protected:
private:
	CMouthPosition();

private:
	static CMouthPosition* m_pMouthPosition;

	GameObject* m_pMouth;	// オブジェクトとして保持
	bool m_bDraw;

	Position_2D* m_tScreenPosition; // スクリーン座標
	Position_2D* m_tClientPosition; // クライアント座標

	bool m_bInitialized;
	bool m_ShowMouthFlag;
};

#endif