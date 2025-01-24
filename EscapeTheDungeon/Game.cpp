#include <iostream>

#include "FileHandler.hpp"

#include "Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.hpp"

namespace {
	sf::RectangleShape tile;
	sf::Vector2f tilePosition;
	std::vector<sf::RectangleShape> tiles;
}

Game::Game() :
	window(sf::VideoMode(fullscreenModes.at(0)), "Escape The Dungeon", sf::Style::Fullscreen),
	isRunning(true),
	deltaTime(Clock.restart().asSeconds())
{
	window.setVerticalSyncEnabled(true);
}

void Game::mapCreation() { // 48x27 tileset
	int totalTiles = 0;
	tile.setSize(sf::Vector2f(fullscreenModes[0].width / 48.f, fullscreenModes[0].height / 27.f)); // 16/9th of the screen
	tiles.reserve(48 * 27);
	for (int i = 0; i < (48 * 27); ++i) {
		tiles.emplace_back(tile);
	}
	std::string content;
	Assets asset;
	FileHandler map = FileHandler("Assets/map.txt");
	for (int j = 0; j < 27; ++j) {
		content = map.read(); // Une ligne
		for (int i = 0; i < content.length(); ++i) {
			tilePosition = { (((float)i / 48.f) * fullscreenModes[0].width), (((float)j / 27.f) * fullscreenModes[0].height) };
			switch (content[i]) {
			case 'L':
				std::cout << "L";
				asset.setElementTexture("wallLeftFloor", tiles[totalTiles], tilePosition); // i-ème colonne, j-ème ligne
				break;
			case 'R':
				std::cout << "R";
				asset.setElementTexture("wallRightFloor", tiles[totalTiles], tilePosition);
				break;
			case 'l':
				std::cout << "l";
				asset.setElementTexture("wallRight", tiles[totalTiles], tilePosition);
				break;
			case 'r':
				std::cout << "r";
				asset.setElementTexture("wallLeft", tiles[totalTiles], tilePosition);
				break;
			case '-':
				std::cout << "-";
				asset.setElementTexture("floorTile", tiles[totalTiles], tilePosition);
				break;
			case 'T':
				std::cout << "T";
				asset.setElementTexture("wallTop", tiles[totalTiles], tilePosition);
				break;
			case 'B':
				std::cout << "B";
				asset.setElementTexture("wallBottom", tiles[totalTiles], tilePosition);
				break;
			case 'F':
				std::cout << "F";
				asset.setElementTexture("fullWall", tiles[totalTiles], tilePosition);
				break;
			case '/':
				std::cout << "/";
				asset.setElementTexture("wallTopLeft", tiles[totalTiles], tilePosition);
				break;
			case '\\':
				std::cout << "\\";
				asset.setElementTexture("wallTopRight", tiles[totalTiles], tilePosition);
				break;
			case '2':
				std::cout << "2";
				asset.setElementTexture("doorTopLeft", tiles[totalTiles], tilePosition);
				break;
			case '3':
				std::cout << "3";
				asset.setElementTexture("doorTopRight", tiles[totalTiles], tilePosition);
				break;
			case '4':
				std::cout << "4";
				asset.setElementTexture("doorBottomLeft", tiles[totalTiles], tilePosition);
				break;
			case '5':
				std::cout << "5";
				asset.setElementTexture("doorBottomRight", tiles[totalTiles], tilePosition);
				break;
			case '6':
				std::cout << "6";
				asset.setElementTexture("wallBottomLeft", tiles[totalTiles], tilePosition);
				break;
			case '9':
				std::cout << "9";
				asset.setElementTexture("wallBottomRight", tiles[totalTiles], tilePosition);
				break;
			default:
				break;
			}
			totalTiles++;
		}
		std::cout << std::endl;
	}
}

void Game::run() {

	Player player;
	Enemy enemy("", 0, 0); // Utilisé pour créer des ennemis de façon aléatoire
	int numberOfEnemies = 10;
	for (int i = 0; i < numberOfEnemies; ++i) {
		// Push back les ennemis crées
		if (i % 2 == 0) {
			enemy.enemies.push_back(std::make_shared<ChaserEnemy>("Chasseur", 50, 100)); // 50 vie / 100 vitesse
		}
		else {
			enemy.enemies.push_back(std::make_shared<PatrollingEnemy>("Patrouilleur", 100, 150)); // 100 vie, 150 vitesse
		}
	}

	std::cout << "Nombre d'ennemis : " << numberOfEnemies << std::endl;

	mapCreation();

	while (window.isOpen() && isRunning) {

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
			if (enemies->getGameOver()) {
				isRunning = false;
				window.close();
			}
		}

		window.clear(sf::Color(64,64,64));

		// Draw the background

		for (auto& element : tiles) {
			window.draw(element);
		}

		// Draw the enemies

		for (auto &enemies : enemy.enemies) {
			enemies->draw(window);
		}

		// Draw the objects



		// Draw the player

		player.draw(window);

		window.display();

	}
}