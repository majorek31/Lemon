#pragma once
#include <string>
#include <chrono>

#define LM_TIME() Lemon::Timer timer(__FUNCTION__" took: {:d}ms")

namespace Lemon {

	class Timer 
	{
	public:
		Timer(const std::string& benchFormat) {
			m_BenchFormat = benchFormat;
			m_StartTime = std::chrono::steady_clock::now(); 
		}
		~Timer() {
			auto endTime = std::chrono::steady_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
			LM_CORE_INFO(m_BenchFormat, duration);
		}
	private:
		std::string m_BenchFormat;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTime;
	};
}