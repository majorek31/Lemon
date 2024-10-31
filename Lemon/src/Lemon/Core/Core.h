#pragma once
#include <memory>
#include <functional>

#define LM_ASSERT(x) if (!(x)) { std::cerr << "Assertion failed! " << #x << "\n"; __debugbreak(); }

#define EVENT_TYPE(event_type)						\
    static size_t GetStaticEventType()					\
    {												\
        return event_type;							\
    }												\
    const size_t GetEventType() const override			\
    {												\
        return GetStaticEventType();						\
    }


#define EVENT_TYPE_AUTO() EVENT_TYPE(typeid(*this).hash_code())

namespace Lemon
{
	using EventHandlerHandle = uint64_t;
	template<typename T>
	using EventHandler = std::function<void(const T& event)>;


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
	constexpr Scoped<T> CreateScoped(TArgs&&... args)
	{
		return std::make_unique<T>(std::forward<TArgs>(args)...);
	}

}