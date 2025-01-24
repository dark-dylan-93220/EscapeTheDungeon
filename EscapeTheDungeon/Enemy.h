#ifndef ENEMY_H
#define ENEMY_H

#include "Game.h"

namespace {
	int positionIndex = 0;
	std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
	sf::Vector2f patrollingPositions[5] = {
		{47 * (float)fullscreenModes[0].width / 48.f, 2 * (float)fullscreenModes[0].height / 27.f},  // BOTTOM RIGHT
		{47 * (float)fullscreenModes[0].width / 48.f, 26 * (float)fullscreenModes[0].height / 27.f}, // TOP RIGHT
		{2 * (float)fullscreenModes[0].width / 48.f, 26 * (float)fullscreenModes[0].height / 27.f},	 // BOTTOM LEFT
		{2 * (float)fullscreenModes[0].width / 48.f, 2 * (float)fullscreenModes[0].height / 27.f},   // TOP LEFT
		// Center bottom
		{24 * (float)fullscreenModes[0].width / 48.f, 13.5f * (float)fullscreenModes[0].height / 27.f} // CENTER BOTTOM
	};
}

class Enemy : public Entity {
protected:
	std::string nom;
	int vie;
	int vitesse;
	bool gameOver = false;

public:
	Enemy(const std::string& nom, int vie, int vitesse)
		: nom(nom), vie(vie), vitesse(vitesse) {}

	sf::RectangleShape enemyShape;
	std::vector<std::shared_ptr<Enemy>> enemies;
	int lastMoveID = -1;

public:
	void initTextures();
	void update(float deltaTime, sf::Vector2f& position, sf::RectangleShape& shape) override {};
	void draw(sf::RenderWindow& window) override;
	bool getGameOver();
	void pathScrpting(const std::vector<int>& pathScript, int indexOfMovement);
	void checkWallCollisions(const std::vector<sf::RectangleShape>& tilesContainer, const sf::RectangleShape& enemyHitbox, float deltaTime);
};


class ChaserEnemy : public Enemy {
private: 
	sf::Vector2f position;
public:
	ChaserEnemy(const std::string& nom, int vie, int vitesse)
		: Enemy(nom, vie, vitesse) {
		enemyShape.setSize(sf::Vector2f(40, 40));
		enemyShape.setPosition(sf::Vector2f(
			rand() % fullscreenModes[0].width, 
			rand() % fullscreenModes[0].height
		));
		position = enemyShape.getPosition();
		if (position.x > fullscreenModes[0].width - enemyShape.getSize().x) {
			position.x -= enemyShape.getSize().x;
		}
		if (position.y > fullscreenModes[0].height - enemyShape.getSize().y) {
			position.y -= enemyShape.getSize().y;
		}
		initTextures();
		setTexture();
	}

public:
	void setTexture();
	void update(float deltaTime, sf::Vector2f& position, sf::RectangleShape& shape) override;
};

class PatrollingEnemy : public Enemy {
private:
	sf::Vector2f position;
public:
	PatrollingEnemy(const std::string& nom, int vie, int vitesse)
		: Enemy(nom, vie, vitesse) {
		enemyShape.setSize(sf::Vector2f(40, 40));
		enemyShape.setPosition(patrollingPositions[positionIndex]);
		positionIndex++;
		position = enemyShape.getPosition();
		if (position.x > fullscreenModes[0].width - enemyShape.getSize().x) {
			position.x -= enemyShape.getSize().x;
		}
		if (position.y < 0) {
			position.y += enemyShape.getSize().y;
		}
		initTextures();
		setTexture();
	}

public:
	void setTexture();
	void update(float deltaTime, sf::Vector2f& position, sf::RectangleShape& shape) override;
};

#endif