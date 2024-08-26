#pragma once
#include <string>

namespace Lemon
{
	template<typename T>
	using EventHandler = std::function<void(const T& event)>;

	class Event
	{
	public:
		virtual ~Event() = default;
		virtual const size_t GetEventType() const = 0;

		bool Handled = false;
	};

	class IEventHandlerWrapper
	{
	public:
		void Execute(const Event& event) { Call(event); }
		virtual const size_t GetType() const = 0;
	protected:
		virtual void Call(const Event& event) = 0;
	};

	template<typename TEvent>
	class EventHandlerWrapper : IEventHandlerWrapper
	{
	public:
		EventHandlerWrapper(const EventHandler<TEvent>& handler) :
			m_Handler(handler),
			m_HandlerType(m_Handler.target_type().hash_code())
		{}
	private:
		void Call(const Event& event) override
		{
			if (event.GetEventType() == TEvent::GetStaticEventType())
			{
				m_Handler(static_cast<const TEvent&>(event));
			}
		}
		const size_t GetType() const override { return m_HandlerType; }
		EventHandler<TEvent> m_Handler;
		const size_t m_HandlerType;
	};
}

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