#pragma once

#include "InputType.h"
#include "AnalogueControl.h"
#include "DigitalControl.h"

#include <vector>

using namespace std;

class InputManager
{
private:
	const int DIGITAL_ID_OFFSET = INT_MAX/2;
	vector<AnalogueControl*> analogues;
	vector<DigitalControl*> digitals;

public:
	InputManager();
	~InputManager();

	/// @brief Adds an Analogue Control to the manager.
	/// The manager takes ownership of the control.
	/// @return An ID used when working with the Control through the handler.
	int addAnalogueControl( AnalogueControl* p_control );

	/// @brief Adds a Digital Control to the manager.
	/// The manager takes ownership of the control.
	/// @return An ID used when working with the Control through the handler 
	int addDigitalControl( DigitalControl* p_control );
};

