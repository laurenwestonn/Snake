#include "Snake.h"

Snake::Snake(int l_blockSize)
{
	m_size = l_blockSize;
	m_bodyRect.setSize(sf::Vector2f(m_size - 1, m_size - 1));
	Reset(); //starting position
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
	return (!m_snakeBody.empty() ?
		m_snakeBody.front().position : sf::Vector2i(1, 1));
}

bool Snake::HasLost()
{
	return m_lost;
}

void Snake::IncreaseScore()
{
	m_score += 10;
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
	if (m_snakeBody.empty())
		return;

	sf::Vector2i tailHeadPos = m_snakeBody.back().position();
	//sf::Vector2i tailHeadPos= m_snakeBody[m_snakeBody.size() - 1]; should be same as above.
	sf::Vector2i upperTailPos = m_snakeBody[m_snakeBody.size() - 2];

	// If we have a body and a tail, find new body from this
	if (m_snakeBody.size() > 1) {

		if (tailHeadPos.x == upperTailPos.x) { 
			
			// Tail is going up or down
			if (tailHeadPos.y > upperTailPos.y)	// End going up
				m_snakeBody.push_back(SnakeSegment(tailHeadPos.x,tailHeadPos.y + 1));
			else // End going down
				m_snakeBody.push_back(SnakeSegment(tailHeadPos.x, tailHeadPos.y - 1));
		}
		else if (tailHeadPos.y == upperTailPos.y) { 
			
			// Tail is going left or right
			if (tailHeadPos.x > upperTailPos.x)	// End going left
				m_snakeBody.push_back(SnakeSegment(tailHeadPos.x + 1, tailHeadPos.y));
			else // End going right
				m_snakeBody.push_back(SnakeSegment(tailHeadPos.x - 1, tailHeadPos.y));

		}

	}
	else { // Just a head. Get new body off direction pressed

		if (m_dir == Direction::Up)
			m_snakeBody.push_back(SnakeSegment(tailHeadPos.x, tailHeadPos.y + 1));

		else if (m_dir == Direction::Right)
			m_snakeBody.push_back(SnakeSegment(tailHeadPos.x - 1, tailHeadPos.y));

		else if (m_dir == Direction::Down)
			m_snakeBody.push_back(SnakeSegment(tailHeadPos.x, tailHeadPos.y - 1));

		else if (m_dir == Direction::Left)
			m_snakeBody.push_back(SnakeSegment(tailHeadPos.x + 1, tailHeadPos.y));

	}


}

void Snake::Reset()
{
	m_snakeBody.clear();
	m_snakeBody.push_back(SnakeSegment(5, 7));
	m_snakeBody.push_back(SnakeSegment(5, 6));
	m_snakeBody.push_back(SnakeSegment(5, 5));

	SetDirection(Direction::None);
	m_lives = 3;
	m_speed = 15;
	m_score = 0;
	m_lost = false;
}

void Snake::Move()
{

}

void Snake::Tick()
{
	if (m_snakeBody.empty || (m_dir == Direction::None))
		return;

	Move();
	CheckCollision();

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
