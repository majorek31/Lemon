#pragma once
#include <string>
namespace Lemon 
{
	class Application
	{
	public:
		struct Options 
		{
			const std::string& Name;
		};
		Application(const Options& options);
		// To implement by client
		static Application* Create(const Options& options);
	private:
		std::string m_ApplicationName;
	};
}