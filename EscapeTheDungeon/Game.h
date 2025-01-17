#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <memory>

#include "SFML/Graphics.hpp"

class Game {
public:
	Game();
	void run();

public:
	std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
	sf::Event event;
	sf::Clock Clock;
	bool isRunning;
	float deltaTime;
	sf::RenderWindow window;
};

class Entity {
protected:
	virtual void update(float deltaTime, sf::Vector2f &position) = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
};

#endif // !GAME_H