#include "InputHandler.h"

InputHandler::InputHandler(HINSTANCE* _hInstance, HWND* _hWnd)
{
	hInstance = _hInstance;
	hWnd = _hWnd;

	// create the DirectInput interface
	DirectInput8Create(*hInstance,    // the handle to the application
					   DIRECTINPUT_VERSION,    // the compatible version
					   IID_IDirectInput8,    // the DirectInput interface version
					   (void**)&din,    // the pointer to the interface
					   NULL);    // COM stuff, so we'll set it to NULL

	// create the keyboard device
	din->CreateDevice(GUID_SysKeyboard,    // the default keyboard ID being used
					  &dinkeyboard,    // the pointer to the device interface
					  NULL);    // COM stuff, so we'll set it to NULL
	din->CreateDevice(GUID_SysMouse,
					  &dinmouse,
					  NULL);

	// set the data format to keyboard format
	dinkeyboard->SetDataFormat(&c_dfDIKeyboard);
	dinmouse->SetDataFormat(&c_dfDIMouse);

	// set the control we will have over the keyboard
	dinkeyboard->SetCooperativeLevel(*hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	dinmouse->SetCooperativeLevel(*hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	reset();

	// Debug Vars
	mouseSpeedX = 1.0f;

	for ( int i=0; i<NUM_MOUSE_KEYS; i++)
	{
		m_mouseKeys[i] = KEY_UP;
	}
	
}

InputHandler::~InputHandler()
{
	dinkeyboard->Unacquire();    // make sure the keyboard is unacquired
	dinmouse->Unacquire();    // make sure the mouse in unacquired
	din->Release();    // close DirectInput before exiting
}

void InputHandler::reset()
{
	keys[A] = 0;
	keys[S] = 0;
	keys[D] = 0;
	keys[W] = 0;
	keys[SPACE] = 0;
	keys[LCTRL] = 0;
	keys[F1] = 0;
	keys[F2] = 0;
	keys[F3] = 0;
	keys[F4] = 0;

	mouse[X] = 0;
	mouse[Y] = 0;
}

void InputHandler::detectInput(void)
{
	// get access if we don't have it already
	dinkeyboard->Acquire();
	dinmouse->Acquire();

	// get the input data
	dinkeyboard->GetDeviceState(256, (LPVOID)keystate);
	dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mousestate);
}

void InputHandler::update()
{
	reset();
	detectInput();
	
	if(keystate[DIK_W] & 0x80)
		keys[W] = true;
	if(keystate[DIK_A] & 0x80)
		keys[A] = true;
	if(keystate[DIK_S] & 0x80)
		keys[S] = true;
	if(keystate[DIK_D] & 0x80)
		keys[D] = true;
	if(keystate[DIK_SPACE] & 0x80)
		keys[SPACE] = true;
	if(keystate[DIK_LSHIFT] & 0x80) //DEBUG: should be LCONTROL
		keys[LCTRL] = true;

	if(keystate[DIK_F1] & 0x80)
		keys[F1] = true;
	if(keystate[DIK_F2] & 0x80)
		keys[F2] = true;
	if(keystate[DIK_F3] & 0x80)
		keys[F3] = true;
	if(keystate[DIK_F4] & 0x80)
		keys[F4] = true;

	if(keystate[DIK_ESCAPE] & 0x80)
		PostMessage(*hWnd, WM_DESTROY, 0, 0);

	for( int i=0; i<NUM_MOUSE_KEYS; i++)
	{
		if( m_mouseKeys[i] == KEY_UP )
		{
			if( mousestate.rgbButtons[i] )
				m_mouseKeys[i] = KEY_PRESSED;
			else
				m_mouseKeys[i] = KEY_UP;
		}
		else if( m_mouseKeys[i] == KEY_PRESSED )
		{
			if( mousestate.rgbButtons[i] )
				m_mouseKeys[i] = KEY_DOWN;
			else
				m_mouseKeys[i] = KEY_RELEASED;
		}
		else if( m_mouseKeys[i] == KEY_DOWN )
		{
			if( mousestate.rgbButtons[i] )
				m_mouseKeys[i] = KEY_DOWN;
			else
				m_mouseKeys[i] = KEY_RELEASED;
		}
		else if( m_mouseKeys[i] == KEY_RELEASED )
		{
			if( mousestate.rgbButtons[i] )
				m_mouseKeys[i] = KEY_PRESSED;
			else
				m_mouseKeys[i] = KEY_UP;
		}
		else
		{
			// should NEVER happen!
			m_mouseKeys[i] = KEY_UP;
		}
	}
}

bool InputHandler::getKey(int key)
{
	return keys[key];
}

int InputHandler::getMouseKeyState( int p_key )
{
	return m_mouseKeys[p_key];
}

long InputHandler::getMouse(int axis)
{
	//DEBUG: return std values
	if(axis == X)
	{
		return mousestate.lX;
	}
	else if (axis == Y)
	{
		return mousestate.lY;
	}
	else
	{
		return 0;
	}
}