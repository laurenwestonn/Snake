#pragma once
#include "Window.h"
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void HandleInput();
	void Update();
	void Render();

	void UpdateClock();
	float GetDeltaSeconds();

	Window* GetWindow();

private:
	void MoveSanta();
	Window m_window;

	sf::Texture m_santaTexture;
	sf::Sprite m_santa;
	sf::Vector2f m_increment;

	sf::Clock clock;
	float m_deltaSeconds;
};

