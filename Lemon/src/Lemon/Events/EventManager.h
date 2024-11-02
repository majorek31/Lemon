#pragma once
#include "Event.h"
#include <queue>
#include "Lemon/Core/UUID.h"

namespace Lemon
{
	class IEventHandlerWrapper
	{
	public:
		void Execute(const Ref<Event> event) { Call(event); }
		virtual const EventHandlerHandle& GetType() const = 0;
	protected:
		virtual void Call(const Ref<Event> event) = 0;
	};

	template<typename TEvent>
	class EventHandlerWrapper : public IEventHandlerWrapper
	{
	public:
		EventHandlerWrapper(const EventHandler<TEvent>& handler) :
			m_Handler(handler),
			m_HandlerHandle(UUID())
		{}
	private:
		void Call(const Ref<Event> event) override
		{
			if (event->GetEventType() == TEvent::GetStaticEventType())
			{
				m_Handler(static_cast<const TEvent&>(*event.get()));
			}
		}
		const EventHandlerHandle& GetType() const override { return m_HandlerHandle; }
		EventHandler<TEvent> m_Handler;
		const EventHandlerHandle m_HandlerHandle;
	};

	class EventManager
	{
	public:
		EventHandlerHandle Subscribe(size_t eventType, Ref<IEventHandlerWrapper> handler);

		void Unsubscribe(size_t eventId, EventHandlerHandle& handlerId);
		void FireEvent(const Ref<Event> event);
		void QueueEvent(const Ref<Event> event);
		void Dispatch();

		static EventManager& Get();
		void EventManager::Unsubscribe(EventHandlerHandle& handle);
		template<typename TEvent>
		EventHandlerHandle Subscribe(const EventHandler<TEvent>& handler)
		{
			auto wrapper = CreateRef<EventHandlerWrapper<TEvent>>(handler);
			return EventHandlerHandle(Subscribe(TEvent::GetStaticEventType(), wrapper).Handle);
		}
	private:
		inline static EventManager* s_Instance = nullptr;
		std::queue<Ref<Event>> m_EventsQueue;
		std::unordered_map<size_t, std::vector<Ref<IEventHandlerWrapper>>> m_Subscribers;
	};
}