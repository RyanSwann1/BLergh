#pragma once
#include "StateBase.h"
class StateMainMenu :
	public StateBase
{
public:
	StateMainMenu(StateManager* stateManager);
	~StateMainMenu();

	void onEnter() override;
	void onExit() override;
	void onCreate() override;
	void onDestroy() override;

	void draw(sf::RenderWindow& window) override;

private:
	void reactToInput(const EventDetails* eventDetails);
	void onMouseClick();
};