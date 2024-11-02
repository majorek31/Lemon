#pragma once
#include "Lemon/Core/Window.h"
struct GLFWwindow;
namespace Lemon
{
	class WindowsWindow : public Window
	{

	public:
		WindowsWindow();
		~WindowsWindow();
		void HandleEvents() override;
		void SwapBuffers() override;
		void* GetNative() override;
	private:
		GLFWwindow* m_Window;
	};
}