#include "Menu.h"

BasicMenu::BasicMenu(InputHandler* p_input, Timer* p_timer, int p_wndWidth, int p_wndHeight,
	ID3D10Device* p_device, ID3D10Effect* p_effect, int p_techNr, int p_passNr)
{
	m_shutdown = false;
	m_document = NULL;
	m_timer = p_timer;
	input = p_input;

	renderInterface = new RenderInterfaceDx10(p_device, p_effect, p_techNr, p_passNr);
	systemInterface = new SystemInterfaceDx10(p_timer);

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

BasicMenu::~BasicMenu()
{
	releaseContext();

	delete renderInterface;
	delete systemInterface;
	delete m_timer;
}
bool BasicMenu::setDocument(string _fileName)
{
	releaseDocument();

	bool success = false;

	if(context != NULL)
	{
		m_document = context->LoadDocument(_fileName.c_str());
		if(m_document != NULL)
		{
			success = true;
			m_document->Show();
			m_document->RemoveReference();
		}
	}
	return success;
}

void BasicMenu::releaseContext()
{
	releaseDocument();
	context->RemoveReference(); //release context

	context = NULL;
}

void BasicMenu::releaseDocument()
{
	if(m_document != NULL)
	{
		m_document->GetContext()->UnloadDocument(m_document);
		m_document = NULL;
	}
}

void BasicMenu::update(float _dt)
{
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	context->ProcessMouseMove(cursorPos.x, cursorPos.y,0);

	if( input->getMouseKeyState( InputHandler::M_LBTN ) == InputHandler::KEY_PRESSED )
		context->ProcessMouseButtonDown( 0, 0 );
	else if( input->getMouseKeyState( InputHandler::M_LBTN ) == InputHandler::KEY_RELEASED )
		context->ProcessMouseButtonUp( 0, 0 );

	if( input->getMouseKeyState( InputHandler::M_RBTN ) == InputHandler::KEY_PRESSED )
		context->ProcessMouseButtonDown( 0, 0 );
	else if( input->getMouseKeyState( InputHandler::M_RBTN ) == InputHandler::KEY_RELEASED )
		context->ProcessMouseButtonUp( 0, 0 );

	context->Update();
}

void BasicMenu::draw()
{
	context->Render();
	
}

bool BasicMenu::loadDocument( string p_filename )
{
	releaseDocument();

	bool result = false;

	if(context != NULL)
	{
		m_document = context->LoadDocument(p_filename.c_str());
		if(m_document != NULL)
		{
			result = true;
			m_document->Show();
			m_document->RemoveReference();
		}
	}

	Rocket::Core::Element* title = m_document->GetElementById("title");
	if(title != NULL)
		title->SetInnerRML(m_document->GetTitle());

	return result;
}

void BasicMenu::requestShutdown()
{
	m_shutdown = false;
}

void BasicMenu::beginLoop(InputHandler* p_inputHandler, DeviceHandler* p_deviceHandler)
{
	MSG msg = {0};
	m_timer->reset();
	while(msg.message != WM_QUIT && m_shutdown == false)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_timer->tick();
			p_inputHandler->update();
			update(m_timer->getDt());
			p_deviceHandler->beginDrawing();
			draw();
			p_deviceHandler->presentFrame();
		}
	}
}
