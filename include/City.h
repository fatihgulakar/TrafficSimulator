#pragma once
#ifndef H_CITY
#define H_CITY

#include "RoadTile.h"
#include "Waypoint.h"
#include "TrafficLight.h"
#include "TrafficLightGroup.h"
#include "Vehicle.h"
#include "Bus.h"
#include "BusStop.h"

class City
{
private:
	std::vector<std::vector<int>> adjList;
	std::vector<RoadTile*>r = std::vector<RoadTile*>(21);						// Roads
	std::vector<Waypoint*>w = std::vector<Waypoint*>(48);						// Waypoints
	std::vector<TrafficLight*>t = std::vector<TrafficLight*>(6);				// Traffic Lights
	std::vector<TrafficLightGroup*>tg = std::vector<TrafficLightGroup*>(3);		// Traffic Light Groups
	std::vector<BusStop*> bs = std::vector<BusStop*>(8);						// Bus stops
	
	sf::Time city_time;															// Global time of city
	bool bfs(int start, int end, int pred[], int dist[]);
public:
	City();
	void getPosition(int current_next, float& x, float& y, float& dir);			
	void draw(sf::RenderWindow& window);
	bool checkDrive(int index);																							
	void checkAllCollision();													
	void simulateAllLights(sf::Clock& clk);														
	void moveAllVehicles(sf::RenderWindow& window);									
	void findShortestPath(Bus* b);												
	std::vector<int> giveNexts(int index);
	std::vector<Vehicle*> vehicles;
};

#endif // !H_CITY