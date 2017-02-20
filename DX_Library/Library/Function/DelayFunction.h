//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DelayFunction.h]
// author : �哴�ˑ�
// 
// �w��̊֐����w�肵���b����Ɏ��s����B
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DelayFunction_H_____
#define _____DelayFunction_H_____

#include <time.h>
#include <Windows.h>
#include <list>
#include <initializer_list>
#include <functional>

// �x�点��֐����쐬���邽�߂̐e�N���X
class IDelayFunction
{
private:
	DWORD	m_ExecTime;		// ���s�\�莞��
	int m_nPriority;		// �D��x

public:
	IDelayFunction() : m_ExecTime(0),m_nPriority(0) {}
	virtual ~IDelayFunction() {}

	// �\�񂷂�֐����Z�b�g����֐�
	//virtual void SetFunction( std::function<void()> Function ) = 0;
	
	// �����Ŋ֐����ĂԂ̂ŁA�w��̕��ɃI�[�o�[���C�h����K�v������B
	virtual void Run () = 0;

	// �������K�v�ł���΃I�[�o�[���C�h
	virtual void SetArgument () {}

	// ���b��Ɏ��s���邩���Ԃ��w��
	inline void SetExecTime( DWORD time ) { m_ExecTime = time; }

	// �ݒ肵�����Ԃ��擾
	inline const DWORD GetExecTime() const { return m_ExecTime; }

	const bool operator< ( const IDelayFunction& rhs ) const
	{
		// �����Ɏ��s�����ꍇ�́A�D��x���`�F�b�N
		if( GetExecTime() == rhs.GetExecTime() ) {
			return m_nPriority > rhs.m_nPriority;
		}

		// ���Ȃ���Βʏ���s
		return GetExecTime() > rhs.GetExecTime();
	}
};

class CDelayFunctionManager
{
	
private:
	// �����o�ϐ�
	static CDelayFunctionManager* m_pDelayFunctionManager;
	std::list<IDelayFunction*> m_FuncList;

	// �����o�֐�
	CDelayFunctionManager();

public:
	~CDelayFunctionManager();

	// ���̎擾
	static CDelayFunctionManager* Instance() { return m_pDelayFunctionManager; }

	// �\��֐���ǉ�
	void Add( IDelayFunction* pFunc );
	
	// ���݂���w��b��̎��Ԃ��擾
	DWORD AfterTime( float x );

	// �i�[����Ă���֐����`�F�b�N
	void CheckStoreFunc();
};	

#endif