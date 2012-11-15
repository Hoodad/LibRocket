#include "Menu.h"

MenuShit::MenuShit()
{
	input           = NULL;
	renderInterface = NULL;
	systemInterface = NULL;
	context         = NULL;
	document        = NULL;
}

MenuShit::~MenuShit()
{
	releaseContext();

	delete renderInterface;
	delete systemInterface;
}

void MenuShit::init(InputHandler* _input, Timer* _timer, int _wndWidth, int _wndHeight,
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
	//Rocket::Debugger::Initialise(context);
	//Rocket::Debugger::SetVisible(true);

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
		document = context->LoadDocument(_fileName.c_str());

		if(document != NULL)
		{
			success = true;
			document->Show();
			document->RemoveReference();
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
	if(document != NULL)
	{
		document->GetContext()->UnloadDocument(document);
		document = NULL;
	}
}

void MenuShit::update(float _dt)
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

void MenuShit::draw()
{
	context->Render();
	
}
