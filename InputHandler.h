#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <dinput.h>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

class InputHandler
{
	//Enums
public:
	enum KEY_STATE{ KEY_DOWN, KEY_PRESSED, KEY_UP, KEY_RELEASED };
	enum KEYBOARD{ W, A, S, D, SPACE, LCTRL, F1, F2, F3, F4, NUM_KEYB_KEYS };
	enum MOUSE_KEY{ M_LBTN, M_MBTN, M_RBTN, NUM_MOUSE_KEYS };
	enum MOUSE{ X, Y, NUM_MOUSE_AXIS };

private:
	HINSTANCE* hInstance;
	HWND* hWnd;
	LPDIRECTINPUT8 din;    // the pointer to our DirectInput interface
	LPDIRECTINPUTDEVICE8 dinkeyboard;    // the pointer to the keyboard device
	LPDIRECTINPUTDEVICE8 dinmouse;    // the pointer to the mouse device
	BYTE keystate[256];    // the storage for the key-information
	DIMOUSESTATE mousestate;    // the storage for the mouse-information

	bool keys[NUM_KEYB_KEYS];

	long mouse[NUM_MOUSE_AXIS];
	int m_mouseKeys[NUM_MOUSE_KEYS];

	// For the debug GUI
	bool autoRotate;
	float mouseSpeedX;

public:
	InputHandler(HINSTANCE* hInstance, HWND* hWnd); // sets up and initializes DirectInput
	~InputHandler();	//closes DirectInput and releases memory
	void reset();
	void detectInput(void);    // gets the current input state
	void update();
	bool getKey(int key);
	int getMouseKeyState( int p_key);
	long getMouse(int axis);
};

#endif //INPUTHANDLER_H