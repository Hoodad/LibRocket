#include "Menu.h"
#include "DeviceHandler.h"
#include "Timer.h"
#include "DIInputHandler.h"

#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int wndWidth = 1280;
	int wndHeight = 720;

	DeviceHandler* deviceHandler = new DeviceHandler( hInstance, wndWidth, wndHeight);
	Timer* timer = new Timer();
	Input* input = new DIInputHandler( &hInstance, deviceHandler->getHWnd());
	//inputHandler->i
	MenuShit* menu = new MenuShit();
	menu->init( input, timer, wndWidth, wndHeight,
		deviceHandler->getDevice(), deviceHandler->getEffect(), 0, 0 );
	menu->setDocument("../menu/assets/demo.rml");

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
			menu->update(timer->getDt());
			deviceHandler->beginDrawing();
			menu->draw();
			deviceHandler->presentFrame();
		}
	}
	//return msg.wParam;

	delete menu;
	delete input;
	delete timer;
	delete deviceHandler;


}