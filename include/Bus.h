#pragma once

#include "utils.h"
#include "SFML/Graphics.hpp"
#include "Vehicle.h"

class Bus : public Vehicle
{
private:
	std::vector<int> stops;										// Global indexes where bus will stop
	std::vector<int> route;										// Global indexes where bus will go through
	int stopPointer;											
	int routePointer;											// Pointer for route vector
public:
	Bus(int firstStop, City* c);
	std::vector<int> getStop();
	void setStop(std::vector<int>& route);
	void addPath(int index);									// Pushes to route vector
	void move(sf::RenderWindow& window);
	void printPath();											
};	

