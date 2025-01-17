#ifndef ENEMY_H
#define ENEMY_H

#include "Game.h"

class Enemy : public Entity {
protected:
	sf::RectangleShape enemyShape;
	std::string nom;
	int vie;
	double vitesse;

public:
	Enemy(const std::string& nom, int vie, double vitesse)
		: nom(nom), vie(vie), vitesse(vitesse) {}

	std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
	std::vector<std::shared_ptr<Enemy>> enemies;

public:
	void update(float deltaTime, sf::Vector2f &position) override {};
	void draw(sf::RenderWindow& window) override;
};


class ChaserEnemy : public Enemy {
private: 
	sf::Vector2f position;
public:
	ChaserEnemy(const std::string& nom, int vie, double vitesse)
		: Enemy(nom, vie, vitesse) {
		enemyShape.setSize(sf::Vector2f(70, 70));
		enemyShape.setFillColor(sf::Color::Red);
		enemyShape.setPosition(sf::Vector2f(
			rand() % fullscreenModes[0].width - enemyShape.getSize().x, 
			rand() % fullscreenModes[0].height - enemyShape.getSize().y
		));
		position = enemyShape.getPosition();
	}

public:
	void update(float deltaTime, sf::Vector2f &position) override;
};

class PatrollingEnemy : public Enemy {
public:
	PatrollingEnemy(const std::string& nom, int vie, double vitesse)
		: Enemy(nom, vie, vitesse) {
		enemyShape.setSize(sf::Vector2f(70, 70));
		enemyShape.setFillColor(sf::Color::Yellow);
		enemyShape.setPosition(sf::Vector2f(
			rand() % fullscreenModes[0].width - enemyShape.getSize().x, 
			rand() % fullscreenModes[0].height - enemyShape.getSize().y
		));
	}

public:
	void update(float deltaTime, sf::Vector2f &position) override;
};

#endif