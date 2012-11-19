#ifndef DIINPUTHANDLER_H
#define DIINPUTHANDLER_H

#include <dinput.h>
#include "Input.h"

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

class DIInputHandler : public Input
{
private:
	HINSTANCE* hInstance;
	HWND* hWnd;
	LPDIRECTINPUT8 din;    // the pointer to our DirectInput interface
	LPDIRECTINPUTDEVICE8 dinkeyboard;    // the pointer to the keyboard device
	LPDIRECTINPUTDEVICE8 dinmouse;    // the pointer to the mouse device
	BYTE keystate[256];    // the storage for the key-information
	DIMOUSESTATE mousestate;    // the storage for the mouse-information

	long m_mouseTravel[NUM_MOUSE_AXIS];
	int m_mouseBtns[NUM_MOUSE_KEYS];
	int m_DIKtoKeyMap[NUM_KEYB_KEYS];
	int m_kbKeys[NUM_KEYB_KEYS];

public:
	DIInputHandler(HINSTANCE* hInstance, HWND* hWnd); // sets up and initializes DirectInput
	~DIInputHandler();	//closes DirectInput and releases memory
	void createDikKeyMap();
	void reset();
	void detectInput();    // gets the current input state
	void update();
	//bool getKey( int key );
	virtual int getKeyState( int p_key );
	int getMouseKeyState( int p_key );
	long getMouse( int axis );
};

#endif //INPUTHANDLER_H