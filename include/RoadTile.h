#pragma once
#include <SFML/Graphics.hpp>
#include "utils.h"

class RoadTile
{
private:
	float x;
	float y;
	sf::Texture texture;
	sf::Sprite sprite;
public:
	RoadTile(tRoadTileType t, int row, int col);
	void draw(sf::RenderWindow& window);
};

