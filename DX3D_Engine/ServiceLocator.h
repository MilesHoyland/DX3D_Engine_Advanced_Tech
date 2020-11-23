#pragma once
#include "Logger.h"
namespace util
{
	class ServiceLocator
	{
	private:
		static std::shared_ptr<Logger<FileLogPolicy> > fileLogger;		// the file logger

	public:

		// file logging services
		static Logger<FileLogPolicy>* getFileLogger() { return fileLogger.get(); };								// returns the file logger
		static void provideFileLoggingService(std::shared_ptr<Logger<FileLogPolicy> > providedFileLogger);		// sets the file logging service to the given logger
	};

}