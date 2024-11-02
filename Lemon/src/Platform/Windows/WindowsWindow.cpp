#include "pch.h"
#include "WindowsWindow.h"
#include <GLFW/glfw3.h>

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
			EventManager::Get().QueueEvent(CreateRef<WindowResizeEvent>(w, h));
		});
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			EventManager::Get().QueueEvent(CreateRef<MouseClickEvent>(button, action, x, y));
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
			EventManager::Get().FireEvent(CreateRef<WindowCloseEvent>());		
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
