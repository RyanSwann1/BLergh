#pragma once
#include "StateBase.h"
struct EventDetails;
class StateGameOver :
	public StateBase
{
public:
	StateGameOver(StateManager* stateManager);
	~StateGameOver();

	void onCreate() override;
	void onDestroy() override;

	void onEnter() override;
	void onExit() override;

	void draw(sf::RenderWindow& window) override;

private:
	void reactToInput(const EventDetails* eventDetails);
	void onMouseClick();
};

