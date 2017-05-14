#include "Window.h"

#include "SDLWindow.h"

void Window::CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight, VulkanInstance* Instance, VulkanLoader* Loader)
{
	myWindow = new SDLWindow();
	if (myWindow)
	{
		myWindow->CreateWindow(aWindowMode, aWindowWidth, aWindowHeight, Instance, Loader);
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