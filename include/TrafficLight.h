#pragma once
#include <SFML/Graphics.hpp>
#include "Waypoint.h"
#include "utils.h"


class TrafficLight
{
private:
	float x;
	float y;
	float dir;											// Same as road it belongs to
	tLightState state;
	sf::Texture redTexture;
	sf::Texture greenTexture;
	sf::Sprite sprite;
	TrafficLight* next;
	friend class TrafficLightGroup;						
	Waypoint* w;										// Waypoint binded to traffic light					
public:
	TrafficLight(float x, float y, float dir, tLightState state, Waypoint* w);
	void draw(sf::RenderWindow& window);
	tLightState getState();
	void setState(tLightState state);
};

