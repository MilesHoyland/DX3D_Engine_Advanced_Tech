#pragma once
#include <Windows.h>
#include "StringConverter.h"

class Window
{
public:
	//Window 
	Window(std::string title, std::string windowType);
	bool StartUp();
	bool ShutDown();
	void Broadcast();
	bool Running();
	RECT GetClientWindowRect();
	void SetHWND(HWND hWnd);

	//Events
	virtual void OnCreate();
	virtual void OnUpdate();
	virtual void OnDestroy();

	//Release the window
	~Window();
protected:
	HWND hwnd = nullptr;
	bool running = true;

	std::string window_title = "";
	std::wstring window_title_wide = L""; //Wide string representation of window title
	std::string window_class = "";
	std::wstring window_class_wide = L""; //Wide string representation of window class name
	int width;
	int height;

};