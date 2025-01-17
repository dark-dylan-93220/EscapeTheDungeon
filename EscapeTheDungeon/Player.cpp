#include "Game.h"
#include "Player.h"

namespace {
	std::vector<sf::VideoMode> fullscreenModes = sf::VideoMode::getFullscreenModes();
}

Player::Player() :
	vitesse(0),
	position(fullscreenModes[0].width / 2, fullscreenModes[0].height / 2),
	deltaTime(0)
{
	playerTexture.setSize(sf::Vector2f(100,100));
	playerTexture.setFillColor(sf::Color::Blue);
	playerTexture.setPosition(sf::Vector2f(
		this->position.x - this->playerTexture.getSize().x / 2,
		this->position.y - this->playerTexture.getSize().y / 2
	));
}

void Player::handleInput(sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    playerTexture.move(0, -500 * this->deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  playerTexture.move(-500 * this->deltaTime, 0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  playerTexture.move(0, 500 * this->deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) playerTexture.move(500 * this->deltaTime, 0);
}

void Player::update(float deltaTime, sf::Vector2f &position) {
	position = this->position;
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(playerTexture);
}