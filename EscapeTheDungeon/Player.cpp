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

void Player::handleInput(sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (position.y <= 0) return;
		playerTexture.move(0, -vitesse * this->deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (position.x <= 0) return;
		playerTexture.move(-vitesse * this->deltaTime, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (position.y >= fullscreenModes[0].height - 100) return;
		playerTexture.move(0, vitesse * this->deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (position.x >= fullscreenModes[0].width - 100) return;
		playerTexture.move(vitesse * this->deltaTime, 0);
	}
}

void Player::update(float deltaTime, sf::Vector2f& position) {
	position = this->position;
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerTexture);
}