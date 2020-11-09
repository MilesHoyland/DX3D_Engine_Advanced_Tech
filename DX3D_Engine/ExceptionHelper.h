#pragma once
#include <exception>
#include <string>
#include <comdef.h>

/* 
A class to wrap arround std::exception to make it more extendable.
It stores the line of the file the exception is found and the file itself.
*/
class ExceptionHelper : public std::exception
{
public:
	ExceptionHelper(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int line;
	std::string file;
protected:
	mutable std::string what_buffer; // mutable to change from within what() as it is a const function
};

