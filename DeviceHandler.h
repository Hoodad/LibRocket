#ifndef DEVICEHANDLER_H
#define DEVICEHANDLER_H

#include <string>
#include <windows.h>
#include <windowsx.h>
#include <d3d10.h>
#include <d3dx10.h>
#include "MLInputHandler.h"

using namespace std;

// include the Direct3D Library file
#pragma comment (lib, "d3d10.lib")
#pragma comment (lib, "d3dx10.lib")

#include "Utils.h"

class DeviceHandler
{
private:
	//window settings
	int m_wndWidth;
	int m_wndHeight;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	//Direct3D
	ID3D10Device* m_device;
	ID3D10Effect* m_effect;
	ID3D10RenderTargetView* m_rtv;
	ID3D10DepthStencilView* m_dsv;    //depth stencil view - z/depth buffer
	IDXGISwapChain* m_swapchain;
	D3D10_VIEWPORT m_viewport;

private:
	void initWindow();
	void initD3D();
	void initEffect();

public:
	DeviceHandler(HINSTANCE p_hInstance, int p_wndWidth, int p_wndHeight);
	~DeviceHandler();
	ID3D10Device* getDevice();
	ID3D10Effect* getEffect();
	HWND* getHWnd();
	int getWindowWidth();
	int getWindowHeight();
	void setWindowTitle( string p_text );

	void beginDrawing();
	void presentFrame();
};

#endif //DEVICEHANDLER_U