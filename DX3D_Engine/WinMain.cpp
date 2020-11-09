#include "AppWindow.h"
#include "ExceptionHelper.h"
#include <stdexcept>
#include <Windows.h>
#include "StringConverter.h"

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
/*	catch (const ExceptionHelper& error) {

		std::wstring w_type = StringConverter::StringToWide(error.GetType());
		MessageBox(nullptr, StringConverter::StringToWide(error.what()).c_str(), w_type.c_str(), MB_OK);
	}*/
	catch(const std::exception& error)
	{
		std::wstring w_msg = StringConverter::StringToWide(error.what());
		MessageBox(nullptr,w_msg.c_str(), L"An error has occured", MB_OK);
	}
	return 0;
}
