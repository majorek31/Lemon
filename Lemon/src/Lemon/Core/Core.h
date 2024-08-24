#pragma once

#define LM_ASSERT(x) if (!(x)) { std::cerr << "Assertion failed! " << #x << "\n"; __debugbreak(); }

namespace Lemon
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
}