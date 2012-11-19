#pragma once

#include "AnalogueControl.h"
#include "DigitalControl.h"

#include <vector>

using namespace std;

class InputManager
{
private:
	vector<AnalogueControl> analogues;
	vector<DigitalControl> digitals;

public:
	/// Add a control by listening for output. Non blocking.
	/// \return -1  if no input has been detected. Id for the control if detected. 
	int addControlByListening();
	InputManager(void);
	~InputManager(void);
};

