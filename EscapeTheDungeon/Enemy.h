#ifndef ENEMY_H
#define ENEMY_H

#include "Game.h"

namespace {
	int positionIndex = 0;
	std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
	sf::Vector2f patrollingPositions[5] = {
		{(float)fullscreenModes[0].width - 70, (float)fullscreenModes[0].height - 70},
		{(float)fullscreenModes[0].width - 70, 0},
		{0, (float)fullscreenModes[0].height - 70},
		{0, 0},
		// Center
		{(float)fullscreenModes[0].width / 2, (float)fullscreenModes[0].height / 2}
	};
}

class Enemy : public Entity {
protected:
	sf::RectangleShape enemyShape;
	std::string nom;
	int vie;
	int vitesse;
	bool gameOver = false;

public:
	Enemy(const std::string& nom, int vie, int vitesse)
		: nom(nom), vie(vie), vitesse(vitesse) {}

	
	std::vector<std::shared_ptr<Enemy>> enemies;

public:
	void initTextures();
	void update(float deltaTime, sf::Vector2f& position) override {};
	void draw(sf::RenderWindow& window) override;
	bool getGameOver();
};


class ChaserEnemy : public Enemy {
private: 
	sf::Vector2f position;
public:
	ChaserEnemy(const std::string& nom, int vie, double vitesse)
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
	void update(float deltaTime, sf::Vector2f& position) override;
};

class PatrollingEnemy : public Enemy {
private:
	sf::Vector2f position;
public:
	PatrollingEnemy(const std::string& nom, int vie, double vitesse)
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
	void update(float deltaTime, sf::Vector2f& position) override;
};

#endif