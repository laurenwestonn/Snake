#pragma once
#include "BaseState.h"
#include "StateManager.h"
#include "SharedContext.h"

class State_Game :
	public BaseState
{
public:
	State_Game(StateManager* l_stateManager);
	~State_Game();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void Pause(EventDetails* l_details);
	void MainMenu(EventDetails* l_details);


private:
	sf::Texture m_texture; 
	sf::Sprite m_sprite;

	sf::Vector2f m_speedDir;

};

