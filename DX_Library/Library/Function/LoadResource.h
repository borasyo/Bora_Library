//=======================================================================================
//
//	  リソースを事前に読み込み(ウィンドウ描画前)
//
//=======================================================================================

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____LoadResource_h_____
#define _____LoadResource_h_____

#include "../ObjectType/Object2D.h"
#include "../ObjectType/Object3D_Model.h"

void LoadResources() {

	// 使い捨て変数
	CObject3DModel m_Model;
	CObject2D m_Texture;

	// 事前に読み込みたいリソースの
	// SetFileName
	// をここで実行する

	// --- Model
	m_Model.SetFileName(_T("FIELD/Field.x"));

	m_Model.SetFileName(_T("Chara/Chara_Bishop_Player.x"));
	m_Model.SetFileName(_T("Chara/Chara_Bishop_Enemy.x"));
	m_Model.SetFileName(_T("Chara/Chara_Joker_Player.x"));
	m_Model.SetFileName(_T("Chara/Chara_Joker_Enemy.x"));
	m_Model.SetFileName(_T("Chara/Chara_King_Player.x"));
	m_Model.SetFileName(_T("Chara/Chara_King_Enemy.x"));
	m_Model.SetFileName(_T("Chara/Chara_Knight_Player.x"));
	m_Model.SetFileName(_T("Chara/Chara_Knight_Enemy.x"));
	m_Model.SetFileName(_T("Chara/Chara_Queen_Player.x"));
	m_Model.SetFileName(_T("Chara/Chara_Queen_Enemy.x"));
	m_Model.SetFileName(_T("Chara/Chara_Rook_Player.x"));
	m_Model.SetFileName(_T("Chara/Chara_Rook_Enemy.x"));
	
	m_Model.SetFileName(_T("Weapon/Weapon_Bishop.x"));
	m_Model.SetFileName(_T("Weapon/Weapon_Joker.x"));
	m_Model.SetFileName(_T("Weapon/Weapon_King.x"));
	m_Model.SetFileName(_T("Weapon/Weapon_Queen.x"));
	m_Model.SetFileName(_T("Weapon/Weapon_Knight.x"));
	m_Model.SetFileName(_T("Weapon/Weapon_Knight2.x"));

	// --- Texture
//	m_Texture.SetFileName(_T("Chara/BalanceUI_Enemy.png"));
//	m_Texture.SetFileName(_T("Chara/BalanceUI_Player.png"));
//	m_Texture.SetFileName(_T("Chara/PowerUI_Enemy.png"));
//	m_Texture.SetFileName(_T("Chara/PowerUI_Player.png"));
//	m_Texture.SetFileName(_T("Chara/HealerUI_Enemy.png"));
//	m_Texture.SetFileName(_T("Chara/HealerUI_Player.png"));
}

#endif