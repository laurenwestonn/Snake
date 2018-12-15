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

	sf::Vector2i tailHeadPos = m_snakeBody[m_snakeBody.size() - 1].position;
	sf::Vector2i upperTailPos = m_snakeBody[m_snakeBody.size() - 2].position;

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
	// Move up body parts to be in the position in front
	for (int i = m_snakeBody.size() - 1; i > 0; i--) {
		m_snakeBody[i].position = m_snakeBody[i - 1].position;
	}

	// Move head in direction the snake is going in
	if (m_dir == Direction::Up) {
		--m_snakeBody[0].position.y;
	}
	else if (m_dir == Direction::Right) {
		++m_snakeBody[0].position.x;
	}
	else if (m_dir == Direction::Down) {
		++m_snakeBody[0].position.y;
	}
	else if (m_dir == Direction::Left) {
		--m_snakeBody[0].position.x;


	}
}

void Snake::Tick()
{
	if (m_snakeBody.empty() || m_dir == Direction::None)
		return;

	Move();
	CheckCollision();

}

void Snake::Cut(int l_segment)
{
	for (int i = 0; i < l_segment; i++) {
		m_snakeBody.pop_back();
	}
	m_lives--;
	if (m_lives == 0) {
		Lose();
		return;
	}
}

void Snake::Render(sf::RenderWindow & l_window)
{
	if (m_snakeBody.empty())
		return;

	auto head = m_snakeBody.begin();

	m_bodyRect.setFillColor(sf::Color::Yellow);
	m_bodyRect.setPosition(head->position.x * m_size, head->position.y * m_size);

	l_window.draw(m_bodyRect);

	m_bodyRect.setFillColor(sf::Color::Green);
	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.end(); ++itr) {
		m_bodyRect.setPosition(itr->position.x * m_size, itr->position.y * m_size);
		l_window.draw(m_bodyRect);
	}
}

void Snake::CheckCollision()
{
	if (m_snakeBody.size() < 5)	// too small for self collision
		return;

	for (auto itr = m_snakeBody.begin() + 1; itr != m_snakeBody.begin(); ++itr) {
		if (itr->position == GetPosition()) {
			int segments = m_snakeBody.end() - itr; // no. of pieces to cut (from hit to tail)
			Cut(segments);
			break;
		}
	}
}
