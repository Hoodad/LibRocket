#include "InputManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

int InputManager::addAnalogueControl( AnalogueControl* p_control )
{
	analogues.push_back( p_control );
	return analogues.size();
}

int InputManager::addDigitalControl( DigitalControl* p_control )
{
	digitals.push_back( p_control );
	return digitals.size()+DIGITAL_ID_OFFSET;
}
