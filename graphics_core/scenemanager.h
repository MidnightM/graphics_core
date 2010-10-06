#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#pragma once

//includes
#include "dxinit.h"

//class definition
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool InitScene(HWND hwnd, int width, int height);

	void Render();
	void Close();
private:
	bool m_scenerunning;
	DxInit* m_pdx;
};

#endif