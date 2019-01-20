#include "State_Intro.h"
#include "StateManager.h"


State_Intro::State_Intro(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

void State_Intro::OnCreate()
{
	printf("Creating intro state\n");
	m_timePassed = 0;

	sf::Vector2u windowSize = m_stateManager->GetSharedContext()->m_wind->GetWindowSize();

	m_introTexture.loadFromFile("intro.png");
	m_introSprite.setTexture(m_introTexture);
	m_introSprite.setOrigin(m_introTexture.getSize().x / 2.0f, m_introTexture.getSize().y / 2.0f);
	m_introSprite.setPosition((windowSize.x / 2.0f), 0.0f);	// Start at the top, in the middle

	m_introFont.loadFromFile("ALIEN5.ttf");
	m_introText.setFont(m_introFont);
	m_introText.setString({ "Press SPACE to continue" });
	m_introText.setCharacterSize(10);

	sf::FloatRect textRec = m_introText.getLocalBounds();
	m_introText.setOrigin(sf::Vector2f(textRec.left + textRec.width / 2, textRec.top + textRec.height / 2));
	m_introText.setPosition(sf::Vector2f(windowSize.x / 2, windowSize.y / 3 * 2));

	EventManager *eventManager = m_stateManager->GetSharedContext()->m_eventManager;
	eventManager->AddCallback(StateType::Intro, "Intro_continue", &State_Intro::Continue,this);
}

void State_Intro::OnDestroy()
{
	m_stateManager->GetSharedContext()->m_eventManager->
		RemoveCallback(StateType::Intro, "Intro_continue");

}

void State_Intro::Update(const sf::Time& l_time)
{
	if (m_timePassed < 5.0f) {	// Been less than 5 seconds
		printf("It's still less than 5 secs. It's been %f seconds. Sprite at %f, %f. Increase y by %f\n", 
			m_timePassed,
			m_introSprite.getPosition().x, m_introSprite.getPosition().y,
			(4 * l_time.asSeconds()));
		
		m_timePassed += l_time.asSeconds(); // Keep updating the time
		m_introSprite.setPosition(
			m_introSprite.getPosition().x, 
			m_introSprite.getPosition().y + (48 * l_time.asSeconds())); // Move down 48 per sec
	} else
 		printf("Been over 5 secs. Stop the sprite from moving. It's now at %f, %f\n", m_introSprite.getPosition().x, m_introSprite.getPosition().y);
}

void State_Intro::Draw()
{
	m_stateManager->GetSharedContext()->m_wind->Draw(m_introSprite);
	if (m_timePassed > 5.0f)
		m_stateManager->GetSharedContext()->m_wind->Draw(m_introText);
}

void State_Intro::Activate() { }
void State_Intro::Deactivate() { }

void State_Intro::Continue(EventDetails * l_details)
{
	if (m_timePassed >= 5.0f) {
		m_stateManager->SwitchTo(StateType::MainMenu);
		m_stateManager->Remove(StateType::Intro);
	}

}
