#pragma once
#ifndef H_VEHICLE
#define H_VEHICLE



#include <SFML/Graphics.hpp>
#include "utils.h"
#include "Waypoint.h"
//#include "City.h"

class City;
class Vehicle
{
protected:
	float x;						// X coordinate of vehicle
	float y;						// Y coordinate of vehicle 
	float angle;					// Angle of vehicle
	bool arrived_x, arrived_y;		// Variables keeping if vehicle is arrived at next waypoint
	bool isStopped;
	float straight_velocity;		// Velocity of car
	float circular_velocity;		// Circular velocity of the car;
	float turn_direction;			// Angle of vehicle before last turn point
	float x_dest;					// X coordinate of destination
	float y_dest;					// Y coordinate of destination
	float dir_dest;					// Angle of coordinate
	int current_index;				// Current global index of the car
	sf::Texture texture;			// Texture of vehicle object
	sf::Sprite sprite;				// Sprite of vehicle object
	City* city;						// Pointer to city object
public:
	Vehicle(int firstIndex, City* c);
	virtual void move(sf::RenderWindow& window) = 0;
	void detectCollision(Vehicle* car);
};

#endif // !H_VEHICLE