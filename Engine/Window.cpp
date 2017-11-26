#include "Window.h"

#include "SDLWindow.h"

void CerberusWindow::CreateWindow(
		const WindowMode aWindowMode, 
		const uint16 aWindowWidth, 
		const uint16 aWindowHeight, 
		VulkanInstance* Instance)
{
	if (myWindow)
	{
		printf("Tried to create window a second time this is not allowed");
		return;
	}
	myWindow = new SDLWindow();
	if (myWindow)
	{
		myWindow->CreateWindow(aWindowMode, aWindowWidth, aWindowHeight, Instance);
	}
}

void CerberusWindow::Close()
{
	if (myWindow)
	{
		myWindow->Close();
		delete myWindow;
	}
}
