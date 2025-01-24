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

void Enemy::pathScrpting(const std::vector<int>& pathScript, int indexOfMovement) {
	switch (pathScript[indexOfMovement]) {
	case 1: // UP
		this->enemyShape.move(0, -1 * ((float)fullscreenModes[0].height / 27.f));
		break;
	case 2: // DOWN
		this->enemyShape.move(0, 1 * ((float)fullscreenModes[0].height / 27.f));
		break;
	case 3: // LEFT
		this->enemyShape.move(-1 * ((float)fullscreenModes[0].width / 48.f), 0);
		break;
	case 4: // RIGHT
		this->enemyShape.move(1 * ((float)fullscreenModes[0].width / 48.f), 0);
		break;
	default:
		break;
	}
}

void ChaserEnemy::update(float deltaTime, sf::Vector2f& position, sf::RectangleShape& shape) {
	// position : Position du joueur
	// this->position : Position de l'ennemi en question
	this->position = enemyShape.getPosition();
	if (enemyShape.getGlobalBounds().intersects(shape.getGlobalBounds())) {
		// Game over
		gameOver = true;
		return;
	}
	if (position.x > this->position.x) {
		enemyShape.move(sf::Vector2f(vitesse * deltaTime, 0));
		this->lastMoveID = 0;
	}
	if (position.x < this->position.x) {
		enemyShape.move(-vitesse * deltaTime, 0);
		this->lastMoveID = 1;
	}
	if (position.y > this->position.y) {
		enemyShape.move(sf::Vector2f(0, vitesse * deltaTime));
		this->lastMoveID = 2;
	}
	if (position.y < this->position.y) {
		enemyShape.move(0, -vitesse * deltaTime);
		this->lastMoveID = 3;
	}
}

void Enemy::checkWallCollisions(const std::vector<sf::RectangleShape>& tilesContainer, const sf::RectangleShape& enemyHitbox, float deltaTime) {
	for(auto& wall : tilesContainer) {
		if (enemyHitbox.getGlobalBounds().intersects(wall.getGlobalBounds())) {
			switch(this->lastMoveID){
			case 0:
				this->enemyShape.move(sf::Vector2f(-vitesse * deltaTime, 0));
				break;
			case 1:
				this->enemyShape.move(vitesse * deltaTime, 0);
				break;
			case 2:
				this->enemyShape.move(sf::Vector2f(0, -vitesse * deltaTime));
				break;
			case 3: 
				this->enemyShape.move(0, vitesse * deltaTime);
				break;
			default:
				break;
			}
		}
	}
}

void PatrollingEnemy::update(float deltaTime, sf::Vector2f& position, sf::RectangleShape& shape) {
	// Chemin programmé, random dans une liste de chmins programmés
	if (enemyShape.getGlobalBounds().intersects(shape.getGlobalBounds())) {
		// Game over
		gameOver = true;
		return;
	}
	return;
}