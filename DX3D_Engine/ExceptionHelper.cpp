#include "ExceptionHelper.h"
#include <sstream>

ExceptionHelper::ExceptionHelper(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* ExceptionHelper::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	what_buffer = oss.str();
	return what_buffer.c_str();
}

const char* ExceptionHelper::GetType() const noexcept
{
	return "Exception";
}

int ExceptionHelper::GetLine() const noexcept
{
	return line;
}

const std::string& ExceptionHelper::GetFile() const noexcept
{
	return file;
}

std::string ExceptionHelper::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
