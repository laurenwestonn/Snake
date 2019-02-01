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

	virtual void OnCreate() override;
	virtual void OnDestroy() override;

	virtual void Activate() override;
	virtual void Deactivate() override;

	virtual void Update(const sf::Time& l_time) override;
	virtual void Draw() override;

	void UnPause(EventDetails* l_details);

private:
	sf::Text m_text;
	sf::Font m_font;
	sf::RectangleShape m_backdrop;
};

