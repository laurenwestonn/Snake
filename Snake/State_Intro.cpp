#include "State_Intro.h"
#include "StateManager.h"


State_Intro::State_Intro(StateManager* l_state_manager)
	: BaseState(l_state_manager)
{
	m_timePassed = 0;
}

void State_Intro::OnCreate()
{
	printf("Creating intro state\n");

	const auto window_size = m_stateManager->GetSharedContext()->m_wind->GetWindowSize();

	m_introTexture.loadFromFile("intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
	m_introSprite.setPosition((window_size.x / 2.0f), 0.0f);	// Start at the top, in the middle

	m_introFont.loadFromFile("ALIEN5.ttf");
	m_introText.setFont(m_introFont);
	m_introText.setString({ "Press SPACE to continue" });
	m_introText.setCharacterSize(10);

	const sf::FloatRect text_rec = m_introText.getLocalBounds();
	m_introText.setOrigin(sf::Vector2f(text_rec.left + text_rec.width / 2, text_rec.top + text_rec.height / 2));
	m_introText.setPosition(sf::Vector2f(float(window_size.x) / 2, float(window_size.y) / 3 * 2));

	EventManager *event_manager = m_stateManager->GetSharedContext()->m_eventManager;
	event_manager->AddCallback(StateType::Intro, "Intro_Continue", &State_Intro::Continue,this);
}

void State_Intro::OnDestroy()
{
	m_stateManager->GetSharedContext()->m_eventManager->
		RemoveCallback(StateType::Intro, "Intro_Continue");

}

void State_Intro::Update(const sf::Time& l_time)
{
	if (m_timePassed < 3.0f) {	// Been less than 3 seconds
		m_introSprite.setPosition(
			m_introSprite.getPosition().x, 
			m_introSprite.getPosition().y + (100 * l_time.asSeconds())); // Move down 48 per sec
	}

	m_timePassed += l_time.asSeconds(); // Keep updating the time
}

void State_Intro::Draw()
{
	m_stateManager->GetSharedContext()->m_wind->Draw(m_introSprite);
	if (m_timePassed >= 3.0f)
		m_stateManager->GetSharedContext()->m_wind->Draw(m_introText);
}

void State_Intro::Activate() { }
void State_Intro::Deactivate() { }

void State_Intro::Continue(EventDetails * l_details)
{
	if (m_timePassed >= 3.0f) {
		m_stateManager->SwitchTo(StateType::MainMenu);
		m_stateManager->Remove(StateType::Intro);
	}

}
