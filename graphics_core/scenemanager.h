#ifndef _SCENE_MANAGER_H
#define _SCENE_MANAGER_H

#pragma once

//includes

//class definition
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	bool InitScene();

	void Render();
	void Close();
private:
	bool m_scenerunning;
};

#endif