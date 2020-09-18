#pragma once
#include <SFML/Graphics.hpp>
#include "utils.h"

class Waypoint
{
private:
	float x;
	float y;
	int dir;
	int next1;
	int next2;
	int next3;
	sf::Texture texture;
	sf::Sprite sprite;
	bool canDrive;					// Determines if car on the waypoint can leave, according to TrafficLight's state.
public:
	Waypoint(tWaypointDir dir, tRoadTileType type, int row, int col, int idx, int next1 = -1, int next2 = -1, int next3 = -1);
	void getPosition(float& x, float& y, float& dir);
	void draw(sf::RenderWindow & window);
	bool getDrive();
	void setDrive(bool status);
	std::vector<int> get_next_indexes();
};



