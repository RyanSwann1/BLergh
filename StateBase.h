#pragma once

#include "StateType.h"
#include <SFML\Graphics.hpp>

struct EventDetails;
class StateManager;
class StateBase
{
public:
	StateBase(StateManager* stateManager)
	: m_stateManager(stateManager) {}

	virtual ~StateBase() {}

	virtual void onEnter() {}
	virtual void onExit() {}

	virtual void onCreate() {}
	virtual void onDestroy() {}

	virtual void update(const float deltaTime) {}
	virtual void draw(sf::RenderWindow& window) = 0;

	sf::View getView() const { return m_view; }
	StateType getType() const { return m_type; }

protected:
	StateManager* m_stateManager;
	sf::View m_view;
	StateType m_type;

private:
	StateBase(const StateBase&);
	StateBase& operator=(const StateBase&);
};

