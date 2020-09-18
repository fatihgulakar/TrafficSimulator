#pragma once
#include "TrafficLight.h"

class TrafficLightGroup
{
// It is a simple circular linked list that holds TrafficLight objects
private:
	TrafficLight* head;
	TrafficLight* greenLight;
	float time;
	float duration;
public:
	TrafficLightGroup(float duration);
	void add(TrafficLight* light);
	void simulate(float timestep);
};

