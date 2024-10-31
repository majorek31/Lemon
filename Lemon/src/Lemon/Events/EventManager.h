#pragma once
#include "Event.h"
#include <queue>
#include "Lemon/Core/UUID.h"

namespace Lemon
{
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
			m_HandlerHandle(UUID())
		{}
	private:
		void Call(const Event& event) override
		{
			if (event.GetEventType() == TEvent::GetStaticEventType())
			{
				m_Handler(static_cast<const TEvent&>(event));
			}
		}
		const EventHandlerHandle GetType() const override { return m_HandlerHandle; }
		EventHandler<TEvent> m_Handler;
		const EventHandlerHandle m_HandlerHandle;
	};

	class EventManager
	{
	public:
		void Subscribe(size_t eventType, IEventHandlerWrapper* handler);
		void Unsubscribe(size_t eventId, size_t handlerId);
		void FireEvent(const Event& event);
		void FireEvent(const Event* event);
		void QueueEvent(Event* event);
		void Dispatch();

		static EventManager& Get();
		template<typename TEvent>
		static EventHandlerHandle Subscribe(EventHandler<TEvent> handler);
		static void Unsubscribe(EventHandlerHandle handle);
	private:
		inline static EventManager* s_Instance = nullptr;
		std::queue<Event*> m_EventsQueue;
		std::unordered_map<size_t, std::vector<IEventHandlerWrapper*>> m_Subscribers;
	};
	template<typename TEvent>
	inline EventHandlerHandle EventManager::Subscribe(EventHandler<TEvent> handler)
	{
		IEventHandlerWrapper* eventHandler = (IEventHandlerWrapper*)(new EventHandlerWrapper<TEvent>(handler));
		EventManager::Get().Subscribe(TEvent::GetStaticEventType(), eventHandler);

		return eventHandler->GetType();
	}
}