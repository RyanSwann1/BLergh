#include "StateGameOver.h"
#include "StateManager.h"
#include "GUIManager.h"
#include "SharedContext.h"
#include "EventManager.h"
#include "Window.h"

StateGameOver::StateGameOver(StateManager* stateManager)
	: StateBase(stateManager)
{
	m_type = StateType::GameOver;
}

StateGameOver::~StateGameOver()
{
}

void StateGameOver::onCreate()
{
	GUIManager* guiManager = m_stateManager->getSharedContext()->m_guiManager;
	FontManager* fontManager = m_stateManager->getSharedContext()->m_fontManager;
	GUIInterface gameOverInterface("GameOver");
	gameOverInterface.constructNewGuiElement(fontManager, GuiStyle(sf::Color::White, 18, sf::Vector2f(150, 50), "Magnificent"), "Game Over!", sf::Vector2f(400, 200));
	gameOverInterface.constructNewGuiElement(fontManager, GuiStyle(sf::Color::White, 18, sf::Vector2f(150, 50), "Magnificent"), "Retry", sf::Vector2f(400, 500));
	gameOverInterface.constructNewGuiElement(fontManager, GuiStyle(sf::Color::White, 18, sf::Vector2f(150, 50), "Magnificent"), "Main Menu", sf::Vector2f(400, 650));

	guiManager->addInterface("GameOver", gameOverInterface);
}

void StateGameOver::onEnter()
{
	EventManager* eventManager = m_stateManager->getSharedContext()->m_eventManager;
	eventManager->addCallback<StateGameOver>("Left_Click", StateType::GameOver, &StateGameOver::reactToInput, this);

	GUIManager* guiManager = m_stateManager->getSharedContext()->m_guiManager;
	guiManager->setInterfaceVisibility("GameOver", true);
	guiManager->setCurrentInterface("GameOver");
}

void StateGameOver::onDestroy()
{
	GUIManager* guiManager = m_stateManager->getSharedContext()->m_guiManager;
	guiManager->removeInterface("GameOver");
}

void StateGameOver::onExit()
{
	EventManager* eventManager = m_stateManager->getSharedContext()->m_eventManager;
	eventManager->removeCallback("Left_Click");

	GUIManager* guiManager = m_stateManager->getSharedContext()->m_guiManager;
	guiManager->setInterfaceVisibility("GameOver", false);
}

void StateGameOver::draw(sf::RenderWindow & window)
{
	GUIManager* guiManager = m_stateManager->getSharedContext()->m_guiManager;
	guiManager->draw(window);
}

void StateGameOver::reactToInput(const EventDetails * eventDetails)
{
	if (eventDetails->m_name == "Left_Click")
	{
		onMouseClick();
	}
}

void StateGameOver::onMouseClick()
{
	GUIManager* guiManager = m_stateManager->getSharedContext()->m_guiManager;
	sf::RenderWindow& window = m_stateManager->getSharedContext()->m_window->getWindow();
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	if (guiManager->interactingWithGuiEntry(mousePos, "Retry"))
	{
		m_stateManager->switchTo(StateType::Game);
		m_stateManager->removeState(StateType::GameOver);
	}
	else if (guiManager->interactingWithGuiEntry(mousePos, "Main Menu"))
	{
		m_stateManager->switchTo(StateType::MainMenu);
		m_stateManager->removeState(StateType::GameOver);
	}
}