#ifndef MENU_H
#define MENU_H

#include <string>

#include "DIInputHandler.h"
#include "Timer.h"
#include "RenderInterfaceDx10.h"
#include "SystemInterfaceDx10.h"
#include <Rocket/Core.h>
#include <Rocket/Debugger.h>
#include "ButtonEvent.h"
#include "DeviceHandler.h"

using namespace std;

class Menu
{
private:
	Input* input;
	DeviceHandler* m_dh;
	RenderInterfaceDx10* renderInterface;
	SystemInterfaceDx10* systemInterface;
	Rocket::Core::Context* context;
	Rocket::Core::ElementDocument* m_document1;
	Rocket::Core::ElementDocument* m_document2;
	ButtonEvent* m_btn1;
	ButtonEvent* m_btn2;

	//string documentFileName;
private:
	void init();

public:
	Menu(Input* p_input, Timer* p_timer, int p_wndWidth, int p_wndHeight,
		DeviceHandler* p_dh, int p_techNr, int p_passNr);
	~Menu();
	bool setDocument( string p_filename );
	void releaseContext();
	void releaseDocument();
	void update( float p_dt );
	void draw();

};

#endif