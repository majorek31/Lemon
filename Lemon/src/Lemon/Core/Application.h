#pragma once
#include <string>
#include "Lemon/Core/Window.h"
#include "Lemon/Core/Core.h"

class Window;

namespace Lemon 
{
	class WindowCloseEvent;
	class Application
	{
	public:
		static Application& Get() { return *s_Instance; }
		struct Options 
		{
			const std::string& Name;
		};
		Application(const Options& options);
		~Application();

		void Start();
		void Close();

		// To implement by client
		static Application* Create(const Options& options);
	private:
		void OnWindowClose(const WindowCloseEvent& event);
	private:
		inline static Application* s_Instance = nullptr;
		std::string m_ApplicationName;
		Scoped<Window> m_Window;
		bool m_IsRunning;
		EventHandlerHandle m_WindowCloseEventHandler;
	};
}