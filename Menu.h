#ifndef MENU_H
#define MENU_H

#include <string>

#include "InputHandler.h"
#include "Timer.h"
#include "RenderInterfaceDx10.h"
#include "SystemInterfaceDx10.h"
#include <Rocket/Core.h>
#include <Rocket/Debugger.h>
#include "ButtonEvent.h"
#include "DeviceHandler.h"

using namespace std;

class BasicMenu
{
private:
	InputHandler* input;
	RenderInterfaceDx10* renderInterface;
	SystemInterfaceDx10* systemInterface;
	Rocket::Core::Context* context;
	Rocket::Core::ElementDocument* m_document;
	bool m_shutdown;
	Timer* m_timer;
public:
	BasicMenu(InputHandler* p_input, Timer* p_timer, int p_wndWidth, int p_wndHeight,
		ID3D10Device* p_device, ID3D10Effect* p_effect, int p_techNr, int p_passNr);
	~BasicMenu();
	bool setDocument(string filename);
	bool loadDocument(string p_filename);
	void releaseContext();
	void releaseDocument();
	void update(float _dt);
	void draw();
	void requestShutdown();
	void beginLoop(InputHandler* p_inputHandler, DeviceHandler* p_deviceHandler);
};

#endif