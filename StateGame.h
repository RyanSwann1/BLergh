#pragma once

#include "StateBase.h"
#include "EntitySpawner.h"
#include "Rat.h"
#include "Camera.h"
#include "AudioPlayer.h"

struct EventDetails;
class Player;
class Map;
class StateGame :
	public StateBase
{
public:
	StateGame(StateManager* stateManager);
	~StateGame();

	void onEnter() override;
	void onExit() override;

	void onCreate() override;
	void onDestroy() override;

	void update(const float deltaTime) override;
	void draw(sf::RenderWindow& window) override;

private:
	Map* m_map;
	Camera m_camera;
	AudioPlayer m_audioPlayer;
	bool m_paused;

	void reactToInput(const EventDetails* eventDetails);
};

