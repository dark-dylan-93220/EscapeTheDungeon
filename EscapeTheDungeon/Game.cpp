#include <iostream>

#include "FileHandler.hpp"
#include "Assets.hpp"

#include "Game.h"
#include "Player.h"
#include "Enemy.h"


namespace {
	sf::RectangleShape tile;
	sf::Vector2f tilePosition;
	std::vector<sf::RectangleShape> tiles;
	std::vector<sf::RectangleShape> onlyWalls;
	sf::RectangleShape key;
	sf::RectangleShape speedPotionRect;
	std::vector<int> patrollerTopRightRoutine = {
		2,
		3,3,3,3,3,3,3,
		1,
		4,4,4,4,4,4,4
	}; 
	std::vector<int> patrollerTopLeftRoutine = {
		2,2,2,2,
		4,4,4,4,
		1,1,1,1,
		3,3,3,3
	}; 
	std::vector<int> patrollerBottomRightRoutine = {
		1,1,1,1,1,
		4,4,4,
		2,2,2,2,2,
		3,3,3
	}; 
	std::vector<int> patrollerBottomLeftRoutine = {
		1,1,1,1,1,
		3,3,3,
		4,4,4,
		2,2,2,2,2
	};
	std::vector<int> patrollerCenterBottomRoutine = {
		4,4,4,4,4,4,4,4,
		3,3,3,3,3,3,3,3
	};
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
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case 'R':
				std::cout << "R";
				asset.setElementTexture("wallRightFloor", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case 'l':
				std::cout << "l";
				asset.setElementTexture("wallRight", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case 'r':
				std::cout << "r";
				asset.setElementTexture("wallLeft", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case '-':
				std::cout << "-";
				asset.setElementTexture("floorTile", tiles[totalTiles], tilePosition);
				break;
			case 'T':
				std::cout << "T";
				asset.setElementTexture("wallTop", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case 'B':
				std::cout << "B";
				asset.setElementTexture("wallBottom", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case 'F':
				std::cout << "F";
				asset.setElementTexture("fullWall", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case '/':
				std::cout << "/";
				asset.setElementTexture("wallTopLeft", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case '\\':
				std::cout << "\\";
				asset.setElementTexture("wallTopRight", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
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
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			case '9':
				std::cout << "9";
				asset.setElementTexture("wallBottomRight", tiles[totalTiles], tilePosition);
				onlyWalls.push_back(tiles[totalTiles]);
				break;
			default:
				break;
			}
			totalTiles++;
		}
		std::cout << std::endl;
	}

	// Key and speed potion
	// ---
	// Key :
	key.setSize(tile.getSize());
	key.setPosition(((45.f / 48.f) * fullscreenModes[0].width), ((6.f / 27.f) * fullscreenModes[0].height));
	asset.setElementTexture("doorKey", key, key.getPosition());
	// Speed potion :
	speedPotionRect.setSize(tile.getSize());
	speedPotionRect.setPosition((((float)(rand() % 48) / 48.f)* fullscreenModes[0].width), (((float)(rand() % 27) / 27.f)* fullscreenModes[0].height));
	asset.setElementTexture("speedPotion", speedPotionRect, speedPotionRect.getPosition());
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

	int patrollingEnemiesRoutineStep = 0;
	int declencher = 0;

	sf::Font EightBitDragon;
	if (!EightBitDragon.loadFromFile("Assets/Fonts/8bitDragon.ttf")) {
		std::cerr << "Police 8-bit dragon non chargee." << std::endl;
	}
	sf::Text winTXT;
	winTXT.setString("YOU WIN!");
	winTXT.setFont(EightBitDragon);
	winTXT.setFillColor(sf::Color::Yellow);
	winTXT.setOutlineColor(sf::Color::Black);
	winTXT.setOutlineThickness(2.f);
	winTXT.setCharacterSize(90);
	winTXT.setPosition(sf::Vector2f(fullscreenModes[0].width / 2.f - winTXT.getLocalBounds().width / 2.f, fullscreenModes[0].height / 2.f - winTXT.getLocalBounds().height / 2.f));
	sf::Text gameOverTXT;
	gameOverTXT.setString("GAME OVER");
	gameOverTXT.setFont(EightBitDragon);
	gameOverTXT.setFillColor(sf::Color::Red);
	gameOverTXT.setOutlineColor(sf::Color::Black);
	gameOverTXT.setOutlineThickness(2.f);
	gameOverTXT.setCharacterSize(90);
	gameOverTXT.setPosition(sf::Vector2f(fullscreenModes[0].width / 2.f - gameOverTXT.getLocalBounds().width / 2.f, fullscreenModes[0].height / 2.f - gameOverTXT.getLocalBounds().height / 2.f));

	mapCreation();

	while (window.isOpen()) {

		deltaTime = Clock.restart().asSeconds();

		player.deltaTime = deltaTime;

		// Polling the events

		player.handleInput(onlyWalls, player.playerTexture);

		if (player.win()) {
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.clear();
				window.draw(winTXT);
				window.display();
			}
			window.close();
			break;
		}
		else if (isGameOver) {
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.clear();
				window.draw(gameOverTXT);
				window.display();
			}
			window.close();
			break;
		}

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			{
				window.close();
				std::cout << "Programme termine" << std::endl;
				return;
			}
		}

		// Updating the enemies' behavior and the player's position

		player.update(deltaTime, player.position, player.playerTexture);
		player.position = player.playerTexture.getPosition();
		int check = 0;
		for (auto& enemies : enemy.enemies) {
			if (check % 2 != 0) { // Patrolling enemy
				switch (check) {
				case 1:
					enemies->pathScrpting(patrollerBottomRightRoutine, patrollingEnemiesRoutineStep);
					break;
				case 3:
					enemies->pathScrpting(patrollerTopRightRoutine, patrollingEnemiesRoutineStep);
					break;
				case 5:
					enemies->pathScrpting(patrollerBottomLeftRoutine, patrollingEnemiesRoutineStep);
					break;
				case 7:
					enemies->pathScrpting(patrollerTopLeftRoutine, patrollingEnemiesRoutineStep);
					break;
				case 9:
					enemies->pathScrpting(patrollerCenterBottomRoutine, patrollingEnemiesRoutineStep);
					break;
				default:
					break;
				}
				if (patrollingEnemiesRoutineStep == 15) {
					patrollingEnemiesRoutineStep = 0;
				}
			}
			enemies->checkWallCollisions(onlyWalls, enemies->enemyShape, deltaTime);
			enemies->update(deltaTime, player.position, player.playerTexture);
			if (enemies->getGameOver()) {
				isGameOver = true;
			}
			check++;
		}

		patrollingEnemiesRoutineStep++;
		declencher++;

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

		player.objectCollisions(player.playerTexture, key, speedPotionRect);

		if (player.isKeyCollected) {
			key.setPosition(player.position.x - key.getSize().x / 2.f, player.position.y - key.getSize().y / 2.f);
		}
		if (!player.isPotionCollected) {
			window.draw(speedPotionRect);
		}
		else {
			player.playerTexture.setFillColor(sf::Color(216, 174, 255));
			player.vitesse = 400;
		}

		window.draw(key);

		// Draw the player

		player.draw(window);

		window.display();

	}

}