//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testObj.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "testObj.h"
#include "testDelay.h"

// DelayFunction
class CCreateDelay : public IDelayFunction {

public:
	std::function<void()> m_Function;

public:

	void Run() {
		m_Function();
	}
};

testObj::testObj() {
	m_Transform.Name = "testObj";
	m_Obj.SetFileName(_T("Player.x"));
}

testObj::~testObj() {
	
}

bool testObj::Start(){

	m_pDelayFuncManager = CDelayFunctionManager::Create();
	m_pDirectInputManager = CDirectInputManager::Create();

	return true;
}

void testObj::Update(){

	if(m_pDirectInputManager->GetKeyboardTrigger(DIK_Q)) {
		CCreateDelay* pFunc = new CCreateDelay;
		pFunc->SetExecTime(m_pDelayFuncManager->AfterTime(1));
		pFunc->m_Function = std::bind(&testObj::CreateDelay, this);
		m_pDelayFuncManager->Add(pFunc);
	}
}

void testObj::Draw(){
	m_Obj.Draw( this );
}

void testObj::CreateDelay() {

	TaskManager* m_pTask = TaskManager::Create();
	m_pTask->CreateObject(new testDelay)->Start();
}