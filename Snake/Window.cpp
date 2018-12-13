#include "Window.h"

Window::Window()
{
	Setup("Default window name", sf::Vector2u(500, 500));
}

Window::Window(const std::string & l_title, const sf::Vector2u & l_size)
{
	Setup(l_title, l_size);
}

Window::~Window()
{
	Destroy();
}

void Window::BeginDraw()
{
	m_window.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	m_window.display();
}

void Window::Update()
{
	sf::Event evt;
	while (m_window.pollEvent(evt)) {
		if (evt.type == sf::Event::Closed || 
			(evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Escape)) {
			m_isDone = true;
		}
		else if (evt.type == sf::Event::KeyPressed &&
									evt.key.code == sf::Keyboard::F5) {
			ToggleFullscreen();

		}
	}
}

bool Window::IsDone()
{
	return m_isDone;
}

bool Window::IsFullscreen()
{
	return m_isFullscreen;
}

sf::Vector2u Window::GetWindowSize()
{
	return m_windowSize;
}

void Window::ToggleFullscreen()
{
	m_isFullscreen = !m_isFullscreen;

	Destroy();
	Create();
}

void Window::Draw(sf::Drawable & l_drawable)
{
	m_window.draw(l_drawable);
}

void Window::Setup(const std::string & l_title, const sf::Vector2u & l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;

	m_isDone = false;
	m_isFullscreen = false;

	Create();
}

void Window::Destroy()
{
	m_window.close();
}

void Window::Create()
{
	auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
}
