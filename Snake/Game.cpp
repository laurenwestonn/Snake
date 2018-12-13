#include "Game.h"

Game::Game(): m_window("Chapter 2", sf::Vector2u(800,600))
{
	if (!m_santaTexture.loadFromFile("santa.jpg"))
		printf("Can't load the file");
	m_santa.setOrigin(m_santaTexture.getSize().x / 2, m_santaTexture.getSize().y / 2);
	m_santa.setPosition(200, 300);
	m_santa.setTexture(m_santaTexture);

	m_increment = sf::Vector2f(400, 400);
}


Game::~Game()
{
}

void Game::HandleInput()
{
	//Nothing for now
}

void Game::Update()
{
	m_window.Update();
	MoveSanta();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_window.Draw(m_santa);
	m_window.EndDraw();
}

void Game::UpdateClock()
{
	m_deltaSeconds = clock.restart().asSeconds();
}

float Game::GetDeltaSeconds()
{
	return m_deltaSeconds;
}

Window* Game::GetWindow()
{
	return &m_window;
}

void Game::MoveSanta()
{
	sf::Vector2u l_windSize = m_window.GetWindowSize();
	sf::Vector2u l_textSize = m_santaTexture.getSize();

	if ((m_santa.getPosition().x - (l_textSize.x / 2.0) + (m_increment.x * m_deltaSeconds) < 0)
		|| (m_santa.getPosition().x + (l_textSize.x / 2.0) + (m_increment.x* m_deltaSeconds) > l_windSize.x))
		m_increment.x = -m_increment.x;

	if ((m_santa.getPosition().y - (l_textSize.y / 2.0) + (m_increment.y * m_deltaSeconds) < 0)
		|| (m_santa.getPosition().y + (l_textSize.y / 2.0) + (m_increment.y * m_deltaSeconds) > l_windSize.y))
		m_increment.y = -m_increment.y;

	m_santa.setPosition(
		m_santa.getPosition().x + m_increment.x * m_deltaSeconds,
		m_santa.getPosition().y + m_increment.y * m_deltaSeconds);
}