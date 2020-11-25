#pragma once

#include "SkinnyWindows.h"
#include <string>
#include <functional>

enum class EventType
{
	NONE = 0,
	WINDOW_CLOSE, WINDOW_RESIZE, WINDOW_FOCUS, WINDOW_LOST_FOCUS, WINDOW_MOVED,
	APP_TICK, APP_UPDATE, APP_RENDER,
	KEY_PRESSED, KEYRELEASED,
	MS_BTN_PRESSED, MS_BTN_RELEASED, MS_MOVED, MS_SCROLLED 
};

enum EventCategory
{
	NONE = 0,
	EVENT_APPLICATION = 1,
	EVENT_INPUT = 2,
	EVENT_KEYBOARD = 3,
	EVENT_MOUSE = 4,
	EVENT_MOUSE_BUTTON = 5
};

class Event
{
private:
	friend class EventDispatcher;
public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}
protected:
	bool m_Handled = false;
};


class EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	EventDispatcher(Event& event)
		: m_Event(event)
	{
	}

	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		if (m_Event.GetEventType() == T::GetStaticType())
		{
			m_Event.m_Handled = func(*(T*)&m_Event);
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}
