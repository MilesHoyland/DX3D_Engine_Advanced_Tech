#pragma once
#include <Windows.h>
#include "StringConverter.h"
#include "ExceptionHelper.h"

class Window
{
public:
	class Exception : public ExceptionHelper
	{
	public:
		Exception(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		virtual const char* GetType() const noexcept;
		static std::string TranslateHR(HRESULT hr) noexcept;
		HRESULT GetHR() const noexcept;
		std::string GetErrorString() const noexcept;
	private:
		HRESULT hr;
	};

public:
	//Window 
	Window(std::string title, std::string windowType);
	void Broadcast();
	bool Running();
	RECT GetClientWindowRect();

	//Events
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();
	virtual void onFocus();
	virtual void onKillFocus();

	//Release the window
	~Window();
protected:
	HWND hwnd = nullptr;
	bool running = true;
	bool initialised = false;

	std::string window_title = "";
	std::wstring window_title_wide = L""; //Wide string representation of window title
	std::string window_class = "";
	std::wstring window_class_wide = L""; //Wide string representation of window class name
	int width;
	int height;

};



#define WINDOW_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)