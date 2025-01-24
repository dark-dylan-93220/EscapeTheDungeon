#include "Game.h"
#include "Player.h"

namespace {
	std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
	sf::Texture playerTXTure;
}

Player::Player() :
	vitesse(250),
	position(fullscreenModes[0].width / 2, fullscreenModes[0].height / 2),
	deltaTime(0)
{
	initTextures();
	playerTexture.setSize(sf::Vector2f(40,40));
	playerTexture.setTexture(&playerTXTure);
	playerTexture.setPosition(sf::Vector2f(
		this->position.x - this->playerTexture.getSize().x / 2,
		this->position.y - this->playerTexture.getSize().y / 2
	));
}

void Player::initTextures() {
	playerTXTure.loadFromFile("Assets/Images/Player/frame0.png");
}

bool Player::win() {
	return winCase;
}

void Player::objectCollisions(const sf::RectangleShape& playerHitbox, sf::RectangleShape& key, sf::RectangleShape& speedPotion) {
	if (playerHitbox.getGlobalBounds().intersects(key.getGlobalBounds())) {
		isKeyCollected = true;
	}
	else if (playerHitbox.getGlobalBounds().intersects(speedPotion.getGlobalBounds())) {
		isPotionCollected = true;
	}

}

void Player::handleInput(const std::vector<sf::RectangleShape>& tilesContainer, const sf::RectangleShape& playerHitbox) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (position.y <= 30) return;
		playerTexture.move(0, -vitesse * this->deltaTime);
		for (auto& shape : tilesContainer) {
			if (shape.getGlobalBounds().intersects(playerHitbox.getGlobalBounds())) {
				playerTexture.move(0, vitesse * this->deltaTime);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (position.x <= 20) return;
		playerTexture.move(-vitesse * this->deltaTime, 0);
		for (auto& shape : tilesContainer) {
			if (shape.getGlobalBounds().intersects(playerHitbox.getGlobalBounds())) {
				playerTexture.move(vitesse * this->deltaTime, 0);
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (position.y >= (fullscreenModes[0].height - 40 - (fullscreenModes[0].height / 27.f))) {
			if (!isKeyCollected) return;
		};
		playerTexture.move(0, vitesse * this->deltaTime);
		for (auto& shape : tilesContainer) {
			if (shape.getGlobalBounds().intersects(playerHitbox.getGlobalBounds())) {
				playerTexture.move(0, -vitesse * this->deltaTime);
			}
		}
		if (position.y >= fullscreenModes[0].height) {
			winCase = true;
			return;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (position.x >= fullscreenModes[0].width - 60) return;
		playerTexture.move(vitesse * this->deltaTime, 0);
		for (auto& shape : tilesContainer) {
			if (shape.getGlobalBounds().intersects(playerHitbox.getGlobalBounds())) {
				playerTexture.move(-vitesse * this->deltaTime, 0);
			}
		}
	}
}

void Player::update(float deltaTime, sf::Vector2f& position, sf::RectangleShape& shape) {
	position = this->position;
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerTexture);
}