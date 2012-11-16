#include "EventManager.h"
#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>
#include <rocket/Core/ElementUtilities.h>
#include "EventHandler.h"

extern Rocket::Core::Context* e_context;

static EventHandler*	s_eventHandler = NULL;

typedef std::map< Rocket::Core::String, EventHandler* > EventHandlerMap;
EventHandlerMap event_handlers;

EventManager::EventManager()
{
}
EventManager::~EventManager()
{
	Shutdown();
}
// Releases all event handlers registered with the manager.
void EventManager::Shutdown()
{
	for (EventHandlerMap::iterator i = event_handlers.begin(); i!= event_handlers.end(); i++)
		delete (*i).second;

	event_handlers.clear();
	s_eventHandler = NULL;
}

// Registers a new event handler with the manager.
void EventManager::RegisterEventHandler(const Rocket::Core::String& p_handlerName, EventHandler* p_handler)
{
	// Release any handler bound under the same name.
	EventHandlerMap::iterator iterator = event_handlers.find(p_handlerName);
	if (iterator != event_handlers.end())
		delete (*iterator).second;

	event_handlers[p_handlerName] = p_handler;
}

void EventManager::ProcessEvent(Rocket::Core::Event& event, const Rocket::Core::String& value)
{
	// Chosing not to allow for commands containing ; as in the invaders example 
	Rocket::Core::StringList commands;
	Rocket::Core::StringUtilities::ExpandString(commands, value, ' ');

	if(commands[0] == "exit")
	{
	}
}