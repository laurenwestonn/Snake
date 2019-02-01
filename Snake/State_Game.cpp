#include "State_Game.h"


State_Game::State_Game(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}


State_Game::~State_Game() { }

void State_Game::OnCreate()
{
	if (m_texture.loadFromFile("santa.jpg"))
		m_sprite.setTexture(m_texture);
	else
		printf("Couldn't load santa.jpg\n");


	sf::Vector2u wSize = m_stateManager->GetSharedContext()->m_wind->GetWindowSize();
	m_sprite.setPosition(wSize.x / 2.0f, wSize.y / 2.0f); // Start in the middle

	m_sprite.setOrigin(m_texture.getSize().x / 2.0f, m_texture.getSize().y / 2.0f);

	m_speedDir = sf::Vector2f(200,200);

	m_stateManager->GetSharedContext()->m_eventManager->AddCallback(StateType::Game, "Key_P", &State_Game::Pause, this);
	m_stateManager->GetSharedContext()->m_eventManager->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);

}

void State_Game::OnDestroy()
{
	m_stateManager->GetSharedContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_P");
	m_stateManager->GetSharedContext()->m_eventManager->RemoveCallback(StateType::Game, "Key_Escape");
}

void State_Game::Activate()
{
}

void State_Game::Deactivate()
{
}

void State_Game::Update(const sf::Time & l_time)
{
	sf::Vector2f currPos = m_sprite.getPosition();
	sf::Vector2u windowSize = m_stateManager->GetSharedContext()->m_wind->GetWindowSize();

	int halfX = m_texture.getSize().x/ 2.0f;
	int halfY = m_texture.getSize().y / 2.0f;

	if (currPos.x + (m_speedDir.x * l_time.asSeconds()) - halfX < 0
		|| currPos.x + (m_speedDir.x * l_time.asSeconds()) + halfX > windowSize.x)
		m_speedDir.x *= -1.1f;

	if (currPos.y + (m_speedDir.y * l_time.asSeconds() - halfY) < 0
		|| currPos.y + (m_speedDir.y * l_time.asSeconds() + halfY) > windowSize.y)
		m_speedDir.y *= -0.9f;

	m_sprite.setPosition(m_sprite.getPosition() + (m_speedDir * l_time.asSeconds()));
}

void State_Game::Draw()
{
	m_stateManager->GetSharedContext()->m_wind->GetRenderWindow()->draw(m_sprite);
}

void State_Game::Pause(EventDetails* l_details)
{
	printf("Pause here!\n");
	m_stateManager->SwitchTo(StateType::MainMenu);
}

void State_Game::MainMenu(EventDetails* l_details)
{
	printf("Main menu\n");
	m_stateManager->SwitchTo(StateType::MainMenu);
}
