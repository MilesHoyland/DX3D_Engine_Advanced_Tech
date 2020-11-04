#include "AppWindow.h"
#include <stdexcept>


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
	catch(const std::runtime_error& error)
	{
		//MessageBox(nullptr, error.what(), "An error has occured", MB_OK);
	}
	return 0;
}
