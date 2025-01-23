#ifndef PLAYER_H
#define PLAYER_H

#include "Game.h"

class Player : public Entity {
public:
	Player();

public:
	sf::RectangleShape playerTexture;
	float deltaTime;
	sf::Vector2f position;
	int vitesse;

public:
	void initTextures();
	void handleInput(sf::Event& event);
	void update(float deltaTime, sf::Vector2f& position) override;
	void draw(sf::RenderWindow& window) override;
};

#endif