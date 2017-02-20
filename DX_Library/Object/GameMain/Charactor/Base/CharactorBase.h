//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [CharactorBase.h]
// author : 大洞祥太
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____CharactorBase_H_____
#define _____CharactorBase_H_____

#include <iostream>
#include "../../../../Library/Task/TaskManager.h"
#include "../../../../Library/Task/GameObject.h"
#include "../../../../Library/ObjectType/Object3D_Model.h"

#include "MoveMassBase.h"
#include "AtackMassBase.h"
#include "AtackEffectBase.h"
#include "../../Field/FieldMassManager.h"

enum eCharaType {
	CHARA_ROOK = 0,
	CHARA_BISHOP,
	CHARA_KNIGHT,
	CHARA_QUEEN,
	CHARA_KING,
	CHARA_JOKER,

	CHARA_MAX,
};

enum eUser {
	USER_PLAYER = 0,
	USER_ENEMY,

	USER_MAX,
};

class CCharactorBase : public GameObject {

protected:

	CObject3DModel	m_Chara;
	eCharaType		m_eCharaType;
	eUser			m_eUser;
	int				m_nNowMass;

	CFieldMassManager* m_pFieldMassManager;	//	全マス情報保持
	
	//	移動関係の変数
	int m_nNext;	//	移動先のマス
	tBez m_Bez;		//	移動計算

	std::list<CMoveMassBase*> m_MoveMassList;		//	移動可能エリアを表示する
	std::list<CAtackMassBase*> m_AtackMassList;		//	攻撃するエリアを表示する
	std::list<CAtackEffectBase*> m_AtackEffectList;	//	攻撃エフェクトを表示する

public:

	CCharactorBase(int nMass, eUser user, CFieldMassManager* pFieldManager);
	~CCharactorBase();

	virtual bool Start();
	virtual void Update();
	void Draw();
#if _DEBUG
	void LateDraw();
#endif
	
	void Select(bool bOn);	//	プレイヤーが選択、キャンセルした時の処理

	void MoveMass(bool bActive);	//	移動可能エリアON・OFF
	void AtackMass(bool bActive);	//	攻撃可能エリアON・OFF
	void AtackEffect(bool bActive);	//	攻撃エフェクトON・OFF

	virtual void Move();	//	移動処理
	virtual void Atack();	//	攻撃処理

	//	キャラタイプのゲット
	eCharaType GetCharaType() { return m_eCharaType; }

	//	ユーザーのゲット
	eUser GetUser() { return m_eUser; }

	//	Massのゲットセット
	void SetMass(int nMass) { m_nNowMass = nMass; }
	int GetMass() { return m_nNowMass; }

	//	Nextのゲットセット
	void SetNext(int nNext) { m_nNext = nNext; }
	int GetNext() { return m_nNext; }
	
	CCharactorBase* GetDownCastClass(GameObject* Obj){
		if( Obj->GetName() != "CharactorBase" ) // 失敗!!!
			return nullptr;

		CCharactorBase* Child = static_cast<CCharactorBase*>(Obj); 
		return Child;
	}
};

#endif