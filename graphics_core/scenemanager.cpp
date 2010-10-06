#include "scenemanager.h"

SceneManager::SceneManager()
{
	m_scenerunning = false;
}

SceneManager::~SceneManager()
{

}

bool SceneManager::InitScene()
{
	if(!m_scenerunning)
		m_scenerunning = true;

	return true;
}

void SceneManager::Render()
{

}

void SceneManager::Close()
{
	m_scenerunning = false;
}