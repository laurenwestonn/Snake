#pragma once
#include <SFML\Graphics.hpp>

using SnakeContainer = std::vector<SnakeSegment>;

struct SnakeSegment {
	SnakeSegment(int x, int y) : position(x,y) {}
	sf::Vector2i position;
};

enum class Direction {
	None,
	Up,
	Down,
	Left,
	Right
};

class Snake
{
public:
	Snake(int l_blockSize);
	~Snake();

	void SetDirection(Direction l_dir);
	Direction GetDirection();
	int GetLives();
	int GetSpeed();
	int GetScore();
	sf::Vector2i GetPosition();
	bool HasLost();

	void ToggleLost();
	void Lose();
	void IncreaseScore();

	void Extend();	// Grow snake
	void Reset();	// To starting position

	void Move();	// Move
	void Tick();	// Update
	void Cut(int l_segment); // Cute the snake

	void Render(sf::RenderWindow &l_window);


private:
	void CheckCollision();

	SnakeContainer m_snakeBody;
	int m_size;
	Direction m_dir;
	int m_lives;
	int m_score;
	int m_speed;
	bool m_lost;
	sf::RectangleShape m_bodyRect;
};

