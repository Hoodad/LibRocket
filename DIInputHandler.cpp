#include "DIInputHandler.h"

DIInputHandler::DIInputHandler(HINSTANCE* _hInstance, HWND* _hWnd)
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
	m_dikFromKeyMap[W]		= DIK_W;
	m_dikFromKeyMap[A]		= DIK_A;
	m_dikFromKeyMap[S]		= DIK_S;
	m_dikFromKeyMap[D]		= DIK_D;
	m_dikFromKeyMap[SPACE]	= DIK_SPACE;
	m_dikFromKeyMap[LCTRL]	= DIK_LCONTROL;
	m_dikFromKeyMap[F1]		= DIK_F1;
	m_dikFromKeyMap[F2]		= DIK_F2;
	m_dikFromKeyMap[F3]		= DIK_F3;
	m_dikFromKeyMap[F4]		= DIK_F4;
}

DIInputHandler::~DIInputHandler()
{
	dinkeyboard->Unacquire();    // make sure the keyboard is unacquired
	dinmouse->Unacquire();    // make sure the mouse in unacquired
	din->Release();    // close DirectInput before exiting
}

void DIInputHandler::reset()
{
	for( int i=0; i<NUM_MOUSE_KEYS; i++)
		m_mouseBtns[i] = KEY_UP;

	for( int i=0; i<NUM_KEYB_KEYS; i++)
		m_mouseBtns[i] = KEY_UP;
}

void DIInputHandler::detectInput(void)
{
	// get access if we don't have it already
	dinkeyboard->Acquire();
	dinmouse->Acquire();

	// get the input data
	dinkeyboard->GetDeviceState(256, (LPVOID)keystate);
	dinmouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&mousestate);

	//Reset the mouse vars
	m_mouseTravel[X] = 0;
	m_mouseTravel[Y] = 0;
}

void DIInputHandler::update()
{
	detectInput();

	if(keystate[DIK_ESCAPE] & 0x80)
		PostMessage(*hWnd, WM_DESTROY, 0, 0);

	for( int i=0; i<NUM_MOUSE_KEYS; i++)
	{
		m_mouseBtns[i] = calcState( m_mouseBtns[i], mousestate.rgbButtons[i] );
	}

	for( int i=0; i<NUM_KEYB_KEYS; i++)
	{
		m_kbKeys[i] = calcState( m_kbKeys[i], keystate[m_dikFromKeyMap[i]] & 0x80 );
	}
}

int DIInputHandler::getKeyState( int p_key )
{
	return m_kbKeys[p_key];
}

int DIInputHandler::getMouseKeyState( int p_key )
{
	return m_mouseBtns[p_key];
}

long DIInputHandler::getMouse(int axis)
{
	if( axis == X )
		return mousestate.lX;
	else if ( axis == Y )
		return mousestate.lY;
	else
		return 0;
}