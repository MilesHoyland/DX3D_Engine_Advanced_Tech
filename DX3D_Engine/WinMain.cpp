#include "AppWindow.h"
#include "ExceptionHelper.h"
#include <stdexcept>
#include <Windows.h>
#include "StringConverter.h"
#include "InputSystem.h"

int main()
{
	try
	{
		AppWindow app("MyWindew", "AppClass");
		
		if (app.StartUp())
		{
			while (app.Running())
			{
				app.Broadcast();
			}
		}
	}
	catch(const std::exception& error)
	{
		std::wstring w_msg = StringConverter::StringToWide(error.what());
		MessageBox(nullptr,w_msg.c_str(), L"An error has occured", MB_OK);
	}
	return 0;
}
