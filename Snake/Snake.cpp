#include "Snake.h"



Snake::Snake()
{
}


Snake::Snake(int l_blockSize)
{
}

Snake::~Snake()
{
}

void Snake::SetDirection(Direction l_dir)
{
	m_dir = l_dir;
}

Direction Snake::GetDirection()
{
	return m_dir;
}

int Snake::GetLives()
{
	return m_lives;
}

int Snake::GetSpeed()
{
	return m_speed;
}

int Snake::GetScore()
{
	return m_score;
}

sf::Vector2i Snake::GetPosition()
{
	return sf::Vector2i();
}

bool Snake::HasLost()
{
	return m_lost;
}

void Snake::IncreaseScore()
{
	m_score++;
}

void Snake::Lose()
{
}

void Snake::ToggleLost()
{
	m_lost = !m_lost;
}

void Snake::Extend()
{
}

void Snake::Reset()
{
}

void Snake::Move()
{
}

void Snake::Tick()
{
}

void Snake::Cut(int l_segment)
{
}

void Snake::Render(sf::RenderWindow & l_window)
{
}

void Snake::CheckCollision()
{
}
