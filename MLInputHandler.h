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
	int m_mouseBtns[NUM_MOUSE_KEYS];
	int m_DIKtoKeyMap[NUM_KEYB_KEYS];
	int m_kbKeys[NUM_KEYB_KEYS];
	int keyFromCharMap[VK_F4+1]; //F4 is the last char
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

