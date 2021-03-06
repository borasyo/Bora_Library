//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ModelManager.cpp]
// author : 大洞祥太
// 
// 読み込んだモデルを管理するマネージャークラス
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include <iostream>
#include <tchar.h>
#include "ModelManager.h"
#include "../Function/Define.h"

CModelManager::CModelManager(){
}


CModelManager::~CModelManager(){

}

CModelManager* CModelManager::Create(){
	static CModelManager* pModelManager = new CModelManager;

	return pModelManager;
}

// 初期化処理
HRESULT CModelManager::Init() { // const std::wstring& FilePath ){

	//m_FilePath = FilePath;

	return S_OK;
}

void CModelManager::RenderModel( const D3DXMATRIXA16* pMtx, const std::wstring& FileName, const bool bShadow, D3DXCOLOR MaterialColor ){
	// 探索
	std::map<std::wstring, CModel*>::iterator Ite = m_ModelList.find( FileName );

	 // マップにすでに追加されているモデルなのでそのまま描画
	if( Ite != m_ModelList.end() ){
		Ite->second->RenderModel(pMtx, bShadow, MaterialColor);
	} 
	// ないので追加して描画
	else { 
		std::wstring ModelName = ModelFolderPath + FileName;
		CModel* pAddModel = new CModel();	// 追加用のCModelクラス作成					
		
		//モデル読み込み
		if(!pAddModel->LoadModel(ModelName)) {						
			return;
		}

		m_ModelList.insert(std::make_pair( FileName, pAddModel ));	// マップに追加
		pAddModel->RenderModel(pMtx, bShadow, MaterialColor);		// 今回の分を描画
	}
}

// 指定のモデルを削除
void CModelManager::Release( const std::wstring& FileName ){
	
	// 探索
	std::map<std::wstring, CModel*>::iterator Ite = m_ModelList.find( FileName );
	
	// 対象となるモデルがあれば削除
	if( Ite != m_ModelList.end() ){
		Ite->second->Uninit();
		CModel* temp = Ite->second;
		m_ModelList.erase(Ite);
		delete temp;
	}
	else
		MessageBox( NULL, _T("対象ファイルがありません"), _T("3D Lib"), MB_OK );
}

// 全てのモデルを削除	
void CModelManager::AllRelease(){
	
	std::map<std::wstring, CModel*>::iterator Ite = m_ModelList.begin();
	
	 while( Ite != m_ModelList.end() ){
		Ite->second->Uninit();
		CModel* temp = Ite->second;
		Ite++;
		delete temp;
	}
	if( !m_ModelList.empty() )
		m_ModelList.erase(m_ModelList.begin(),m_ModelList.end());
}

// 特定のモデルを取得
CModel* CModelManager::GetModel( const std::wstring& FileName ){
	
	// 探索
	std::map<std::wstring, CModel*>::iterator Ite = m_ModelList.find( FileName );
	
	// 対象となるモデルがあれば削除
	if( Ite != m_ModelList.end() )
		return Ite->second;

	// 探索失敗
	return nullptr;
}