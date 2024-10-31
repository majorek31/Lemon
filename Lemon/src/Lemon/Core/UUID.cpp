#include "pch.h"

namespace Lemon
{
	static std::random_device s_RandomDevice;
	static std::mt19937_64 s_Engine(s_RandomDevice());
	static std::uniform_int_distribution<uint64_t> s_Distributor;

	UUID::UUID() : m_UUID(s_Distributor(s_Engine)) {}
}
