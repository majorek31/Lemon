#pragma once

namespace Lemon
{
	class UUID
	{
	public:
		UUID();
		operator uint64_t() { return m_UUID; }
	private:
		uint64_t m_UUID;
	};
}