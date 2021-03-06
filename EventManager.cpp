#include "EventManager.h"
#include "Window.h"
#include "SharedContext.h"
#include <fstream>
#include <sstream>
#include <iostream>
	
EventManager::EventManager()
{
	loadInBindings("Keys.txt");
}

EventManager::~EventManager()
{	
	for (auto &i : m_callBacks)
	{
		i.second.second = nullptr;
	}
	m_callBacks.clear();
}

void EventManager::handleEvent(sf::Event polledEvent)
{
	//Search through all bindings to attempt to match the event
	for (auto &bIter : m_bindings)
	{
		//Search through all events for this bind
		for (auto eIter : bIter.m_events)
		{
			EventType currentEvent = static_cast<EventType>(polledEvent.type);
			//If Event Type and polled event match
			if (eIter.second == currentEvent)
			{
				//If key was polled
				if (polledEvent.type == sf::Event::KeyPressed)
				{
					if (eIter.first.m_keyCode == polledEvent.key.code)
					{
						bIter.m_eventDetails.m_keyCode = eIter.first.m_keyCode;
						bIter.m_eventDetails.m_eventType = EventType::KeyPressed;
						++bIter.m_count;
					}
				}
				//If mouse button was polled
				else if (polledEvent.type == sf::Event::MouseButtonPressed)
				{
					if (eIter.first.m_keyCode == polledEvent.mouseButton.button)
					{
						bIter.m_eventDetails.m_keyCode = polledEvent.mouseButton.button;
						bIter.m_eventDetails.m_eventType = EventType::MouseButtonPressed;
						++bIter.m_count;
					}
				}
				break;
			}
		}
		if (static_cast<EventType>(polledEvent.type) == EventType::KeyReleased)
		{
			bIter.m_eventDetails.m_eventType = EventType::KeyReleased;
		}
	}
}

void EventManager::update()
{
	//Search through bindings
	for (auto &bIter : m_bindings)
	{
		//Check if bindings event has been activated
		if (bIter.m_count)
		{
			//Find callback
			auto iter = m_callBacks.find(bIter.m_name);
			if (iter != m_callBacks.cend())
			{
				//If callback matching the current state, activate
				if (m_currentStateType == iter->second.first)
				{
					iter->second.second(&bIter.m_eventDetails);
				}
			}

			if (bIter.m_eventDetails.m_eventType == EventType::KeyReleased ||
				bIter.m_eventDetails.m_eventType == EventType::MouseButtonReleased)
			{
				bIter.m_count = 0;
			}	
		}
	}
}

void EventManager::loadInBindings(const std::string & fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::cerr << "Failed to open: " << fileName << "\n";
		return;
	}
	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream keyStream(line);

		std::string name;
		int eventType = 0;
		int keyCode = -1;

		keyStream >> name >> eventType >> keyCode;

		//Will have to change, only supports one added event at each time
		Binding bind(name);
		bind.addEvent(EventInfo(keyCode), static_cast<EventType>(eventType));
		m_bindings.push_back(bind);
	}
}

void EventManager::removeCallback(const std::string & name)
{
	auto iter = m_callBacks.find(name);
	if (iter != m_callBacks.cend())
	{
		iter->second.second = nullptr;
		m_callBacks.erase(iter);
	}
}