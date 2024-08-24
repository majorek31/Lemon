#pragma once

namespace Lemon
{
	class Logger
	{
	public:
		Logger(const std::string& name);
		void Log(const char* fmt, ...);
		void Warn(const char* fmt, ...);
		void Error(const char* fmt, ...);
	private:
		std::string m_LoggerName;
	};
}