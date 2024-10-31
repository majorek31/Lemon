#include "pch.h"
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>
#include "Lemon/Events/ApplicationEvents.h"

namespace Lemon
{
	std::once_flag initGlfwFlag;
	WindowsWindow::WindowsWindow()
	{
		std::call_once(initGlfwFlag, [] {
			glfwInit();
		});
		m_Window = glfwCreateWindow(800, 600, "Lemon Window", 0, 0);
		glfwMakeContextCurrent(m_Window);
		LM_CORE_INFO("Created window");
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow*, int w, int h) {
			EventManager::Get().FireEvent(new WindowResizeEvent(w, h));
		});
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void WindowsWindow::HandleEvents()
	{
		glfwPollEvents();
		if (glfwWindowShouldClose(m_Window))
			EventManager::Get().QueueEvent(new WindowCloseEvent());		
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
