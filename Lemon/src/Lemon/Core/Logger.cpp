#include "pch.h"

namespace Lemon
{
	void Logger::Init()
	{
		LM_TIME();
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>());
		logSinks[0]->set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = std::make_shared<spdlog::logger>("Lemon", logSinks.begin(), logSinks.end());
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);
	}

	Ref<spdlog::logger> Logger::GetCore()
	{
		return s_CoreLogger;
	}
}