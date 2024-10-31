#include "Lemon/Lemon.h"
#include "Lemon/Events/EventManager.h"
#include "Lemon/Events/ApplicationEvents.h"
#include <iostream>

class SandboxApp : public Lemon::Application
{
public:
	SandboxApp(const Application::Options& options) : Application(options)
	{
		Lemon::EventManager::Get().Subscribe<Lemon::WindowResizeEvent>([](const Lemon::WindowResizeEvent& e) {
			std::cout << e.Width << "x" << e.Height << std::endl;
			return false;
		});
	
	}
};
Lemon::Application* Lemon::Application::Create(const Application::Options& options)
{
	return new SandboxApp(options);
}
int main()
{
	auto app = Lemon::Application::Create({ "Lemon Sandbox - 2D" });
	app->Start();
	delete app;
}