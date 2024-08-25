#include "pch.h"

namespace Lemon
{
	Application::Application(const Options& options) : 
		m_ApplicationName(options.Name),
		m_IsRunning(true)
	{
		if (s_Instance)
			LM_CORE_ERROR("Application created twice {:p}", (void*)this);
		s_Instance = this;
		Logger::Init();
		LM_CORE_INFO("Application created: {:s}", options.Name);
		m_Window.reset(Window::Create());
	}

	void Application::Start()
	{
		while (m_IsRunning)
		{
			m_Window->HandleEvents();
			m_Window->SwapBuffers();
		}
	}

	void Application::Close()
	{
		m_IsRunning = false;
	}

}
