#include "Enemy.h"
#include "Player.h"
#include "Game.h"

namespace {
	sf::Texture chaserEnemyTXTure;
	sf::Texture patrollingEnemyTXTure;
}

void Enemy::initTextures() {
	chaserEnemyTXTure.loadFromFile("Assets/Images/Enemies/ChaserEnemy/frame0.png");
	patrollingEnemyTXTure.loadFromFile("Assets/Images/Enemies/PatrollingEnemy/frame0.png");
}

void Enemy::draw(sf::RenderWindow& window) {
	window.draw(enemyShape);
}

bool Enemy::getGameOver() {
	return gameOver;
}

void ChaserEnemy::setTexture() {
	enemyShape.setTexture(&chaserEnemyTXTure);
}

void PatrollingEnemy::setTexture() {
	enemyShape.setTexture(&patrollingEnemyTXTure);
}

void ChaserEnemy::update(float deltaTime, sf::Vector2f& position) {
	// position : Position du joueur
	// this->position : Position de l'ennemi en question
	this->position = enemyShape.getPosition();
	if (enemyShape.getGlobalBounds().contains(position)) {
		// Game over
		gameOver = true;
		return;
	}
	if (position.x > this->position.x) {
		enemyShape.move(sf::Vector2f(vitesse * deltaTime, 0));
	}
	if (position.x < this->position.x) {
		enemyShape.move(-vitesse * deltaTime, 0);
	}
	if (position.y > this->position.y) {
		enemyShape.move(sf::Vector2f(0, vitesse * deltaTime));
	}
	if (position.y < this->position.y) {
		enemyShape.move(0, -vitesse * deltaTime);
	}
}

void PatrollingEnemy::update(float deltaTime, sf::Vector2f& position) {
	// Chemin programmé, random dans une liste de chmins programmés
	if (enemyShape.getGlobalBounds().contains(position)) {
		// Game over
		gameOver = true;
		return;
	}
	return;
}