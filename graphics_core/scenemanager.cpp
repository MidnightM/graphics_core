#include "scenemanager.h"

SceneManager::SceneManager()
{
	m_scenerunning = false;
	m_pdx = 0;
}

SceneManager::~SceneManager()
{

}

bool SceneManager::InitScene(HWND hwnd, int width, int height)
{
	if(!m_scenerunning)
		m_scenerunning = true;

	m_pdx = new DxInit;

	m_pdx->InitDX(hwnd, width, height);

	return true;
}

void SceneManager::Render()
{
	m_pdx->BeginScene();

	m_pdx->EndScene();
}

void SceneManager::Close()
{
	m_scenerunning = false;

	m_pdx->CleanUp();

	delete m_pdx;
	m_pdx = 0;
}