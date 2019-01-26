#include "Textbox.h"

Textbox::Textbox()
{
	Setup(5, 10, 200, sf::Vector2f(0,0));
}

Textbox::Textbox(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos)
{
	Setup(l_visible, l_charSize, l_width, l_screenPos);
}

//Destructor
Textbox::~Textbox() { Clear();}

void Textbox::Setup(int l_visible, int l_charSize, int l_width, sf::Vector2f l_screenPos)
{
	m_numVisible = l_visible;

	sf::Vector2f l_padding(2.0f, 2.0f);

	m_font.loadFromFile("fonts\\films.Dynasty.ttf");
	m_content.setFont(m_font);
	m_content.setCharacterSize(l_charSize);
	m_content.setString("");
	m_content.setFillColor(sf::Color::White);
	m_content.setPosition(l_screenPos + l_padding);

	m_backdrop.setSize(sf::Vector2f(float(l_width), float(l_visible * l_charSize * 1.2f)));
	m_backdrop.setFillColor(sf::Color(90,90,90,90));
	m_backdrop.setPosition(l_screenPos);
}

void Textbox::Add(std::string l_message)
{
	m_messages.push_back(l_message);

	if (m_messages.size() > m_numVisible) {
		m_messages.erase(m_messages.begin());
	}
}

void Textbox::Clear()
{
	m_messages.clear();
}

void Textbox::Render(sf::RenderWindow & l_wind)
{
	std::string totalContent;
	// Accumulate all the messages in one string
	for (auto &itr : m_messages) {
		totalContent += itr + "\n";
	}

	// Set string to be a 'Text' obj - (font, colour, size...)
	if (totalContent != "") {
		m_content.setString(totalContent);
		l_wind.draw(m_backdrop);
		l_wind.draw(m_content);
	}
}

sf::RectangleShape Textbox::GetBackdrop()
{
	return m_backdrop;
}
