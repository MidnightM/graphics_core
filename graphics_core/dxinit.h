#ifndef _DX_INIT_H
#define _DX_INIT_H

#pragma once

//includes
#include <d3d10.h>
#include <d3dx10.h>

//class definition
class DxInit
{
public:
	DxInit();
	~DxInit();

	bool InitDX(HWND hwnd, int width, int height);

	void BeginScene();
	void EndScene();
	void CleanUp();
private:
	ID3D10Device*				m_pd3ddevice;
	ID3D10RenderTargetView*		m_prendertargetview;
	IDXGISwapChain*				m_pswapchain;
	D3D10_DRIVER_TYPE			m_drivertype;
};

#endif