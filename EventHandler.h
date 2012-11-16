#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include <Rocket/Core/String.h>

namespace Rocket{
	namespace Core{
		class Event;
	}
}

class EventHandler
{
public:
	virtual ~EventHandler();
	virtual void ProcessEvent(Rocket::Core::Event& p_event, const Rocket::Core::String& value) = 0;
private:
};

#endif	//EVENTHANDLER_H