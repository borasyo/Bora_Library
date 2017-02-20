//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [GameObject.h]
// author : 大洞祥太
// 
// 概要 : 全てのゲームオブジェクトの親クラス
//
// 「ObjectType」
// Object3DModel, Object3DPolygon, Object2D, ObjectCamera, 
// ObjectLight, Collision2D, Collision3D, Particle2D, Particle3D
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____GAMEOBJECT_H_____
#define _____GAMEOBJECT_H_____

#include <iostream>
#include <map>
#include <list>
#include <string>
#include <vector>
#include "d3dx9.h"
#include "DepthData.h"
#include "../Function/Define.h"
#include "../Function/Time.h"
#include "../Function/Math.h"
#include "../DirectX/Window.h"
#include "../DirectX/Direct3D.h"
#include "../DirectX/DirectInputManager.h"

// 
class GameObject;

// -- 構造体定義
struct Collision {
	bool bCollision;							// 当たり判定を行ってもよいか
	D3DXVECTOR3 CollisionCube;					// 箱の大きさ(各辺の長さ)
	float fCollisionCircle;						// 球体の大きさ(直径)
	std::map<GameObject*, bool> OnCollision;	// 当たり判定中か
//	bool bOnCollision;				// 当たり判定中か
};

struct Transform {
	// ---- 基本変数
	std::string Name;				// 名前
	std::string Tag;				// タグ
	std::string Layer;				// レイヤー

	D3DXVECTOR3 Position;			// 座標
	D3DXVECTOR3 Rotation;			// 角度
	D3DXVECTOR3 Size;				// サイズ
	D3DXVECTOR3 MoveAmount;			// どれだけ移動したか
	D3DXVECTOR3 RotationAmount;		// どれだけ回転したか
	D3DXVECTOR3 SizeAmount;			// どれだけ拡大縮小したか
	D3DXVECTOR3 OldPosition;		// 過去座標
	D3DXVECTOR3 OldRotation;		// 過去角度
	D3DXVECTOR3 OldSize;			// 過去サイズ
};

// -- クラス定義
class GameObject {

protected:
	Transform m_Transform;
	Collision m_Collision;
	
	int m_nSortingLayer;
	int m_nOrderinLayer;
	//int m_nDepth;				// 深度 (奥がZ-で描画順をソート)

	bool m_bActive;				// アクティブかどうか
	bool m_bNotChangeActive;	// アクティブ状態の変更をさせてもよいか
	bool m_bUpdate;				// 更新させるか
	bool m_bNotChangeUpdate;	// 更新可否の変更をさせてもよいか
	bool m_bDestroy;			// このオブジェクトは自由に破壊できるか
	std::string m_Message;		// メッセージに応じて特定の処理を実行
	int m_nLife; 
	
	// ---- 親子関係
	GameObject* m_Parent;			  // 親クラス
	std::list<GameObject*> m_Child;	  // 子クラス

	// ---- 変更、参照はしない
	D3DXVECTOR3 m_BaseCube;			// m_Sizeが1(基準)の時の当たり範囲を保持
	float m_fBaseCircle;			// m_Sizeが1(基準)の時の当たり範囲を保持
	
protected:
	// ---- オブジェクトのアクティブ状態を変更した際のイベント関数(外部からは呼び出し不可)
	virtual void OnEnable() {}
	virtual void OnDisable() {}

public:
	GameObject();
	virtual ~GameObject();

	// ---- 基本関数
	virtual void Awake();		// コンストラクタで実行
	virtual bool Start();		// ゲームループ1フレーム目で1度だけ実行

	virtual void FastUpdate();	// 優先してUpdate	(事前初期化などの処理を書く。他のオブジェクトは触らない)
	virtual void Update();		// 普通にUpdate		(基本処理)
	virtual void LateUpdate();	// 最後にUpdate		(コリジョンなど)

	virtual void FastDraw();	// 優先してDraw		(カメラなど)
	virtual void Draw();		// 普通にDraw()		(モデルなど)
	virtual void LateDraw();	// 最後にDraw		(UI、デバッグコリジョンなど)

	virtual void Clear(){}		// 後処理

	virtual GameObject* CreateChild(){ return nullptr; } // Particleなどnewの数が膨大になるオブジェトを処理効率よく作成する
	
	// ---- ダウンキャスト
	virtual GameObject* GetDownCastClass(GameObject* Obj) = 0; // ダウンキャストのためには必須デス

	// ---- 例外チェック
	void ExceptionCheck();
	
	// ---- 再初期化
	void ReInit();
	
	// ---- 更新前準備
	void Preparation();
	
	// ---- ゲッター関数
	const std::string GetName() { return m_Transform.Name; }	// 名前取得
	const std::string GetTag() { return m_Transform.Tag; }		// タグ取得
	const std::string GetLayer() { return m_Transform.Layer; }	// レイヤー取得

