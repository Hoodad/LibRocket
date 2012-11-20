#pragma once

#include "Rocket/Core/Input.h"

class Input
{
	//Enums
public:
	enum KEY_STATE{ KEY_DOWN, KEY_PRESSED, KEY_UP, KEY_RELEASED };
	enum KEYBOARD{ W, A, S, D, SPACE, LCTRL, F1, F2, F3, F4, NUM_KEYB_KEYS };
	enum MOUSE_KEY{ M_LBTN, M_MBTN, M_RBTN, NUM_MOUSE_KEYS };
	enum MOUSE{ X, Y, Z, NUM_MOUSE_AXIS }; // Z = Scroll wheel
	enum KEY_RAW_STATE{ UP, DOWN };

	// libRocket map
private:
	Rocket::Core::Input::KeyIdentifier libRocketFromKeysMap[NUM_KEYB_KEYS];

public:
	Input();
	virtual ~Input();

	virtual void update() = 0;
	virtual int getKeyState( int p_key ) = 0;
	virtual int getMouseKeyState( int p_key ) = 0;
	virtual long getMouse( int p_axis ) = 0;
	static int calcState( int p_state, bool p_pressed );
	Rocket::Core::Input::KeyIdentifier libRocketFromKeys( int m_key );
};