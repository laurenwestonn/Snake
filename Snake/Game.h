#pragma once
#include "Window.h"
#include "Snake.h"
#include "World.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	void RestartClock();
	sf::Time GetElapsed();

	Window* GetWindow();

private:
	Window m_window;

	sf::Clock clock;
	sf::Time m_elapsed;

	World m_world;
	Snake m_snake;
};

