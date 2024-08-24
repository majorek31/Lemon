#pragma once

namespace Lemon
{
	class Logger
	{
	public:
		static void Init();
		static Ref<spdlog::logger> GetCore();
	private:
		inline static Ref<spdlog::logger> s_CoreLogger;
	};
}

#define LM_CORE_INFO(...) ::Lemon::Logger::GetCore()->info(__VA_ARGS__)
#define LM_CORE_ERROR(...) ::Lemon::Logger::GetCore()->error(__VA_ARGS__)