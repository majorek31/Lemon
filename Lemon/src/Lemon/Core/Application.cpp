#include "pch.h"

#include "Lemon/Events/ApplicationEvents.h"

namespace Lemon
{
	Application::Application(const Options& options) : 
		m_ApplicationName(options.Name),
		m_IsRunning(true)
	{
		LM_TIME();
		if (s_Instance)
			LM_CORE_ERROR("Application created twice {:p}", (void*)this);
		s_Instance = this;
		Logger::Init();
		LM_CORE_INFO("Application created: {:s}", options.Name);
		m_Window.reset(Window::Create());
		m_WindowCloseEventHandler =	EventManager::Subscribe<WindowCloseEvent>([this](const WindowCloseEvent& e) { OnWindowClose(e); });
	}

	Application::~Application()
	{
		LM_TIME();
		EventManager::Unsubscribe(m_WindowCloseEventHandler);
	}

	void Application::Start()
	{
		while (m_IsRunning)
		{
			m_Window->HandleEvents();
			m_Window->SwapBuffers();

			EventManager::Get().Dispatch();
		}
	}

	void Application::OnWindowClose(const WindowCloseEvent& event)
	{
		Close();
	}

	void Application::Close()
	{
		LM_TIME();
		m_IsRunning = false;
	}

}
