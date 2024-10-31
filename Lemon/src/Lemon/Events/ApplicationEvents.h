#pragma once
#include "Event.h"

namespace Lemon
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE(typeid(WindowCloseEvent).hash_code());

		WindowCloseEvent() = default;
	};

	class WindowResizeEvent : public Event
	{
	public:
		EVENT_TYPE(typeid(WindowResizeEvent).hash_code());

		WindowResizeEvent(int width, int height) : Width(width), Height(height) { }
		int Width = 0, Height = 0;
	};
}
