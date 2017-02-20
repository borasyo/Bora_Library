//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [ModelManager.cpp]
// author : �哴�ˑ�
// 
// �ǂݍ��񂾃��f�����Ǘ�����}�l�[�W���[�N���X
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

// ����������
HRESULT CModelManager::Init() { // const std::wstring& FilePath ){

	//m_FilePath = FilePath;

	return S_OK;
}

void CModelManager::RenderModel( const D3DXMATRIXA16* pMtx, const std::wstring& FileName, const bool bShadow, D3DXCOLOR MaterialColor ){
	// �T��
	std::map<std::wstring, CModel*>::iterator Ite = m_ModelList.find( FileName );

	 // �}�b�v�ɂ��łɒǉ�����Ă��郂�f���Ȃ̂ł��̂܂ܕ`��
	if( Ite != m_ModelList.end() ){
		Ite->second->RenderModel(pMtx, bShadow, MaterialColor);
	} 
	// �Ȃ��̂Œǉ����ĕ`��
	else { 
		std::wstring ModelName = ModelFolderPath + FileName;
		CModel* pAddModel = new CModel();	// �ǉ��p��CModel�N���X�쐬					
		
		//���f���ǂݍ���
		if(!pAddModel->LoadModel(ModelName)) {						
			return;
		}

		m_ModelList.insert(std::make_pair( FileName, pAddModel ));	// �}�b�v�ɒǉ�
		pAddModel->RenderModel(pMtx, bShadow, MaterialColor);		// ����̕���`��
	}
}

// �w��̃��f�����폜
void CModelManager::Release( const std::wstring& FileName ){
	
	// �T��
	std::map<std::wstring, CModel*>::iterator Ite = m_ModelList.find( FileName );
	
	// �ΏۂƂȂ郂�f��������΍폜
	if( Ite != m_ModelList.end() ){
		Ite->second->Uninit();
		CModel* temp = Ite->second;
		m_ModelList.erase(Ite);
		delete temp;
	}
	else
		MessageBox( NULL, _T("�Ώۃt�@�C��������܂���"), _T("3D Lib"), MB_OK );
}

// �S�Ẵ��f�����폜	
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

// ����̃��f�����擾
CModel* CModelManager::GetModel( const std::wstring& FileName ){
	
	// �T��
	std::map<std::wstring, CModel*>::iterator Ite = m_ModelList.find( FileName );
	
	// �ΏۂƂȂ郂�f��������΍폜
	if( Ite != m_ModelList.end() )
		return Ite->second;

	// �T�����s
	return nullptr;
}