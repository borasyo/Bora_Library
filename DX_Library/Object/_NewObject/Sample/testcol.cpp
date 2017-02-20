//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testcol.cpp]
// author : ‘å“´Ë‘¾
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "testcol.h"

testcol::testcol() {
	m_Transform.Name = "testcol";
}

testcol::~testcol() {
	
}

bool testcol::Start(){

	TaskManager* pTask = TaskManager::Create();
	//pPlayer = pTask->FindWithName("Player");
	pPlayer = pTask->FindWithName("Player");
	pEnemy = pTask->FindWithName("Enemy");

	return true;
}

void testcol::Update(){

	Collision.CollisionCircleandCircle(pPlayer,pEnemy);
}

void testcol::Draw(){

}