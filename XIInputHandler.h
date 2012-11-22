#pragma once

#include "input.h"

#include <Windows.h>
#include <Xinput.h>

class XIInputHandler : public Input
{
private:
	int m_btns[NUM_KEYB_KEYS];
	int m_stickBtns[NUM_MOUSE_KEYS];
	XINPUT_STATE m_currentState;
public:
	XIInputHandler();
	~XIInputHandler();

	virtual void update();
	virtual int getKeyState( int p_key );
	virtual int getMouseKeyState( int p_key );
	virtual int getMousePos( int p_axis );
	virtual int getMouseTravel( int p_axis );
};

