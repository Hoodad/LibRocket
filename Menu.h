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
	DIInputHandler* input;
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
	void init(DIInputHandler* _input, Timer* _timer, int _wndWidth, int _wndHeight,
		ID3D10Device* _device, ID3D10Effect* _effect, int _techNr, int _passNr);
	bool setDocument(string filename);
	void releaseContext();
	void releaseDocument();
	void update(float _dt);
	void draw();

};

#endif