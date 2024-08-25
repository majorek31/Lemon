#pragma once
#include <memory>

#define LM_ASSERT(x) if (!(x)) { std::cerr << "Assertion failed! " << #x << "\n"; __debugbreak(); }

namespace Lemon
{
	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename... TArgs>
	constexpr Ref<T> CreateRef(TArgs... args)
	{
		return std::make_shared(new T(std::forward<TArgs>(args)...));
	}

	template<typename T>
	using Scoped = std::unique_ptr<T>;
	template<typename T, typename... TArgs>
	constexpr Scoped<T> CreateScoped(TArgs... args)
	{
		return std::make_unique(new T(std::forward<TArgs>(args)...));
	}

}