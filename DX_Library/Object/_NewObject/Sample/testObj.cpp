//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [testObj.cpp]
// author : ëÂì¥èÀëæ
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#include "testObj.h"

testObj::testObj() {
	m_Transform.Name = "testObj";
	m_Obj.SetFileName(_T("Player.x"));
}

testObj::~testObj() {
	
}

bool testObj::Start(){

	return true;
}

void testObj::Update(){

}

void testObj::Draw(){
	m_Obj.Draw( this );
}