#include "SFML/Graphics.hpp"
#include <iostream>

namespace {
	sf::Texture wallLeft;
	sf::Texture wallRight;
	sf::Texture wallTop;
	sf::Texture wallBottom;
	sf::Texture fullWall;
	sf::Texture wallLeftFloor;
	sf::Texture wallRightFloor;
	sf::Texture floorTile;
	sf::Texture speedPotion;
	sf::Texture doorKey;
	sf::Texture doorTopLeft;
	sf::Texture doorTopRight;
	sf::Texture doorBottomLeft;
	sf::Texture doorBottomRight;
}

class Assets {
public:
	Assets() {
		wallLeft.loadFromFile("Assets/Images/Map/Walls/wall-left.png");
		wallRight.loadFromFile("Assets/Images/Map/Walls/wall-right.png");
		wallTop.loadFromFile("Assets/Images/Map/Walls/wall-top.png");
		wallBottom.loadFromFile("Assets/Images/Map/Walls/wall-bottom.png");
		wallLeftFloor.loadFromFile("Assets/Images/Map/Walls/wall-left-floor.png");
		wallRightFloor.loadFromFile("Assets/Images/Map/Walls/wall-right-floor.png");
		fullWall.loadFromFile("Assets/Images/Map/Walls/full-wall.png");
		floorTile.loadFromFile("Assets/Images/Map/Floor/tile.png");
		speedPotion.loadFromFile("Assets/Images/Map/Floor/potion-floor.png");
		doorKey.loadFromFile("Assets/Images/Map/Floor/door-key.png");
		doorBottomLeft.loadFromFile("Assets/Images/Map/Door/door-bottom-left.png");
		doorBottomRight.loadFromFile("Assets/Images/Map/Door/door-bottom-right.png");
		doorTopLeft.loadFromFile("Assets/Images/Map/Door/door-top-left.png");
		doorTopRight.loadFromFile("Assets/Images/Map/Door/door-top-right.png");
	}
	void setElementTexture(const std::string& assetCode, sf::RectangleShape& element) {
		if (assetCode == "wallLeft")
			element.setTexture(&wallLeft);
		else if (assetCode == "wallRight")
			return;
		else if (assetCode == "wallTop")
			return;
		else if (assetCode == "wallBottom")
			return;
		else if (assetCode == "fullWall")
			return;
		else if (assetCode == "wallLeftFloor")
			return;
		else if (assetCode == "wallRightFloor")
			return;
		else if (assetCode == "floorTile")
			return;
		else if (assetCode == "speedPotion")
			return;
		else if (assetCode == "doorKey")
			return;
		else if (assetCode == "doorTopLeft")
			return;
		else if (assetCode == "doorTopRight")
			return;
		else if (assetCode == "doorBottomLeft")
			return;
		else if (assetCode == "doorBottomRight")
			return;
		else {
			std::cerr << "Aucun code d'asset ne correspond a cette texture. (" << assetCode << ")\n";
		}
	}
};