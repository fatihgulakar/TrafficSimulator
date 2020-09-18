#pragma once
#include "Vehicle.h" 

class Car : public Vehicle
{
public:
	Car(tCarType t, int firstIndex, City* c);
	void move(sf::RenderWindow& window);
};

