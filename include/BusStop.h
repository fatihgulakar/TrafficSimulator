#pragma once
#include "utils.h"
#include "SFML/Graphics.hpp"

class BusStop
{
private:
	float x;
	float y;
	float dir;
	sf::Texture texture;
	sf::Sprite sprite;
	bool busStatus;
public:
	BusStop(float x, float y, float dir);
	void getPosition(float& x, float& y, float& dir);
	void draw(sf::RenderWindow& window);
	void setBusStatus(bool status);
};

