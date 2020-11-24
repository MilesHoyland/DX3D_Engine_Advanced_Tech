#include "Window.h"
#include <stdexcept>
#include <sstream>
#include "StringConverter.h"
#include "ServiceLocator.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);


Window::Window(std::string title, std::string windowType)
{
	this->window_title = title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = windowType;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);

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
	{
		throw std::runtime_error("Filed to register WNDCLASSEX.");
		util::ServiceLocator::getFileLogger()->print<util::SeverityType::error>("Failed to register Window.");
	}
		

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
		nullptr);

	//if the creation fail return false
	if (!hwnd)
	{
		throw std::runtime_error("Failed to initialize Window.");
		util::ServiceLocator::getFileLogger()->print<util::SeverityType::error>("Failed to initialize window.");
	}

	//show the window
	ShowWindow(hwnd, SW_SHOW);

}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		/*// Create window msg
		auto* const params = reinterpret_cast<LPCREATESTRUCT>(lparam);
		auto* const window =
			reinterpret_cast<Window* const>(params->lpCreateParams);

		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		window->SetHWND(hwnd);
		window->OnCreate();
		*/
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
	case WM_SETFOCUS:
	{
		// Event fired when the window get focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		if(window) window->onFocus();
		break;
	}
	case WM_KILLFOCUS:
	{
		// Event fired when the window lost focus
		Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
		window->onKillFocus();
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}

void Window::Broadcast()
{
	if (!this->initialised)
	{
		// .. and then stored for later lookup
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
		this->OnCreate();
		this->initialised = true;
	}

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

void Window::OnCreate()
{
}

void Window::OnUpdate()
{
}

void Window::onFocus()
{
}

void Window::onKillFocus()
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

Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept
	: ExceptionHelper(line, file),
	hr(hr)
{}

const char* Window::Exception::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] " << GetHR() << std::endl
		<< "[Description] " << GetErrorString() << std::endl
		<< GetOriginString();
	what_buffer = oss.str();
	return what_buffer.c_str();
}

const char* Window::Exception::GetType() const noexcept
{

	return "Window Error";
}

std::string Window::Exception::TranslateHR(HRESULT hr) noexcept
{
	char* p_buffer = nullptr;
	WCHAR p_buff[2048] = {};
	DWORD nMsgLen = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, // 
		nullptr, //
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		p_buff,
		sizeof(p_buff),
		nullptr
	);

	// 0 string length returned indicates a failure
	if (nMsgLen == 0)
	{
		return "Unidentified error code";
	}
	// copy error string from windows-allocated buffer to std::string
	std::string errorString = StringConverter::WideToString(p_buff);
	// free windows buffer as not needed
	LocalFree(p_buff);
	return errorString;
}

HRESULT Window::Exception::GetHR() const noexcept
{
	return hr;
}

std::string Window::Exception::GetErrorString() const noexcept
{
	return TranslateHR(hr);
}
