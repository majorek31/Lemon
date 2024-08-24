#include "Lemon/Lemon.h"

class SandboxApp : public Lemon::Application
{
public:
	SandboxApp(const Application::Options& options) : Application(options)
	{
	}
};
Lemon::Application* Lemon::Application::Create(const Application::Options& options)
{
	return new SandboxApp(options);
}
int main()
{
	auto app = Lemon::Application::Create({ "Lemon Sandbox - 2D" });
	delete app;
}