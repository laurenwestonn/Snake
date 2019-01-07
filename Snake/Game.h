#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Snake.h"
#include "World.h"
#include "Textbox.h"

struct SharedContext
{
	SharedContext() : m_wind(nullptr), m_eventManager(nullptr) {}
	Window *m_wind;
	EventManager *m_eventManager;
};

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
	void MoveSprite(EventDetails* l_details);

	Window* GetWindow();

private:
	Window m_window;

	sf::Clock clock;
	sf::Time m_elapsed;

	World m_world;
	Snake m_snake;
	Textbox m_textbox;

	sf::Texture m_texture;
	sf::Sprite m_santa;
};

