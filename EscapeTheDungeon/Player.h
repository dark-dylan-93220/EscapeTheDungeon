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
	bool isKeyCollected = false;
	bool isPotionCollected = false;

private:
	bool winCase = false;

public:
	void initTextures();
	void handleInput(const std::vector<sf::RectangleShape>& tilesContainer, const sf::RectangleShape& playerHitbox);
	void objectCollisions(const sf::RectangleShape& playerHitbox, sf::RectangleShape& key, sf::RectangleShape& speedPotion);
	void update(float deltaTime, sf::Vector2f& position, sf::RectangleShape& shape) override;
	void draw(sf::RenderWindow& window) override;
	bool win();
	
};

#endif