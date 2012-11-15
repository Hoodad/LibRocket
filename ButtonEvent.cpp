#include "ButtonEvent.h"


ButtonEvent::ButtonEvent( Rocket::Core::ElementDocument* p_document, string p_name )
{
	m_document	= p_document;
	m_name		= p_name;
	m_numTimes  = 0;
}


ButtonEvent::~ButtonEvent(void)
{

}

void ButtonEvent::ProcessEvent( Rocket::Core::Event &p_event )
{
	if (p_event == "click")
	{
		stringstream ss;
		ss << m_name << " " << m_numTimes++;
		m_document->GetElementById("title")->SetInnerRML( ss.str().c_str() );
	}
}
