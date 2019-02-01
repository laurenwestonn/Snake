#include "State_Pause.h"

State_Pause::State_Pause(StateManager* l_stateManager)
	:BaseState(l_stateManager) { }

State_Pause::~State_Pause() { }

void State_Pause::OnCreate()
{

	SetTransparent(true);	// MAKE THIS PAUSED STATE TRANSPARENT

	const auto winSize = m_stateManager->GetSharedContext()->m_wind->GetWindowSize();

	if (m_font.loadFromFile("ALIEN5.ttf"))
	{
		m_text.setFont(m_font);
		m_text.setCharacterSize(30);
		m_text.setFillColor(sf::Color::White);
		m_text.setStyle(sf::Text::Style::Bold);
		m_text.setPosition(winSize.x / 2.0f, winSize.y / 2.0f);
		m_text.setString("PAUSED");
	}
	else
		printf("Can't load font ALIEN5.ttf in the paused state.\n");

	m_backdrop.setSize(sf::Vector2f(winSize));
	m_backdrop.setPosition(0, 0);
	m_backdrop.setFillColor(sf::Color(0, 0, 0, 150));

	m_stateManager->GetSharedContext()->m_eventManager->AddCallback(StateType::Pause, "Key_P", &State_Pause::UnPause, this);
}

void State_Pause::OnDestroy()
{
}

void State_Pause::Activate()
{
}

void State_Pause::Deactivate()
{
}

void State_Pause::Update(const sf::Time& l_time)
{
}

void State_Pause::Draw()
{
	sf::RenderWindow* rw = m_stateManager->GetSharedContext()->m_wind->GetRenderWindow();
	rw->draw(m_backdrop);
	rw->draw(m_text);
}

void State_Pause::UnPause(EventDetails* l_details)
{
	printf("Un-pause!");
	m_stateManager->SwitchTo(StateType::Game);
}
