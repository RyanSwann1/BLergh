#include "StateGame.h"
#include "SharedContext.h"
#include "StateManager.h"
#include "EntityManager.h"
#include "Map.h"
#include "Player.h"
#include "Rat.h"
#include "Window.h"
#include "Character.h"
#include "EventManager.h"

StateGame::StateGame(StateManager* stateManager)
	: StateBase(stateManager),
	m_camera(stateManager->getSharedContext()),
	m_map(nullptr),
	m_audioPlayer(stateManager->getSharedContext()),
	m_paused(false)
{
	m_type = StateType::Game;
}


StateGame::~StateGame()
{

}

void StateGame::onCreate()
{
	m_map = new Map(m_stateManager->getSharedContext());
	m_map->loadNextLevel();

	m_audioPlayer.registerAudioClip("Game", "BackgroundMusic");
	m_audioPlayer.registerOwner("Game");

	EventManager* eventManager = m_stateManager->getSharedContext()->m_eventManager;
	eventManager->addCallback<StateGame>("Pause", StateType::Game, &StateGame::reactToInput, this);
	eventManager->addCallback<StateGame>("UnPause", StateType::Game, &StateGame::reactToInput, this);
}

void StateGame::onEnter()
{
	//m_audioPlayer.play("BackgroundMusic", true);
	m_paused = false;
}

void StateGame::onExit()
{
	m_camera.reset();
	m_audioPlayer.stop("BackgroundMusic");
}

void StateGame::onDestroy()
{
	delete m_map;
	m_map = nullptr;

	m_stateManager->getSharedContext()->m_map = nullptr;
	EntityManager* entityManager = m_stateManager->getSharedContext()->m_entityManager;
	m_stateManager->removeState(StateType::Paused);
	entityManager->purgeEntities();
}

void StateGame::update(const float deltaTime)
{
	//Do not update game if paused
	if (m_paused) {
		return;
	}
	m_map->update();

	SharedContext* sharedContext = m_stateManager->getSharedContext();
	Window* window = sharedContext->m_window;
	//Set position for the state's view
	Character* player = static_cast<Character*>(sharedContext->m_entityManager->findEntity("Player"));
	if (player)
	{
		m_camera.update(player);
	}
	//If player does not exist, spawn new player
	else
	{	
		m_camera.reset();
		if (!m_map->loadingNextMap())
		{
			m_stateManager->switchTo(StateType::GameOver);
			m_stateManager->removeState(StateType::Game);
		}	
	}
	
	sharedContext->m_entityManager->update(deltaTime);
}

void StateGame::draw(sf::RenderWindow & window)
{
	SharedContext* sharedContext = m_stateManager->getSharedContext();

	if (m_map)
	{
		m_map->draw(window);
	}
	
	sharedContext->m_entityManager->draw(window);
}

void StateGame::reactToInput(const EventDetails * eventDetails)
{
	if(eventDetails->m_name == "Pause")
	{ 
		m_paused = true;
		m_stateManager->switchTo(StateType::Paused);
	}
}