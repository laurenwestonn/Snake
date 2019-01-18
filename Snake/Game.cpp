#include "Game.h"

Game::Game() : 
	m_window("Snake", sf::Vector2u(800, 600)), 
	m_snake(20, &m_textbox), 
	m_world(sf::Vector2u(800,600), 20),
	m_stateManager(&m_context)
{
	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	m_stateManager.SwitchTo(StateType::Intro);

	if (!m_texture.loadFromFile("santa.jpg"))
		printf("Couldn't load santa.jpg");

	m_santa.setTexture(m_texture);
	m_santa.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);


	m_window.GetEventManager()->AddCallback(StateType::Game, "Move_sprite", &Game::MoveSprite, this);
}


Game::~Game()
{
}

void Game::HandleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && m_snake.GetPhysicalDirection() != Direction::Down)
		m_snake.SetDirection(Direction::Up);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_snake.GetPhysicalDirection() != Direction::Right)
		m_snake.SetDirection(Direction::Left);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && m_snake.GetPhysicalDirection() != Direction::Left)
		m_snake.SetDirection(Direction::Right);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && m_snake.GetPhysicalDirection() != Direction::Up)
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
	m_stateManager.Update(m_elapsed);
}

void Game::Render()
{
	m_window.BeginDraw();
	m_snake.Render(*m_window.GetRenderWindow());
	m_world.Render(*m_window.GetRenderWindow(), m_snake.GetLives());
	m_textbox.Render(*m_window.GetRenderWindow());
	m_window.Draw(m_santa);
	m_stateManager.Draw();
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

void Game::MoveSprite(EventDetails* l_details)
{
	sf::Vector2i mousePos = m_window.GetEventManager()->GetMousePos(m_window.GetRenderWindow());
	m_santa.setPosition(mousePos.x, mousePos.y);
	
	std::cout << "Move sprite to " << mousePos.x << ", " << mousePos.y << std::endl;
}

void Game::LateUpdate()
{
	m_stateManager.ProcessRequests();
	RestartClock();
}

Window* Game::GetWindow()
{
	return &m_window;
}