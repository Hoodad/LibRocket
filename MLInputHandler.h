#pragma once
#include "Input.h"
#include <Windows.h>
#include <deque>

using namespace std;

struct MsgAndParams
{
	UINT message;
	WPARAM wParam;
	LPARAM lParam;
};

class MLInputHandler : public Input
{
private:
	int m_mouseTravel[NUM_MOUSE_AXIS];
	int m_mouseBtnStates[NUM_MOUSE_KEYS];
	int m_keyStates[NUM_KEYB_KEYS];

	bool m_mouseBtnsPressed[NUM_MOUSE_KEYS];
	bool m_mouseBtnsReleased[NUM_MOUSE_KEYS];
	bool m_keysPressed[NUM_KEYB_KEYS];
	bool m_keysReleased[NUM_KEYB_KEYS];

	int m_keyFromCharMap[VK_LCONTROL+1]; //VK_LCONTROL is the last char
	static deque<MsgAndParams> msgQue;

public:
	MLInputHandler();
	~MLInputHandler();

	virtual void update();
	virtual int getKeyState( int p_key );
	virtual int getMouseKeyState( int p_key );
	virtual long getMouse( int p_axis );
	void processWindowsEvent( MsgAndParams p_msgAndParams );
	void processWindowsEvent( UINT p_message, WPARAM p_wParam, LPARAM p_lParam );
	static void pushToQue( MsgAndParams p_msgAndParams );
	static void pushToQue( UINT p_message, WPARAM p_wParam, LPARAM p_lParam );
};

