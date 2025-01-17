#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Enemy.h"


Game::Game() :
	window(sf::VideoMode(fullscreenModes.at(0)), "Escape The Dungeon", sf::Style::Fullscreen),
	isRunning(true),
	deltaTime(Clock.restart().asSeconds())
{
	window.setVerticalSyncEnabled(true);
}

void Game::run() {

	Player player;
	Enemy enemy("", 0, 0); // Utilisé pour créer des ennemis de façon aléatoire
	int numberOfEnemies = rand() % 10 + 2; // Au minimum 2 ennemis (max 11)

	for (int i = 0; i < numberOfEnemies; ++i) {
		// Push back les ennemis crées
		int enemyType = rand() % 2;
		if (enemyType == 0) {
			enemy.enemies.push_back(std::make_shared<ChaserEnemy>("Chasseur", 50, 200));
		}
		else {
			enemy.enemies.push_back(std::make_shared<PatrollingEnemy>("Patrouilleur", 100, 150));
		}
	}

	std::cout << "Nombre d'ennemis : " << numberOfEnemies << std::endl;

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

		// Drawing the elements on the screen

		window.clear();
		for (auto &enemies : enemy.enemies) {
			enemies->draw(window);
		}
		player.draw(window);
		window.display();

	}
}