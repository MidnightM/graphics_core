#include "dxinit.h"

DxInit::DxInit()
{
	m_pd3ddevice = 0;
	m_prendertargetview = 0;
	m_pswapchain = 0;
	m_drivertype = D3D10_DRIVER_TYPE_NULL;
}

DxInit::~DxInit()
{

}

//method prepares the render device and the backbuffer
bool DxInit::InitDX(HWND hwnd, int width, int height)
{
	//setup result var
	HRESULT result = S_OK;
	//setup the device flags
	unsigned int createdeviceflags = 0;

#ifdef _DEBUG
	createdeviceflags |= D3D10_CREATE_DEVICE_DEBUG;
#endif

	//setup the drivers
	D3D10_DRIVER_TYPE drivertypes[] = 
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};

	unsigned int numdrivertypes = sizeof(drivertypes) / sizeof(drivertypes[0]);

	//setup swapchain desc
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = (unsigned int)width;
	sd.BufferDesc.Height = (unsigned int)height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = true;

	//setup device and chain
	for(unsigned int x = 0; x < numdrivertypes; x++)
	{
		m_drivertype = drivertypes[x];

		result = D3D10CreateDeviceAndSwapChain(NULL,
											   m_drivertype,
											   NULL,
											   createdeviceflags,
											   D3D10_SDK_VERSION,
											   &sd,
											   &m_pswapchain,
											   &m_pd3ddevice);

		if(SUCCEEDED(result))
			break;
	}

	if(FAILED(result))
		return false;

	//setup the backbuffer
	ID3D10Texture2D* pbackbuffer = 0;
	result = m_pswapchain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pbackbuffer);
	if(FAILED(result))
		return false;

	result = m_pd3ddevice->CreateRenderTargetView(pbackbuffer, NULL, &m_prendertargetview);
	pbackbuffer->Release();
	if(FAILED(result))
		return false;

	m_pd3ddevice->OMSetRenderTargets(1, &m_prendertargetview, NULL);

	//setup viewport
	D3D10_VIEWPORT vp;
	vp.Width = (unsigned int)width;
	vp.Height = (unsigned int)height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;

	m_pd3ddevice->RSSetViewports(1, &vp);
	return true;
}

//method clears the rendertargetview device so we can render the next scene
void DxInit::BeginScene()
{
	float clearcolor[4] = { 0.0f, 0.0f, 0.0f, 0.0f};

	m_pd3ddevice->ClearRenderTargetView(m_prendertargetview, clearcolor);
}

//method at current state simply calls the present method from the swapchain
void DxInit::EndScene()
{
	m_pswapchain->Present(0, 0);
}

//method releases all pointers and sets memory to zero
void DxInit::CleanUp()
{
	if(m_pd3ddevice)
		m_pd3ddevice->ClearState();

	if(m_pswapchain)
	{
		m_pswapchain->Release();
		m_pswapchain = 0;
	}

	if(m_prendertargetview)
	{
		m_prendertargetview->Release();
		m_prendertargetview = 0;
	}

	if(m_pd3ddevice)
	{
		m_pd3ddevice->Release();
		m_pd3ddevice = 0;
	}
}