#include "BusStop.h"

BusStop::BusStop(float x, float y, float dir)
{
	std::cout << "Bus Stop object initialized" << std::endl;
	this->x = x;
	this->y = y;
	this->dir = dir;
	if (!this->texture.loadFromFile("./images/busstop/busstop.png"))
		std::cout << "BusStop texture load unsuccessful" << std::endl;

	this->sprite.setTexture(this->texture);
}

void BusStop::getPosition(float& x, float& y, float& dir)
{
	x = this->x;
	y = this->y;
	dir = this->dir;
}

void BusStop::draw(sf::RenderWindow& window)
{
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setRotation(this->dir);
	window.draw(this->sprite);
}

void BusStop::setBusStatus(bool status)
{
	this->busStatus = status;
}

