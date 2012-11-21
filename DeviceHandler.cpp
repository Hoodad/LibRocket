#include "DeviceHandler.h"
//=========================================================================
// Global callback function used by windows
//=========================================================================
LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// HACK: C/P with multiple returns

	// Otherwise handle the msg
	switch(message)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;

		default:
		{
			MLInputHandler::pushToQue( message, wParam, lParam );
		}
		break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc (hWnd, message, wParam, lParam);
}

//=========================================================================
// Private functions
//=========================================================================
void DeviceHandler::initWindow()
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = wndProc;
	wc.hInstance = m_hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"WindowClass";

	RegisterClassEx(&wc);

	//create window, save result
	m_hWnd = CreateWindowEx(NULL, L"WindowClass", L"Window", 
		WS_OVERLAPPEDWINDOW, -7, -29, m_wndWidth, m_wndHeight, NULL, NULL,
		m_hInstance, NULL);

	ShowWindow(m_hWnd, SW_SHOW);
}

void DeviceHandler::initD3D()
{
	DXGI_SWAP_CHAIN_DESC scd;    //Swap Chain Device
	ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));    //Clear before use

	scd.BufferCount = 1;    //Two buffers
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow = m_hWnd;
	scd.SampleDesc.Count = 1;    //Level of multi sampling, 1 = No
	scd.SampleDesc.Quality = 0;    //Quality of multi-sampling
	scd.Windowed = TRUE;

	//Create a m_device and swap chain using info from scd
	HR(D3D10CreateDeviceAndSwapChain(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0,
		D3D10_SDK_VERSION, &scd, &m_swapchain, &m_device));

	// create a texture for the depth buffer
	D3D10_TEXTURE2D_DESC zbd;
	ZeroMemory(&zbd, sizeof(zbd));
	zbd.Width = m_wndWidth;    // set the width of the depth buffer
	zbd.Height = m_wndHeight;    // set the height of the depth buffer
	zbd.ArraySize = 1;    // we are only creating one texture
	zbd.SampleDesc.Count = 1;    // no multi-sampling
	zbd.Format = DXGI_FORMAT_D32_FLOAT;    // one 32-bit float per pixel
	zbd.BindFlags = D3D10_BIND_DEPTH_STENCIL;    // texture is to be used as a depth buffer
	ID3D10Texture2D* pDepthBuffer;
	HR(m_device->CreateTexture2D(&zbd, NULL, &pDepthBuffer));    // create the texture

	// create the depth buffer
	D3D10_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.Format = DXGI_FORMAT_D32_FLOAT;    // one 32-bit float per pixel
	dsvd.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;    // depth buffer is a 2D texture
	HR(m_device->CreateDepthStencilView(pDepthBuffer, &dsvd, &m_dsv));    // create the depth buffer
	pDepthBuffer->Release();    // release the texture once the depth buffer is made

	//Get the address of the back buffer and use it to create the render target
	ID3D10Texture2D* backBufferPtr;
	m_swapchain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&backBufferPtr);
	HR(m_device->CreateRenderTargetView(backBufferPtr, NULL, &m_rtv));
	backBufferPtr->Release();   //backBufferPtr no longer needed, release to free RAM

	
	ZeroMemory(&m_viewport, sizeof(m_viewport));
	m_viewport.TopLeftX = 0;    
	m_viewport.TopLeftY = 0;    
	m_viewport.Width = m_wndWidth;    
	m_viewport.Height = m_wndHeight;
	m_viewport.MinDepth = 0;    // the closest an object can be on the depth buffer is 0.0
	m_viewport.MaxDepth = 1;    // the farthest an object can be on the depth buffer is 1.0
}


void DeviceHandler::initEffect()
{
	//Debug
	DWORD shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	shaderFlags |= D3D10_SHADER_DEBUG;
	shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
#endif

	//Send blob to gather debug data
	ID3D10Blob* compilationErrors = 0;
	HRESULT hr = 0;
	ID3D10Device* tmp = m_device;
	hr = D3DX10CreateEffectFromFile(L"../shaders/effect.fx", 0, 0, "fx_4_0", shaderFlags, 0,
		m_device, 0, 0, &m_effect, &compilationErrors, 0);
	// the FAILED() macro modifies the hr, this copy is used with the HR() macro
	HRESULT hrCopy = hr;

	// If compilation of the .fx-file fails. Present compilation errors to the user
	if(FAILED(hr))
	{
		if( compilationErrors )
		{
			MessageBoxA(0, (char*)compilationErrors->GetBufferPointer(), 0, 0);
			SAFE_RELEASE(compilationErrors);
		}
		else
		{
			HR(hrCopy);
		}
	}
}

//=========================================================================
// Public functions
//=========================================================================
DeviceHandler::DeviceHandler(HINSTANCE p_hInstance, int p_wndWidth, int p_wndHeight)
{
	m_hInstance = p_hInstance;
	m_hWnd = NULL;
	m_wndHeight = p_wndHeight;
	m_wndWidth = p_wndWidth;

	initWindow();
	initD3D();
	initEffect();
}

DeviceHandler::~DeviceHandler()
{
	//Some COMs aren't released now, must be fixed
	SAFE_RELEASE(m_device);    // close and release the 3D m_device
	SAFE_RELEASE(m_rtv);
	SAFE_RELEASE(m_dsv);
	SAFE_RELEASE(m_swapchain);
	SAFE_RELEASE(m_rtv);
}

ID3D10Device* DeviceHandler::getDevice()
{
	return m_device;
}

ID3D10Effect* DeviceHandler::getEffect()
{
	return m_effect;
}

HWND* DeviceHandler::getHWnd()
{
	return &m_hWnd;
}

int DeviceHandler::getWindowWidth()
{
	return m_wndWidth;
}

int DeviceHandler::getWindowHeight()
{
	return m_wndHeight;
}


// Solution stolen from:
// http://stackoverflow.com/questions/1950993/how-do-i-get-the-position-of-a-co
// ntrol-relative-to-the-windows-client-rect
void DeviceHandler::getWindowPosition( int *out_x, int *out_y )
{
	HWND hWndParent = GetParent(m_hWnd);
	POINT point = {0};

	MapWindowPoints(m_hWnd, hWndParent, &point, 1);

	if( out_x != NULL )
		(*out_x) = point.x;
	if( out_x != NULL )
		(*out_y) = point.y;
}

void DeviceHandler::setWindowTitle( string p_text )
{
	SetWindowTextA(m_hWnd, p_text.c_str());
}

void DeviceHandler::beginDrawing()
{

	m_device->RSSetViewports(1, &m_viewport);    //Set the viewport
	m_device->ClearRenderTargetView( m_rtv, D3DXCOLOR(0.0f, 0.2f, 0.4f, 1.0f) );
	m_device->ClearDepthStencilView( m_dsv, D3D10_CLEAR_DEPTH, 1.0f, 0 );

	//#1F7116
	// clear the window to a deep blue
	//Set the render target as the back buffer
	//m_device->OMSetRenderTargets(1, &m_rtv, m_dsv);
	// HACK: Use no depth buffer = text will not fail depth test
	m_device->OMSetRenderTargets(1, &m_rtv, NULL);

	// reset states
	m_device->OMSetDepthStencilState( 0, 0 );
	float blendFactors[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	m_device->OMSetBlendState( 0, blendFactors, 0xffffffff );
}
void DeviceHandler::presentFrame()
{
	// display the rendered frame
	HR( m_swapchain->Present(0, 0) );
}