#include "pch.h"

namespace Lemon
{
	Application::Application(const Options& options) : 
		m_ApplicationName(options.Name)
	{
		Logger::Init();
		LM_CORE_INFO("Application created: {:s}", options.Name);
		auto wnd = Window::Create();
		while (true)
		{
			wnd->HandleEvents();
			wnd->SwapBuffers();
		}
	}
}
