//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DelayFunctionManager.cpp]
// author : �哴�ˑ�
// 
// �֐����s���w�肵���t���[�����x�点�Ă�����s����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "DelayFunction.h"
#include <list>

// ���̒�`
CDelayFunctionManager* CDelayFunctionManager::m_pDelayFunctionManager = new CDelayFunctionManager;

// �R���X�g���N�^
CDelayFunctionManager::CDelayFunctionManager() {

}

// �f�X�g���N�^
CDelayFunctionManager::~CDelayFunctionManager() {
	for( auto Ite = m_FuncList.begin(); Ite != m_FuncList.end(); Ite++ ) delete *Ite;
	m_FuncList.erase(m_FuncList.begin(),m_FuncList.end());
}

// �\��֐���ǉ�
void CDelayFunctionManager::Add( IDelayFunction* pFunc ) { 
	m_FuncList.push_back( pFunc ); 
}

// ���݂���w��b��̎��Ԃ��擾
DWORD CDelayFunctionManager::AfterTime( float x ) { 
	return timeGetTime() + (DWORD)(x*1000); 
}

// �i�[����Ă���֐����`�F�b�N
void CDelayFunctionManager::CheckStoreFunc()
{
	// ��łȂ��Ȃ�
	DWORD dwNowTime = timeGetTime();
	for(auto Ite = m_FuncList.begin(); Ite != m_FuncList.end();) {
		
		// List���Ɏ��Ԃ��v��
		if ( (*Ite)->GetExecTime() <= dwNowTime )
		{
			// ���s
			(*Ite)->Run(); 
			auto temp = (*Ite);
			Ite = m_FuncList.erase(Ite);
			delete temp;
		}
		// Top���܂����s���Ȃ��Ȃ炻�̑������s���Ȃ�
		else
		{
			break;
		}
	}
}