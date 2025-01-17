#include <iostream>
#include "SFML/Graphics.hpp"

int main() {
	std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
	sf::RenderWindow window(fullscreenModes.at(0), "Escape The Dungeon", sf::Style::Fullscreen);

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(50, 50));
	rectangle.setFillColor(sf::Color::Blue);
	rectangle.setPosition(sf::Vector2f(0, 0));

	sf::Event event;

	while (window.isOpen()) {
		// Poll events

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				std::cout << "Ferme" << std::endl;
				break;
			}
		}

		// Draw / Render
		window.clear();
		window.draw(rectangle);
		window.display();
	}

	std::cout << "Hello" << std::endl;
}