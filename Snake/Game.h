#pragma once
#include "Window.h"
//#include "Snake.h"
//#include "World.h"
//#include "Textbox.h"
#include "StateManager.h"

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
	void LateUpdate();

	Window* GetWindow();

private:
	Window m_window;
	StateManager m_stateManager;
	SharedContext m_context;

	sf::Clock clock;
	sf::Time m_elapsed;

	//World m_world;
	//Snake m_snake;
	//Textbox m_textbox;

	sf::Texture m_texture;
	sf::Sprite m_santa;
};

