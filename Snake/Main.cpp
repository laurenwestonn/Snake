#include "Main.h"
#include <SFML/Graphics.hpp>


Main::Main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "The Window");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear(sf::Color::Black);
		window.display();
	}
}


Main::~Main()
{
}
