#include "pch.h"

namespace Lemon
{

	EventHandlerHandle EventManager::Subscribe(size_t eventType, Ref<IEventHandlerWrapper> handler)
	{
		auto subscribers = m_Subscribers.find(eventType);
		if (subscribers != m_Subscribers.end())
		{
			auto& handlers = subscribers->second;
			for (auto& item : handlers)
			{
				if (item->GetType() == handler->GetType())
				{
					LM_CORE_ERROR("Tried to register already registered event callback");
					throw std::runtime_error("Tried to register already registered event callback");
				}
			}
			handlers.emplace_back(handler);
			return handler->GetType();
		}
		else
		{
			m_Subscribers[eventType].emplace_back(std::move(handler));
		}
	}

	void EventManager::Unsubscribe(size_t eventId, EventHandlerHandle& handlerId)
	{
		auto& handlers = m_Subscribers[eventId];
		for (auto& it : handlers)
		{
			if (it->GetType() == handlerId)
			{
				handlers.erase(std::find(handlers.begin(), handlers.end(), it));
				return;
			}
		}
	}

	void EventManager::FireEvent(const Ref<Event> event)
	{
		for (auto& handler : m_Subscribers[event->GetEventType()])
			handler->Execute(event);
	}

	void EventManager::QueueEvent(const Ref<Event> event)
	{
		m_EventsQueue.emplace(event);
	}

	void EventManager::Dispatch()
	{
		while (!m_EventsQueue.empty())
		{
			auto event = m_EventsQueue.front();
			if (!event->Handled)
			{
				FireEvent(event);
			}
			m_EventsQueue.pop();
		}
	}

	EventManager& EventManager::Get()
	{
		if (s_Instance == nullptr)
			s_Instance = new EventManager;
		return *s_Instance;
	}

	void EventManager::Unsubscribe(EventHandlerHandle& handle)
	{
		for (auto& [_, handlers] : s_Instance->m_Subscribers)
		{
			for (auto& handler : handlers)
			{
				if (handler->GetType() == handle)
				{
					handlers.erase(std::find(handlers.begin(), handlers.end(), handler));
					return;
				}
			}
		}
	}

}