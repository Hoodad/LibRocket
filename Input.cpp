#include "Input.h"


Input::Input(void)
{
	libRocketFromKeysMap[W]		= Rocket::Core::Input::KI_W;
	libRocketFromKeysMap[A]		= Rocket::Core::Input::KI_A;
	libRocketFromKeysMap[S]		= Rocket::Core::Input::KI_S;
	libRocketFromKeysMap[D]		= Rocket::Core::Input::KI_D;
	libRocketFromKeysMap[SPACE] = Rocket::Core::Input::KI_SPACE;
	libRocketFromKeysMap[LCTRL] = Rocket::Core::Input::KI_LCONTROL;
	libRocketFromKeysMap[F1]	= Rocket::Core::Input::KI_F1;
	libRocketFromKeysMap[F2]	= Rocket::Core::Input::KI_F2;
	libRocketFromKeysMap[F3]	= Rocket::Core::Input::KI_F3;
	libRocketFromKeysMap[F4]	= Rocket::Core::Input::KI_F4;
}

Input::~Input(void)
{
}

int Input::calcState( int p_state, bool p_pressed )
{
	if( p_state == KEY_UP )
	{
		if( p_pressed )
			p_state = KEY_PRESSED;
		else
			p_state = KEY_UP;
	}
	else if( p_state == KEY_PRESSED )
	{
		if( p_pressed )
			p_state = KEY_DOWN;
		else
			p_state = KEY_RELEASED;
	}
	else if( p_state == KEY_DOWN )
	{
		if( p_pressed )
			p_state = KEY_DOWN;
		else
			p_state = KEY_RELEASED;
	}
	else if( p_state == KEY_RELEASED )
	{
		if( p_pressed )
			p_state = KEY_PRESSED;
		else
			p_state = KEY_UP;
	}
	else
	{
		// should NEVER happen!
		p_state = KEY_UP;
	}

	return p_state;
}

Rocket::Core::Input::KeyIdentifier Input::libRocketFromKeys( int m_key )
{
	return libRocketFromKeysMap[m_key];
}