	bool GetActive() { return m_bActive; }			// このオブジェクトはアクティブかどうか
	bool GetUpdateFlg() { return m_bUpdate; }		// このオブジェクトは更新するか
	const bool GetDestory() { return m_bDestroy; }	// このオブジェクトは破壊可能か
	int GetLife() { return m_nLife; }				// このオブジェクトのライフを取得

	// --- Free関数 ※基本的には使用しない！
	virtual void FreeFunction(){}
	virtual int* GetInt() { return nullptr; }
	virtual float* GetFloat() { return nullptr; }
	virtual bool* GetBool() { return nullptr; }
	virtual D3DXVECTOR3* GetVec() { return nullptr; }
	virtual D3DXCOLOR* GetColor(){ return nullptr; }
	virtual D3DXMATRIX* GetMatrix(){ return nullptr; }

	// 親子
	GameObject* GetParent() { return m_Parent; }					// 親のオブジェクト取得
	std::list<GameObject*>* GetChild() { return &m_Child; }			// 子のオブジェクト取得
	GameObject* FindChild(const std::string Name);					// 特定の子オブジェクトを取得
	std::list<GameObject*> FindChildAll(const std::string Name);	// 特定の子オブジェクトを取得

	GameObject* SetParent(GameObject* Parent);  // 親子関係を設定
	void DetachParent();
	
	void SetActive(bool bFlg);
	void SetUpdateFlg(bool bFlg);
	void BanDestroy();  // このオブジェクトを破壊できなくする
	void SendForMessage(std::string msg);	// オブジェクトにメッセージを送る
	void SetLife(int nLife); // ライフを変動する
	void Death() { m_nLife = 0; }	// ライフを0にする

	// ---- コリジョン
	const D3DXVECTOR3 GetCollisionCubePlusSize() { return m_Collision.CollisionCube; }
	const D3DXVECTOR3 GetCollisionCubeMinusSize() { return -m_Collision.CollisionCube; }
	float GetCollisionCircleSize() { return m_Collision.fCollisionCircle; }
	bool GetCollisionFlg() { return m_Collision.bCollision; }
	
	void SetCollisionCubeSize(D3DXVECTOR3 Size);
	void SetCollisionCircleSize(float size);
	
	void SetCollisionFlg(bool bFlg);
	
	void OnCollision(GameObject* pObj, bool bOnCollision); // 相手オブジェクトと判定結果を送る
	bool GetOnCollisionFlg(GameObject* pObj);
	virtual void OnCollisionEnter(GameObject* pObj) {}
	virtual void OnCollisionStay(GameObject* pObj) {}
	virtual void OnCollisionExit(GameObject* pObj) {}
	
	// ---- トランスフォーム
	D3DXVECTOR3* GetPosition() { return &m_Transform.Position; }			// 座標を取得
	D3DXVECTOR3* GetRotation() { return &m_Transform.Rotation; }			// 角度を取得
	D3DXVECTOR3* GetSize() { return &m_Transform.Size; }					// サイズを取得

	D3DXVECTOR3* GetOldPosition() { return &m_Transform.OldPosition; }		// 過去座標を取得
	D3DXVECTOR3* GetOldRotation() { return &m_Transform.OldRotation; }		// 過去角度を取得
	D3DXVECTOR3* GetOldSize() { return &m_Transform.OldSize; }				// 過去サイズを取得
	
	D3DXVECTOR3* GetMoveAmount() { return &m_Transform.MoveAmount; }		// 移動量を取得
	D3DXVECTOR3* GetRotAmount() { return &m_Transform.RotationAmount; }		// 回転量を取得
	D3DXVECTOR3* GetSizeAmount() { return &m_Transform.SizeAmount;  }		// 拡大縮小率量を取得
	
	void Move(D3DXVECTOR3 move);			// オブジェクトを移動(子がいれば子も)
	void Rotation(D3DXVECTOR3 rot);			// オブジェクトを回転(子がいれば子も)
	void SizeChange(D3DXVECTOR3 size);		// オブジェクトサイズ変更(子がいれば子も)
	void ScaleChange(D3DXVECTOR3 scale);	// オブジェクトスケール変更(子がいれば子も)
	void ScaleChange(float scale);			// オブジェクトスケール変更(子がいれば子も)
	void ReturnMove();		// 移動したのを戻す
	void ReturnMoveX();		// 移動したXを戻す
	void ReturnMoveY();		// 移動したYを戻す
	void ReturnMoveZ();		// 移動したZを戻す
	void ReturnRot();		// 回転したのを戻す
	void ReturnSize();		// 拡大したのを戻す

	// 深度ソート(勝手に呼ばない)
	//int GetDepth() { return m_nSortingLayer; }
	int GetSortingLayer() { return m_nSortingLayer; }
	int GetOrderinLayer() { return m_nOrderinLayer; }
};

#endif