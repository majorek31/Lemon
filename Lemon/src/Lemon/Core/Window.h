#pragma once

namespace Lemon
{
	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void HandleEvents() = 0;
		virtual void SwapBuffers() = 0;

		virtual void* GetNative() = 0;

		static Window* Create();
	};
}