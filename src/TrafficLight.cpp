#include "TrafficLight.h"

// TODO: Determine location of light by using waypoint object given as parameter
TrafficLight::TrafficLight(float x, float y, float dir, tLightState state, Waypoint* w)
{
	std::cout << "Traffic Light object initialized" << std::endl;
	this->w = w;
	this->x = x;
	this->y = y;
	this->dir = dir;
	this->state = state;

	if (!this->redTexture.loadFromFile("./images/trafficlights/red.png"))
		std::cout << "Red Texture load unsuccessful" << std::endl;
	if (!this->greenTexture.loadFromFile("./images/trafficlights/green.png"))
		std::cout << "Green Texture load unsuccessful" << std::endl;

	// Lock or unlock waypoint according to light state.
	if (this->state == tLightState::green) {
		this->sprite.setTexture(this->greenTexture);
		this->w->setDrive(true);
	}
	else {
		this->sprite.setTexture(this->redTexture);
		this->w->setDrive(false);
	}

	this->next = NULL;
	
}

void TrafficLight::draw(sf::RenderWindow& window)
{
	this->sprite.setPosition(this->x, this->y);
	this->sprite.setRotation(this->dir);
	window.draw(this->sprite);
}

tLightState TrafficLight::getState()
{
	return this->state;
}

void TrafficLight::setState(tLightState state)
{
	this->state = state;
	if (this->state == tLightState::green) {
		this->sprite.setTexture(this->greenTexture);
		this->w->setDrive(true);
	}
	else {
		this->sprite.setTexture(this->redTexture);
		this->w->setDrive(false);
	}
}
