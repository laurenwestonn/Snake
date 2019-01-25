#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_Intro : public BaseState // inherit from template class
{
public:

	State_Intro(StateManager* l_state_manager);

	// Methods inherited from the BaseState
	void OnCreate() override;
	void OnDestroy() override;
	void Update(const sf::Time& l_time) override;
	void Draw() override;
	void Activate() override;
	void Deactivate() override;

	void Continue(EventDetails* l_details);

private:
	sf::Texture m_introTexture;
	sf::Sprite m_introSprite;
	sf::Font m_introFont;
	sf::Text m_introText;
	float m_timePassed;

};

