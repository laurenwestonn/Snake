#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
class World
{
public:
	World(sf::Vector2u l_windowSize, int l_blockSize);
	~World();

	int GetBlockSize();
	void RespawnApple();

	void Update(Snake& l_player);
	void Render(sf::RenderWindow &l_window, int lives);
	sf::Vector2i GetItemPosition();

private:
	sf::Vector2u m_windowSize;
	sf::Vector2i m_item;
	int m_blockSize;

	sf::RectangleShape m_bounds[4];
	sf::CircleShape m_appleShape;
	sf::CircleShape m_livesShape;
};

