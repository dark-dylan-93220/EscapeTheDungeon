#include "Enemy.h"
#include "Game.h"

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(enemyShape);
}

void ChaserEnemy::update(float deltaTime, sf::Vector2f &position) {
	// position : Position du joueur
	// this->position : Position de l'ennemi en question
	this->position = enemyShape.getPosition();
	if (position.x > this->position.x) {
		enemyShape.move(sf::Vector2f(300 * deltaTime, 0));
	}
	if (position.x < this->position.x) {
		enemyShape.move(-300 * deltaTime, 0);
	}
	if (position.y > this->position.y) {
		enemyShape.move(sf::Vector2f(0, 300 * deltaTime));
	}
	if (position.y < this->position.y) {
		enemyShape.move(0, -300 * deltaTime);
	}
}

void PatrollingEnemy::update(float deltaTime, sf::Vector2f &position) {
	// Chemin programmé, random dans une liste de chmins programmés
	return;
}