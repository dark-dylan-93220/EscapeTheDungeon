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
	sf::Texture wallTopLeft;
	sf::Texture wallTopRight;
	sf::Texture wallBottomLeft;
	sf::Texture wallBottomRight;
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
		wallRight.loadFromFile("Assets/Images/Map/Walls/wall-left.png");
		wallLeft.loadFromFile("Assets/Images/Map/Walls/wall-right.png");
		wallTop.loadFromFile("Assets/Images/Map/Walls/wall-top.png");
		wallBottom.loadFromFile("Assets/Images/Map/Walls/wall-bottom.png");
		wallLeftFloor.loadFromFile("Assets/Images/Map/Walls/wall-left-floor.png");
		wallRightFloor.loadFromFile("Assets/Images/Map/Walls/wall-right-floor.png");
		wallTopLeft.loadFromFile("Assets/Images/Map/Walls/wall-top-left.png");
		wallTopRight.loadFromFile("Assets/Images/Map/Walls/wall-top-right.png");
		wallBottomLeft.loadFromFile("Assets/Images/Map/Walls/wall-bottom-left.png");
		wallBottomRight.loadFromFile("Assets/Images/Map/Walls/wall-bottom-right.png");
		fullWall.loadFromFile("Assets/Images/Map/Walls/full-wall.png");
		floorTile.loadFromFile("Assets/Images/Map/Floor/tile.png");
		speedPotion.loadFromFile("Assets/Images/Map/Floor/potion-floor.png");
		doorKey.loadFromFile("Assets/Images/Map/Floor/door-key.png");
		doorBottomLeft.loadFromFile("Assets/Images/Map/Door/door-bottom-left.png");
		doorBottomRight.loadFromFile("Assets/Images/Map/Door/door-bottom-right.png");
		doorTopLeft.loadFromFile("Assets/Images/Map/Door/door-top-left.png");
		doorTopRight.loadFromFile("Assets/Images/Map/Door/door-top-right.png");
	}
	void setElementTexture(const std::string& assetCode, sf::RectangleShape& element, sf::Vector2f position) {
		element.setPosition(position);
		if (assetCode == "wallLeft")
			element.setTexture(&wallLeft);
		else if (assetCode == "wallRight")
			element.setTexture(&wallRight);
		else if (assetCode == "wallTop")
			element.setTexture(&wallTop);
		else if (assetCode == "wallBottom")
			element.setTexture(&wallBottom);
		else if (assetCode == "fullWall")
			element.setTexture(&fullWall);
		else if (assetCode == "wallLeftFloor")
			element.setTexture(&wallLeftFloor);
		else if (assetCode == "wallRightFloor")
			element.setTexture(&wallRightFloor);
		else if (assetCode == "wallTopLeft")
			element.setTexture(&wallTopLeft);
		else if (assetCode == "wallTopRight")
			element.setTexture(&wallTopRight);
		else if (assetCode == "wallBottomLeft")
			element.setTexture(&wallBottomLeft);
		else if (assetCode == "wallBottomRight")
			element.setTexture(&wallBottomRight);
		else if (assetCode == "floorTile")
			element.setTexture(&floorTile);
		else if (assetCode == "speedPotion")
			element.setTexture(&speedPotion);
		else if (assetCode == "doorKey")
			element.setTexture(&doorKey);
		else if (assetCode == "doorTopLeft")
			element.setTexture(&doorTopLeft);
		else if (assetCode == "doorTopRight")
			element.setTexture(&doorTopRight);
		else if (assetCode == "doorBottomLeft")
			element.setTexture(&doorBottomLeft);
		else if (assetCode == "doorBottomRight")
			element.setTexture(&doorBottomRight);
		else {
			std::cerr << "Aucun code d'asset ne correspond a cette texture. (" << assetCode << ")\n";
		}
	}
};