#include "Window.h"
#include <stdexcept>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


Window::Window(std::string title, std::string windowType)
{
	this->window_title = title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = windowType;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);
}

bool Window::StartUp()
{
	//..setting up WindowEx class
	WNDCLASSEX wc{}; 
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = window_class_wide.c_str();
	wc.lpfnWndProc = &WndProc;

	//TODO: change to make use of exceptions
	//..if registration fails return false & throw exception
	if (!RegisterClassEx(&wc))
		throw std::runtime_error("Filed to register WNDCLASSEX.");

	//..adjust client region
	RECT rect = { 0,0,1024,768 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_OVERLAPPEDWINDOW);

	const auto width = rect.right - rect.left;
	const auto height = rect.bottom - rect.top;

	//Creation of window
	this->hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		window_class_wide.c_str(),
		window_title_wide.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		width,
		height,
		nullptr,
		nullptr,
		nullptr,
		this);

	//if the creation fail return false
	if (!hwnd)
		throw std::runtime_error("Filed to initialize Window.");

	//show up the window
	ShowWindow(hwnd, SW_SHOW);
	return true;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Create window msg
		auto* const params = reinterpret_cast<LPCREATESTRUCT>(lparam);
		auto* const window =
			reinterpret_cast<Window* const>(params->lpCreateParams);

		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->SetHWND(hwnd);
		window->OnCreate();
		break;
	}

	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		auto* const window =
			reinterpret_cast<Window* const>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		window->OnDestroy();
		PostQuitMessage(0);
		break;
	}


	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

void Window::Broadcast()
{
	MSG msg{};
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	OnUpdate();

	Sleep(1);
}

bool Window::Running()
{
	return running;
}

RECT Window::GetClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->hwnd, &rc);
	return rc;
}

void Window::SetHWND(HWND hWnd)
{
	this->hwnd = hWnd;
}

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::OnDestroy()
{
	running = false;
}

Window::~Window()
{
	DestroyWindow(hwnd);
}