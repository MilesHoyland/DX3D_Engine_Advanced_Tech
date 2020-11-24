#include "AppWindow.h"
#include "ExceptionHelper.h"
#include <stdexcept>
#include <Windows.h>
#include "StringConverter.h"
#include "InputSystem.h"

#include "expected.h"
#include "ServiceLocator.h"

void startLoggingService();

int main()
{
	// try to start the logging service; if this fails, abort the application!
	try { startLoggingService(); }
	catch (std::runtime_error)
	{
		// show error message on a message box
		MessageBox(NULL, L"Unable to start logging service!", L"Critical Error!", MB_ICONEXCLAMATION | MB_OK);

		// humbly return with error code
		return -1;
	}

	// try to initialise the graphics engine
	try 
	{	GraphicsEngine::create();	}
	catch (...) {
		FILE_LOG_ERROR("Failed to initialise graphics engine.");
		return -1;
	}
	
	// try to initialise the input system
	try
	{	InputSystem::create();	}
	catch (...) 
	{
		FILE_LOG_ERROR("Failed to initialise Input system.");
		return -1;
	}


	// run the game
	try
	{
		AppWindow app("MyWindew", "AppClass");
		util::ServiceLocator::getFileLogger()->print<util::SeverityType::info>("Application instance created.");
		FILE_LOG_INFO("Application instance created via macro");
		while (app.Running())
		{
			app.Broadcast();
		}
	}
	catch(const std::exception& error)
	{
		std::wstring w_msg = StringConverter::StringToWide(error.what());
		MessageBox(nullptr,w_msg.c_str(), L"An error has occured", MB_OK);
	}

	// release systems
	InputSystem::release();
	GraphicsEngine::release();

	return 0;
}


/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Services /////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
void startLoggingService()
{
	// create file logger
	std::shared_ptr<util::Logger<util::FileLogPolicy> > engineLogger(new util::Logger<util::FileLogPolicy>(L"Engine.log"));

	// set name of current thread
	engineLogger->setThreadName("mainThread");

	// register the logging service
	util::ServiceLocator::provideFileLoggingService(engineLogger);

#ifndef NDEBUG
	// print starting message
	util::ServiceLocator::getFileLogger()->print<util::SeverityType::info>("The file logger was created successfully.");
#endif
}