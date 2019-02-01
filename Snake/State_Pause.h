#pragma once
#include "BaseState.h"
#include "StateManager.h"
#include "SharedContext.h"


class State_Pause :
	public BaseState
{
public:
	State_Pause(StateManager *l_stateManager);
	~State_Pause();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void UnPause(EventDetails* l_details);

private:
	sf::Text m_text;
	sf::Font m_font;
	sf::RectangleShape m_backdrop;
};

