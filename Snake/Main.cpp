#include <SFML/Graphics.hpp>

int main(int argc, char** argv[])
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Boop");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(200, 170));
		rect.setFillColor(sf::Color(255, 190, 210, 255));
		rect.setPosition(100, 100);

		window.clear(sf::Color::Black);
		window.draw(rect);
		window.display();
	}
}
