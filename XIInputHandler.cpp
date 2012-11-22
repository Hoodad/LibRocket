#include "XIInputHandler.h"


XIInputHandler::XIInputHandler()
{
	DWORD dwResult; 
	XINPUT_STATE state;
	ZeroMemory( &state, sizeof(XINPUT_STATE) );

	// Simply get the state of the controller from XInput.
	dwResult = XInputGetState( 0, &state );

	if( dwResult == ERROR_SUCCESS )
	{
		int korv = 1;
		// Controller is connected 
	}
	else
	{
		int korv = 0;
		// Controller is not connected 
	}
}


XIInputHandler::~XIInputHandler()
{
}

void XIInputHandler::update()
{
	XINPUT_STATE newState;
	XInputGetState( 0, &newState );
	m_btns[W] = calcState( m_btns[W], newState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
	m_btns[ESC] = calcState( m_btns[W], newState.Gamepad.wButtons & XINPUT_GAMEPAD_B);
	m_stickBtns[M_LBTN] = calcState( m_stickBtns[M_LBTN], newState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
	m_stickBtns[M_RBTN] = calcState( m_stickBtns[M_RBTN], newState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
	m_currentState = newState;

}

int XIInputHandler::getKeyState( int p_key )
{
	switch( p_key )
	{
	case W:
		return m_btns[W];
	case ESC:
		return m_btns[ESC];
	default:
		return 0;
	}
}

int XIInputHandler::getMouseKeyState( int p_key )
{
	switch( p_key )
	{
	case M_LBTN:
		{
			return m_stickBtns[M_LBTN];
		}
	case M_RBTN:
		{
			return m_stickBtns[M_RBTN];
		}
	default:
		return 0;
	}
}

int XIInputHandler::getMousePos( int p_axis )
{
	switch( p_axis )
	{
	case X:
		return m_currentState.Gamepad.sThumbLX;

	case Y:
		return m_currentState.Gamepad.sThumbLY;

	default:
		return 0;
	}
}

int XIInputHandler::getMouseTravel( int p_axis )
{
	switch( p_axis )
	{
	case X:
		return m_currentState.Gamepad.sThumbLX;

	case Y:
		return m_currentState.Gamepad.sThumbLY;

	default:
		return 0;
	}
}
