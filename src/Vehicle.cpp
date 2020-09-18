#include "Vehicle.h"
#include "City.h"

Vehicle::Vehicle(int firstIndex, City* c)
{
	std::cout << "Base Vehicle object is initialized" << std::endl;
	this->city = c;
	this->city->getPosition(firstIndex, this->x, this->y, this->angle);
	this->angle *= 90;
	this->arrived_x = true;				// arrived_x and arrived_y are true at first, since when we initialize them at main.cpp,
	this->arrived_y = true;				// we give the first initial global index of waypoint.
	this->turn_direction = 90*angle;	// Initial turn direction is same as initial angle of vehicle
	this->straight_velocity = 1.0f;
	this->circular_velocity = 1.0f;
	this->isStopped = false;
	this->x_dest = this->x;
	this->y_dest = this->y;
	this->dir_dest = this->angle;
	this->current_index = firstIndex;
}
// Checks two car collide with each other
void Vehicle::detectCollision(Vehicle* car)
{
	// carA and carB are collision boxes bigger than cars' sprites. So cars can slow down withoit colliding actually.
	auto carA = this->sprite;
	carA.setScale(COLLISION_SCALE, COLLISION_SCALE);
	auto carB = car->sprite;
	carB.setScale(COLLISION_SCALE, COLLISION_SCALE);


	if (carA.getGlobalBounds().intersects(carB.getGlobalBounds())) {
		// Detected collision, now determine which car to stop.
		
		// True if current object is behind the passed object.
		if ((this->angle <= 45.0f || this->angle > 315.0f && this->x < car->x) ||
			(this->angle <= 225.0f && this->angle > 135.0f && this->x > car->x) ||
			(this->angle <= 135.0f && this->angle > 45.0f && this->y < car->y) ||
			(this->angle <= 315.0f && this->angle > 225.0f && this->y > car->y)) {

			// If cars are going in straight way.
			if (std::fmod(this->angle, 90.0f) == 0.0f || std::fmod(car->angle, 90.0f) == 0.0f) {
				if (this->straight_velocity >= MIN_SPEED)
					this->straight_velocity -= ACCELERATION * 3.0f;
				else
					this->straight_velocity = 0;

			}
			// If cars are turning around corner
			else {
				if (this->circular_velocity >= 0.125f)
					this->circular_velocity /= 2.0f;
			}
		}
		// Car passed as parameter is behind.
		else if ((this->angle <= 45.0f || this->angle > 315.0f && this->x > car->x) ||
				(this->angle <= 225.0f && this->angle > 135.0f && this->x < car->x) ||
				(this->angle <= 135.0f && this->angle > 45.0f && this->y > car->y) ||
				(this->angle <= 315.0f && this->angle > 225.0f && this->y < car->y)) {

			 if (std::fmod(this->angle, 90.0f) == 0.0f || std::fmod(car->angle, 90.0f) == 0.0f) {
				 if (car->straight_velocity >= MIN_SPEED)
					 car->straight_velocity -= ACCELERATION * 3.0f;
			 	 else
					 car->straight_velocity = 0;
			 }
			 else {
				 if (car->circular_velocity >= 0.125f)
					 car->circular_velocity /= 2.0f;
			 }
		}
	}
	// No collision, reset the circular velocity
	else {
		if(this->circular_velocity <= 0.5f)
			this->circular_velocity *= 2.0f;
		if (car->circular_velocity <= 0.5f)
			car->circular_velocity *= 2.0f;
	}
}



