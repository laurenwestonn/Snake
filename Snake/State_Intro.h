#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState // inherit from template class
{
public:

	State_Intro(StateManager* l_stateManager);

	// Methods inherited from the BaseState
	void OnCreate();
	void OnDestroy();
	void Update(const sf::Time& l_time);
	void Draw();
	void Activate();
	void Deactivate();

	void Continue(EventDetails* l_details);

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Font m_introFont;
	sf::Text m_introText;
	float m_timePassed;

};

