#pragma once
#include "Window.h"
//#include "Textbox.h"
#include "StateManager.h"

class Game
{
public:
	Game();
	~Game();

	void Update();
	void Render();

	void RestartClock();
	sf::Time GetElapsed();
	void LateUpdate();

	Window* GetWindow();

private:
	Window m_window;
	StateManager m_stateManager;
	SharedContext m_context;

	sf::Clock m_clock;
	sf::Time m_elapsed;

	sf::Texture m_texture;
	sf::Sprite m_santa;
};

