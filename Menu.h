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

using namespace std;

class MenuShit
{
private:
	Input* input;
	//Timer* timer;
	RenderInterfaceDx10* renderInterface;
	SystemInterfaceDx10* systemInterface;
	Rocket::Core::Context* context;
	Rocket::Core::ElementDocument* m_document1;
	Rocket::Core::ElementDocument* m_document2;
	ButtonEvent* m_btn1;
	ButtonEvent* m_btn2;

	//string documentFileName;

public:
	MenuShit();
	~MenuShit();
	void init(Input* p_input, Timer* p_timer, int p_wndWidth, int p_wndHeight,
		ID3D10Device* p_device, ID3D10Effect* p_effect, int p_techNr, int p_passNr);
	bool setDocument( string p_filename );
	void releaseContext();
	void releaseDocument();
	void update( float p_dt );
	void draw();

};

#endif