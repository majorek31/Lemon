#pragma once
#include <string>

namespace Lemon
{
	class Event
	{
	public:
		virtual ~Event() = default;
		virtual const size_t GetEventType() const = 0;

		bool Handled = false;
	};

	
}
