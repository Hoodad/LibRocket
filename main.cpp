#include "Menu.h"
#include "DeviceHandler.h"
#include "Timer.h"
#include "DIInputHandler.h"
#include "MLInputHandler.h"

#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int wndWidth = 1280;
	int wndHeight = 720;

	DeviceHandler* deviceHandler = new DeviceHandler( hInstance, wndWidth, wndHeight);
	Timer* timer = new Timer();
	Input* input = NULL;
	//input = new DIInputHandler( &hInstance, deviceHandler->getHWnd() );
	input = new MLInputHandler();
	MenuShit* menuxXx;
	menuxXx = new MenuShit();
	menuxXx->init( input, timer, wndWidth, wndHeight,
		deviceHandler->getDevice(), deviceHandler->getEffect(), 0, 0 );
	menuxXx->setDocument("../menu/assets/demo.rml");

	//exit(0); //HACK: DEBUG: profiling
	MSG msg = {0};
	timer->reset();

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			timer->tick();
			input->update();
			menuxXx->update(timer->getDt());
			deviceHandler->beginDrawing();
			menuxXx->draw();
			deviceHandler->presentFrame();
		}
	}
	//return msg.wParam;

	delete menuxXx;
	delete input;
	delete timer;
	delete deviceHandler;


}