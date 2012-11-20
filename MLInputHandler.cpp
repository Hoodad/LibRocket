#include "MLInputHandler.h"

deque<MsgAndParams> MLInputHandler::msgQue;

MLInputHandler::MLInputHandler()
{
	for( int i=0; i<VK_F4+1; i++ ) //F4 is the last char
		keyFromCharMap[i] = -1;

	keyFromCharMap['W']			= Input::W;
	keyFromCharMap['A']			= Input::A;
	keyFromCharMap['S']			= Input::S;
	keyFromCharMap['D']			= Input::D;
	keyFromCharMap[VK_SPACE]	= Input::SPACE;
	keyFromCharMap[VK_LCONTROL] = Input::LCTRL;
	keyFromCharMap[VK_F1]		= Input::F1;
	keyFromCharMap[VK_F2]		= Input::F2;
	keyFromCharMap[VK_F3]		= Input::F3;
	keyFromCharMap[VK_F4]		= Input::F4;
}

MLInputHandler::~MLInputHandler()
{
}

void MLInputHandler::processWindowsEvent( MsgAndParams p_msgAndParams )
{
	processWindowsEvent( p_msgAndParams.message, p_msgAndParams.wParam, p_msgAndParams.lParam ); 
}

void MLInputHandler::processWindowsEvent( UINT p_message, WPARAM p_wParam, LPARAM p_lParam )
{
	// Process all mouse and keyboard events
	switch (p_message)
	{
		case WM_LBUTTONDOWN:
			m_mouseBtns[Input::M_LBTN] = Input::calcState( m_mouseBtns[Input::M_LBTN], Input::DOWN );
			//context->ProcessMouseButtonDown(0, GetKeyModifierState());
			break;

		case WM_LBUTTONUP:
			m_mouseBtns[Input::M_LBTN] = Input::calcState( m_mouseBtns[Input::M_LBTN], Input::UP );
			//context->ProcessMouseButtonUp(0, GetKeyModifierState());
			break;

		case WM_RBUTTONDOWN:
			m_mouseBtns[Input::M_LBTN] = Input::calcState( m_mouseBtns[Input::M_RBTN], Input::DOWN );
			//context->ProcessMouseButtonDown(1, GetKeyModifierState());
			break;

		case WM_RBUTTONUP:
			m_mouseBtns[Input::M_LBTN] = Input::calcState( m_mouseBtns[Input::M_RBTN], Input::UP );
			//context->ProcessMouseButtonUp(1, GetKeyModifierState());
			break;

		case WM_MBUTTONDOWN:
			m_mouseBtns[Input::M_LBTN] = Input::calcState( m_mouseBtns[Input::M_MBTN], Input::DOWN );
			//context->ProcessMouseButtonDown(2, GetKeyModifierState());
			break;

		case WM_MBUTTONUP:
			m_mouseBtns[Input::M_LBTN] = Input::calcState( m_mouseBtns[Input::M_MBTN], Input::UP );
			//context->ProcessMouseButtonUp(2, GetKeyModifierState());
			break;

		case WM_MOUSEMOVE:
			m_mouseTravel[Input::X] = LOWORD(p_lParam);
			m_mouseTravel[Input::Y] = HIWORD(p_lParam);

			//context->ProcessMouseMove(LOWORD(l_param), HIWORD(l_param), GetKeyModifierState());
			break;

		case WM_MOUSEWHEEL:
			m_mouseTravel[Input::Z] = HIWORD(p_wParam) / -WHEEL_DELTA;
			//context->ProcessMouseWheel(((short) HIWORD(w_param)) / -WHEEL_DELTA, GetKeyModifierState());
			break;

		case WM_KEYDOWN:
		{
			//Rocket::Core::Input::KeyIdentifier key_identifier = key_identifier_map[w_param];
			//int key_modifier_state = GetKeyModifierState();

			//// Check for a shift-~ to toggle the debugger.
			//if (key_identifier == Rocket::Core::Input::KI_OEM_3 &&
			//	key_modifier_state & Rocket::Core::Input::KM_SHIFT)
			//{
			//	Rocket::Debugger::SetVisible(!Rocket::Debugger::IsVisible());
			//	break;
			//}

			//context->ProcessKeyDown(key_identifier, key_modifier_state);

			int key = keyFromCharMap[p_wParam];
			if(key != -1)
				m_kbKeys[key] =  Input::calcState( m_kbKeys[key], Input::DOWN);
		}
		break;

		case WM_CHAR:
		{
			//HACK: Ignore for now

			//// Only send through printable characters.
			//if (w_param >= 32)
			//	context->ProcessTextInput((Rocket::Core::word) w_param);
			//// Or endlines - Windows sends them through as carriage returns.
			//else if (w_param == '\r')
			//	context->ProcessTextInput((Rocket::Core::word) '\n');
		}
		break;

		case WM_KEYUP:
		{
			//context->ProcessKeyUp(key_identifier_map[w_param], GetKeyModifierState());
			int key = keyFromCharMap[p_wParam];
			if(key != -1)
				m_kbKeys[key] =  Input::calcState( m_kbKeys[key], Input::DOWN);
		}
		break;
	}
}

void MLInputHandler::update()
{
	while(!msgQue.empty())
	{
		processWindowsEvent( msgQue.front() );
		msgQue.pop_front();
	}
}

int MLInputHandler::getKeyState( int p_key )
{
	return m_kbKeys[p_key];
}

int MLInputHandler::getMouseKeyState( int p_key )
{
	return m_mouseBtns[p_key];
}

long MLInputHandler::getMouse( int axis )
{
	if( axis == Input::X )
		return m_mouseTravel[Input::X];
	else if ( axis == Input::Y )
		return m_mouseTravel[Input::Y];
	else if ( axis == Input::Z )
		return m_mouseTravel[Input::Z];
	else
		return 0;
}

void MLInputHandler::pushToQue( UINT p_message, WPARAM p_wParam, LPARAM p_lParam )
{
	MsgAndParams msgAndParams;
	msgAndParams.message = p_message;
	msgAndParams.wParam = p_wParam;
	msgAndParams.lParam = p_lParam;
	pushToQue( msgAndParams );
}

void MLInputHandler::pushToQue( MsgAndParams p_msgAndParams )
{
	msgQue.push_back( p_msgAndParams );
}
