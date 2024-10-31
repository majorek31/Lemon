#include "pch.h"

namespace Lemon
{

	void EventManager::Subscribe(size_t eventType, IEventHandlerWrapper* handler)
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
					return;
				}
			}
			handlers.emplace_back(handler);
		}
		else
		{
			m_Subscribers[eventType].emplace_back(std::move(handler));
		}
	}

	void EventManager::Unsubscribe(size_t eventId, size_t handlerId)
	{
		auto& handlers = m_Subscribers[eventId]; // Use reference instead of copying
		for (auto& it : handlers)
		{
			if (it->GetType() == handlerId)
			{
				handlers.erase(std::find(handlers.begin(), handlers.end(), it));
				return;
			}
		}
	}

	void EventManager::FireEvent(const Event& event)
	{
		for (auto& handler : m_Subscribers[event.GetEventType()])
			handler->Execute(event);
	}

	void EventManager::FireEvent(const Event* event)
	{
		for (auto& handler : m_Subscribers[event->GetEventType()])
			handler->Execute(*event);
	}

	void EventManager::QueueEvent(Event* event)
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
			delete event;
			m_EventsQueue.pop();
		}
	}

	EventManager& EventManager::Get()
	{
		if (s_Instance == nullptr)
			s_Instance = new EventManager;
		return *s_Instance;
	}

	void EventManager::Unsubscribe(EventHandlerHandle handle)
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