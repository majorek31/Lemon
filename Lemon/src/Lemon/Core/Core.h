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

#define BIND_EVENT(eventType, method) \
    static_cast<Lemon::EventHandler<eventType>>([this](const eventType& e) -> void { \
        this->method(e); \
    })

#define BIND_EVENT_FN(eventType, method) Lemon::CreateScoped<Lemon::EventHandlerHandle>(BIND_EVENT(eventType, method))

namespace Lemon
{

	template<typename T>
	using EventHandler = std::function<void(const T& event)>;
	class Event;

	struct EventHandlerHandle {
		template<typename TEvent>
		EventHandlerHandle(EventHandler<TEvent> handler)
			: Handle(EventManager::Get().Subscribe<TEvent>(handler).Handle) {}

		explicit EventHandlerHandle(size_t handle)
			: Handle(handle) {}

		bool operator==(const EventHandlerHandle& other) const {
			return Handle == other.Handle;
		}

		~EventHandlerHandle() = default; 

		size_t Handle;
	};



	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename... TArgs>
	constexpr Ref<T> CreateRef(TArgs&&... args)
	{
		return std::make_shared<T>(std::forward<TArgs>(args)...);
	}

	template<typename T>
	using Scoped = std::unique_ptr<T>;
	template<typename T, typename... TArgs>
	constexpr Scoped<T> CreateScoped(TArgs&&... args)
	{
		return std::make_unique<T>(std::forward<TArgs>(args)...);
	}

}