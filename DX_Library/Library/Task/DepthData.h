//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
//
// [DepthData.h]
// author : �哴�ˑ�
//
// �T�v : �f�v�X���w�肵�Ă���I�u�W�F�N�g�̒l��񋓉�
//
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

#if (_MSC_VER > 1000)
#pragma once
#endif	//_MSC_VER > 1000

#ifndef _____DepthData_h_____
#define _____DepthData_h_____

#include <iostream>
#include <stdio.h>

// Depth�萔
enum eDepth {

	// ---- �`�摁�� ----
	
	DEPTH_MIN = -100, 
	DEPTH_CAMERA,
	DEPTH_CLICK,

	DEPTH_FADE,
	DEPTH_TUTORIAL,
	DEPTH_DEBUG,
	DEPTH_BAR,
	DEPTH_ROTUI,
	DEPTH_PARTICLE,
	DEPTH_SCENE,

	DEPTH_NORMAL = 0,

	DEPTH_BACK,
	
	// ---- �`��x�� ----

	DEPTH_MAX,
};

#endif