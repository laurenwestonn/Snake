#include "Game.h"

Game::Game() : m_window("Snake", sf::Vector2u(800, 600)), m_snake(20), m_world(sf::Vector2u(800,600), 20)
{
}


Game::~Game()
{
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetDirection() != Direction::Down)
		m_snake.SetDirection(Direction::Up);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetDirection() != Direction::Right)
		m_snake.SetDirection(Direction::Left);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetDirection() != Direction::Left)
		m_snake.SetDirection(Direction::Right);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetDirection() != Direction::Up)
		m_snake.SetDirection(Direction::Down);
}

void Game::Update()
{
	float timestep = 1.0f / m_snake.GetSpeed();

	if (m_elapsed.asSeconds() >= timestep) {
		m_snake.Tick();
		m_world.Update(m_snake);
		m_elapsed -= sf::seconds(timestep);
		if (m_snake.HasLost()) {
			m_snake.Reset();
		}
	}
	m_window.Update();
}

void Game::Render()
{
	m_window.BeginDraw();
	m_snake.Render(*m_window.GetRenderWindow());
	m_world.Render(*m_window.GetRenderWindow(), m_snake.getLives());
	m_window.EndDraw();
}

void Game::RestartClock()
{
	m_elapsed += clock.restart();
}

sf::Time Game::GetElapsed()
{
	return m_elapsed;
}

Window* Game::GetWindow()
{
	return &m_window;
}