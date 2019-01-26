#pragma once
#include "BaseState.h"
#include "EventManager.h"

class State_MainMenu : public BaseState {
public:
	State_MainMenu(StateManager* l_stateManager);

	~State_MainMenu();

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void MouseClick(EventDetails* l_details);


private:
	sf::Text m_title;
	sf::Font m_font;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	unsigned int m_padding;

	sf::Vector2f m_buttonSize;
	sf::Vector2f m_buttonPosition;
	unsigned int m_buttonPadding;

	sf::RectangleShape m_rects[3];
	sf::Text m_labels[3];

};
