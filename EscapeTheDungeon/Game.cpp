#include <iostream>

#include "FileHandler.hpp"

#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.hpp"

namespace {
	sf::RectangleShape wall_Left;
	sf::RectangleShape wall_Right;
	sf::RectangleShape wall_Top;
	sf::RectangleShape wall_Bottom;
	sf::RectangleShape full_Wall;
	sf::RectangleShape wall_Left_Floor;
	sf::RectangleShape wall_Right_Floor;
	sf::RectangleShape floor_Tile;
	sf::RectangleShape speed_Potion;
	sf::RectangleShape door_Key;
	sf::RectangleShape door_Top_Left;
	sf::RectangleShape door_Top_Right;
	sf::RectangleShape door_Bottom_Left;
	sf::RectangleShape door_Bottom_Right;
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

Game::Game() :
	window(sf::VideoMode(fullscreenModes.at(0)), "Escape The Dungeon", sf::Style::Fullscreen),
	isRunning(true),
	deltaTime(Clock.restart().asSeconds())
{
	window.setVerticalSyncEnabled(true);
}

void Game::mapCreation() {
	wall_Right.setSize(sf::Vector2f(fullscreenModes[0].width / 16.f, fullscreenModes[0].height / 9.f)); // 16/9th of the screen
	wall_Right.setPosition(sf::Vector2f(0, 0));
	std::string content;
	Assets asset;
	FileHandler map = FileHandler("Assets/map.txt");
	while (content != "STOP") {
		content = map.read();
		const char* toChar = content.c_str();
		switch (str2int(toChar)) {
		case str2int("wall-right"):
			std::cout << "RIGHT" << '\n';
			asset.setElementTexture("wallLeft", wall_Right);
			break;
		case str2int("wall-left"):
			std::cout << "LEFT" << '\n';
			break;
		default:
			break;
		}
	}
}

void Game::run() {

	Player player;
	Enemy enemy("", 0, 0); // Utilisé pour créer des ennemis de façon aléatoire
	int numberOfEnemies = 8;
	for (int i = 0; i < numberOfEnemies; ++i) {
		// Push back les ennemis crées
		if (i % 2 == 0) {
			enemy.enemies.push_back(std::make_shared<ChaserEnemy>("Chasseur", 50, 200)); // 50 vie / 200 vitesse
		}
		else {
			enemy.enemies.push_back(std::make_shared<PatrollingEnemy>("Patrouilleur", 100, 150)); // 100 vie, 150 vitesse
		}
	}

	std::cout << "Nombre d'ennemis : " << numberOfEnemies << std::endl;

	mapCreation();

	while (window.isOpen()) {

		deltaTime = Clock.restart().asSeconds();
		player.deltaTime = deltaTime;

		// Polling the events

		player.handleInput(event);

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
				std::cout << "Programme termine" << std::endl;
			}
		}

		// Updating the enemies' behavior and the player's position

		player.update(deltaTime, player.position);
		player.position = player.playerTexture.getPosition();
		for (auto& enemies : enemy.enemies) {
			enemies->update(deltaTime, player.position);
		}

		window.clear(sf::Color(64,64,64));

		// Draw the background



		// Draw the enemies

		for (auto &enemies : enemy.enemies) {
			enemies->draw(window);
		}

		// Draw the objects



		// Draw the player

		player.draw(window);

		window.draw(wall_Right);

		window.display();

	}
}