#include "TrafficLightGroup.h"

TrafficLightGroup::TrafficLightGroup(float duration)
{
	std::cout << "TrafficLight group object initialized" << std::endl;
	this->head = NULL;
	this->greenLight = NULL;
	this->duration = duration;
	this->time = 0.0f;
}
// Insertion to circular linked list;
void TrafficLightGroup::add(TrafficLight* light)
{
	// Empty list
	if (this->head == NULL) {				
		this->head = light;
		this->greenLight = light;
		light->next = light;
	}
	// Non-empty linked list
	else {									
		auto iter = head;
		while (iter->next != head)
			iter = iter->next;
		iter->next = light;
		light->next = head;
	}
}

void TrafficLightGroup::simulate(float timestep)
{
	this->time += timestep;
	// Time to switch lights 
	if (this->time >= this->duration) {					
		this->greenLight->setState(tLightState::red);
		this->greenLight = this->greenLight->next;
		this->greenLight->setState(tLightState::green);
		this->time = 0;
	}
}
