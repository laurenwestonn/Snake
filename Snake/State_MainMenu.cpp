#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}

State_MainMenu::~State_MainMenu()
{
}

void State_MainMenu::OnCreate()
{
	auto sharedContext = m_stateManager->GetSharedContext();
	auto windowSize = sharedContext->m_wind->GetWindowSize();

	// Graphical elements
	m_size = sf::Vector2f(windowSize.x * 0.8, windowSize.y * 0.8);
	m_padding = windowSize.x * 0.1;
	

	// Text members. Font, words, size, colour, origin, position
	sf::Font font;
	font.loadFromFile("ALIEN5.ttf");
	m_title.setFont(font);
	m_title.setString(sf::String("MAIN MENU"));
	m_title.setCharacterSize(15);

	sf::FloatRect textRect = m_title.getLocalBounds();
	m_title.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	m_title.setPosition(windowSize.x * 0.5, windowSize.y * 0.2);

	// Button positions
	m_buttonSize = sf::Vector2f(300.0f, 30.f);
	m_buttonPosition = sf::Vector2f(windowSize.x * 0.5, windowSize.y * 0.5);
	m_buttonPadding = 4; // 4px

	// Button labels
	std::string str[3];
	str[0] = "PLAY";
	str[1] = "Credits";
	str[2] = "Exit";

	// Buttons
	for (int i = 0; i <= 2; i++) {
		sf::Vector2f buttonPosition(
			m_buttonPosition.x,
			m_buttonPosition.y + (i * (m_buttonPadding + m_buttonSize.y)));

		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::Red);

		m_rects[i].setOrigin(m_buttonSize.x * 0.5f, m_buttonSize.y * 0.5f);
		m_rects[i].setPosition(buttonPosition);

		m_labels[i].setFont(font);
		m_labels[i].setString(str[i]);
		m_labels[i].setCharacterSize(12);
		
		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width * 0.5f, rect.top + rect.height * 0.5f);

		m_labels->setPosition(buttonPosition);
	}

	// Mouse click callback
	sharedContext->m_eventManager->AddCallback(StateType::MainMenu, "Mouse_Left", &State_MainMenu::MouseClick, this);
}

void State_MainMenu::OnDestroy()
{
	EventManager* eventMan = m_stateManager->GetSharedContext()->m_eventManager;
	eventMan->RemoveCallback(StateType::MainMenu, "Mouse_Left");
}

void State_MainMenu::Activate()
{
	// If you've been to the game state already, the button should say resume
	if (m_stateManager->HasState(StateType::Game)
		&& m_labels[0].getString() == "PLAY")
	{
		printf("Updating the main menu button from PLAY to Resume");

		m_labels[0].setString("Resume");
		
		sf::FloatRect bounds = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(bounds.left + bounds.width / 2.0f,
			bounds.top + bounds.height / 2.0f);
	}

}

void State_MainMenu::Deactivate()
{
}

void State_MainMenu::Update(const sf::Time & l_time)
{
}

void State_MainMenu::Draw()
{
	// Get the render window
	Window* window = m_stateManager->GetSharedContext()->m_wind;

	sf::Text testText;

	
	sf::Font font;
	font.loadFromFile("ALIEN5.ttf");
	testText.setFont(font);
	testText.setString(sf::String("MAIN MENU"));
	testText.setCharacterSize(15);
	
	sf::FloatRect textRect = testText.getLocalBounds();
	testText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	testText.setPosition(300, 300);


	m_stateManager->GetSharedContext()->m_wind->GetRenderWindow()->draw(testText);


	m_stateManager->GetSharedContext()->m_wind->GetRenderWindow()->draw(m_title);
	
	for (int i = 0; i < 3; ++i) {
		m_stateManager->GetSharedContext()->m_wind->GetRenderWindow()->draw(m_rects[i]);
		m_stateManager->GetSharedContext()->m_wind->GetRenderWindow()->draw(m_labels[i]);
	}
}

void State_MainMenu::MouseClick(EventDetails * l_details)
{
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;

	// Check each button
	for (int i = 0; i < 3; i++)
	{
		// Check each bound
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			printf("Button %d was clicked", i+1);
			if (i == 0)
				m_stateManager->SwitchTo(StateType::Game);
			else if (i == 1)
				;//credits
			else if (i == 2)
				m_stateManager->GetSharedContext()->m_wind->Close();
;		}

	}
}
