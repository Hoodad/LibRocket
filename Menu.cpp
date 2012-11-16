#include "Menu.h"

MenuShit::MenuShit()
{
	input           = NULL;
	renderInterface = NULL;
	systemInterface = NULL;
	context         = NULL;
	m_document1		= NULL;
	m_document2     = NULL;
	m_btn1			= NULL;
	m_btn2			= NULL;
}

MenuShit::~MenuShit()
{
	releaseContext();

	delete renderInterface;
	delete systemInterface;
}

void MenuShit::init(DIInputHandler* _input, Timer* _timer, int _wndWidth, int _wndHeight,
	ID3D10Device* _device, ID3D10Effect* _effect, int _techNr, int _passNr)
{
	input = _input;
	//timer = _timer;

	renderInterface = new RenderInterfaceDx10(_device, _effect, _techNr, _passNr);
	systemInterface = new SystemInterfaceDx10(_timer);

	Rocket::Core::SetSystemInterface(systemInterface);
	Rocket::Core::SetRenderInterface(renderInterface);
	Rocket::Core::Initialise();

	context = Rocket::Core::CreateContext("default", Rocket::Core::Vector2i(1280, 720));
	Rocket::Debugger::Initialise(context);
	Rocket::Debugger::SetVisible(true);

	Rocket::Core::FontDatabase::LoadFontFace("../menu/assets/Delicious-Bold.otf");
	Rocket::Core::FontDatabase::LoadFontFace("../menu/assets/Delicious-BoldItalic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("../menu/assets/Delicious-Italic.otf");
	Rocket::Core::FontDatabase::LoadFontFace("../menu/assets/Delicious-Roman.otf");
}

bool MenuShit::setDocument(string _fileName)
{
	releaseDocument();

	bool success = false;

	if(context != NULL)
	{
		m_document1 = context->LoadDocument(_fileName.c_str());
		m_document2 = context->LoadDocument(_fileName.c_str());
		if(m_document1 != NULL)
		{
			m_document1->GetElementById("title")->SetInnerRML("DELUXE");
			Rocket::Core::Element *element = m_document1->GetElementById("btn");

			if(element != NULL)
			{
				m_btn1 = new ButtonEvent( m_document1, "Changed" );
				element->AddEventListener( "click", m_btn1 );
			}

			success = true;
			m_document1->Show();
			m_document1->RemoveReference();
		}
		if(m_document2 != NULL)
		{
			m_document2->GetElementById("title")->SetInnerRML("DESTINY");
			success = true;
			m_document2->Show();
			m_document2->RemoveReference();
		}
	}



	return success;
}

void MenuShit::releaseContext()
{
	releaseDocument();
	context->RemoveReference(); //release context

	context = NULL;
}

void MenuShit::releaseDocument()
{
	if(m_document1 != NULL)
	{
		m_document1->GetContext()->UnloadDocument(m_document1);
		m_document1 = NULL;
	}
	if(m_document2 != NULL)
	{
		m_document2->GetContext()->UnloadDocument(m_document2);
		m_document2 = NULL;
	}
}

void MenuShit::update(float _dt)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	context->ProcessMouseMove(cursorPos.x, cursorPos.y,0);

	if( input->getMouseKeyState( DIInputHandler::M_LBTN ) == DIInputHandler::KEY_PRESSED )
		context->ProcessMouseButtonDown( 0, 0 );
	else if( input->getMouseKeyState( DIInputHandler::M_LBTN ) == DIInputHandler::KEY_RELEASED )
		context->ProcessMouseButtonUp( 0, 0 );

	if( input->getMouseKeyState( DIInputHandler::M_RBTN ) == DIInputHandler::KEY_PRESSED )
		context->ProcessMouseButtonDown( 0, 0 );
	else if( input->getMouseKeyState( DIInputHandler::M_RBTN ) == DIInputHandler::KEY_RELEASED )
		context->ProcessMouseButtonUp( 0, 0 );

	context->Update();
}

void MenuShit::draw()
{
	context->Render();
	
}
