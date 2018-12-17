#include "World.h"


World::World(sf::Vector2u l_windowSize, int l_blockSize)
{
	m_blockSize = l_blockSize;
	m_windowSize = l_windowSize;
	m_appleShape.setRadius(m_blockSize / 2);
	m_appleShape.setFillColor(sf::Color::Red);
	m_livesShape.setRadius(m_blockSize / 2 - 2);
	m_livesShape.setFillColor(sf::Color(255, 0, 50));
	m_livesShape.setPosition(l_windowSize.x - m_blockSize, 0);

	RespawnApple();

	// Set the bounds rectangles
	for (int i = 0; i < 4; i++) {
		m_bounds[i].setFillColor(sf::Color(150, 0, 0));

		if (i == 0 || i == 2) {
			m_bounds[i].setSize(sf::Vector2f(m_windowSize.x, m_blockSize));
		}
		else {
			m_bounds[i].setSize(sf::Vector2f(m_blockSize, m_windowSize.y));
		}

		if (i < 2) {
			m_bounds[i].setPosition(0, 0);
		}
		else {
			m_bounds[i].setOrigin(m_bounds[i].getSize()); // Set origin to be bottom right corner
			m_bounds[i].setPosition(sf::Vector2f(m_windowSize));
		}
	}
}

World::~World()
{
}

int World::GetBlockSize()
{
	return m_blockSize;
}

void World::RespawnApple()
{
	int columns = m_windowSize.x / m_blockSize - 2;
	int rows = m_windowSize.y / m_blockSize - 2;
	
	srand(time(nullptr));
	m_item = sf::Vector2i(rand() % columns + 1, rand() % rows + 1);
	m_appleShape.setPosition(m_item.x * m_blockSize, m_item.y * m_blockSize);
}

void World::Update(Snake& l_player)
{
	if (l_player.GetPosition() == m_item) { // Head is at an item; apple eaten
		l_player.Extend();
		l_player.IncreaseScore();
		RespawnApple();
	}
	if (l_player.GetPosition().x < 1 || l_player.GetPosition().x > (m_windowSize.x / m_blockSize - 2)
		|| l_player.GetPosition().y < 1 || l_player.GetPosition().y > (m_windowSize.y / m_blockSize - 2)) {
		l_player.Lose();
	}
}

void World::Render(sf::RenderWindow &l_window, int lives)
{
	for (int i = 0; i < 4; i++) {
		l_window.draw(m_bounds[i]);
	}
	l_window.draw(m_appleShape);

	for (int i = lives; i >= 1; i--) {
		l_window.draw(m_livesShape);
		m_livesShape.move(sf::Vector2f(-m_blockSize, 0));
	}
	m_livesShape.setPosition(l_window.getSize().x - m_blockSize, 0);

}

sf::Vector2i World::GetItemPosition()
{
	return m_item;
}
