#pragma once

#include <Rocket/Core.h>
#include <string>
#include <sstream>

using namespace std;

class ButtonEvent : public Rocket::Core::EventListener
{
private:
	Rocket::Core::ElementDocument* m_document;
	string m_name;
	int m_numTimes;

public:
	ButtonEvent( Rocket::Core::ElementDocument* p_document, string p_name );
	virtual ~ButtonEvent();

protected:
	virtual void ProcessEvent( Rocket::Core::Event &p_event );
};

