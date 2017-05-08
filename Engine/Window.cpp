#include "Window.h"

#include "SDLWindow.h"

void Window::CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight)
{
	myWindow = new SDLWindow();
	if (myWindow)
	{
		myWindow->CreateWindow(aWindowMode, aWindowWidth, aWindowHeight);
	}
}

void Window::Close()
{
	if (myWindow)
	{
		myWindow->Close();
		delete myWindow;
	}
}