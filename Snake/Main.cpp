#include <SFML/Graphics.hpp>

int main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Boop");

	sf::Texture texture;
	if (!texture.loadFromFile("santa.jpg"))
		printf("Couldn't load jpg");

	sf::Sprite santa(texture);
	santa.setPosition(320, 240);
	santa.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

	float xDir = 0.4;
	float yDir = 0.4;

	while (window.isOpen()) {
		window.clear(sf::Color::Black);

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if ((santa.getPosition().x - (texture.getSize().x / 2) + xDir) < 0 ||
			(santa.getPosition().x + (texture.getSize().x / 2) + xDir) > window.getSize().x) {
			xDir *= -1;
			santa.setColor(sf::Color(255, 100, 100, 255));
		}

		if ((santa.getPosition().y - (texture.getSize().y / 2) + yDir) < 0 ||
			(santa.getPosition().y + (texture.getSize().y / 2) + yDir) > window.getSize().y) {
			yDir *= -1;
			santa.setColor(sf::Color(100, 100, 255, 255));
		}

		santa.setPosition(santa.getPosition().x + xDir, santa.getPosition().y + yDir);
		window.draw(santa);
		window.display();
	}
}
