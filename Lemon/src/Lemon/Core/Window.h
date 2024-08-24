#pragma once

namespace Lemon
{
	class Window
	{
	public:
		virtual ~Window() = 0;

		virtual void HandleEvents() = 0;
		virtual void SwapBuffers() = 0;

		void* GetNative() const { return m_NativeWindow; }

		static Window* Create();
	protected:
		void* m_NativeWindow;
	};
}