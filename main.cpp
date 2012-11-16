/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "Menu.h"
#include "DeviceHandler.h"
#include "Timer.h"
#include "InputHandler.h"
#include <iostream>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	int wndWidth = 1280;
	int wndHeight = 720;

	DeviceHandler* deviceHandler = new DeviceHandler( hInstance, wndWidth, wndHeight);
	Timer* timer = new Timer();
	InputHandler* inputHandler = new InputHandler( &hInstance, deviceHandler->getHWnd());
	BasicMenu* menu = new BasicMenu(inputHandler, timer, wndWidth, wndHeight,
		deviceHandler->getDevice(), deviceHandler->getEffect(), 0, 0 );
	menu->loadDocument("../menu/assets/main_menu.rml");
	//menu->loadDocument("../menu/assets/start_game.rml");
	//menu->loadDocument("../menu/assets/options.rml");
	menu->beginLoop(inputHandler,deviceHandler);

	delete menu;
	delete inputHandler;
	delete deviceHandler;
}