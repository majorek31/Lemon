#include "pch.h"
#include "WindowsWindow.h"
#include <glfw/glfw3.h>

namespace Lemon
{
	std::once_flag initGlfwFlag;
	WindowsWindow::WindowsWindow()
	{
		std::call_once(initGlfwFlag, [] {
			glfwInit();
		});
		m_Window = glfwCreateWindow(800, 600, "Lemon Window", 0, 0);
		LM_CORE_INFO("Created window");
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowsWindow::HandleEvents()
	{
		glfwPollEvents();
	}

	void WindowsWindow::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

	void* WindowsWindow::GetNative()
	{
		return reinterpret_cast<void*>(m_Window);
	}

}
