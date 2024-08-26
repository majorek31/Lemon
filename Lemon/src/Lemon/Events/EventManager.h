#pragma once
#include "ApplicationEvents.h"

namespace Lemon
{
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
		static void Subscribe(EventHandler<TEvent> handler);
	private:
		inline static EventManager* s_Instance = nullptr;
		std::queue<Event*> m_EventsQueue;
		std::unordered_map<size_t, std::vector<IEventHandlerWrapper*>> m_Subscribers;
	};
	template<typename TEvent>
	inline void EventManager::Subscribe(EventHandler<TEvent> handler)
	{
		EventManager::Get().Subscribe(TEvent::GetStaticEventType(), (IEventHandlerWrapper*)(new EventHandlerWrapper<TEvent>(handler)));
	}
}

