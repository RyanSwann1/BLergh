#pragma once
#include "StateBase.h"

class StatePause :
	public StateBase
{
public:
	StatePause(StateManager* stateManager);
	~StatePause();

	void onEnter() override;
	void onExit() override;

	void onCreate() override;
	void onDestroy() override;

	void draw(sf::RenderWindow& window);

private:
	void reactToInput(const EventDetails* eventDetails);
	void onMouseClick();
};

