#include "Bus.h"
#include "City.h"

Bus::Bus(int firstStop, City* c) : Vehicle(firstStop, c)
{
	std::cout << "--> Derived Bus object is initialized" << std::endl;
	if (!this->texture.loadFromFile("./images/vehicles/bus.png"))
		std::cout << "Invalid path" << std::endl;
	this->sprite.setTexture(this->texture);

	this->sprite.setOrigin(sf::Vector2f(this->texture.getSize().x * 0.5f, this->texture.getSize().y * 0.5f));

	this->stopPointer = 0;
	this->routePointer = 0;
	//this->straight_velocity = 0.8f;
}

std::vector<int> Bus::getStop()
{
	return this->stops;
}

void Bus::setStop(std::vector<int>& route)
{
	this->stops = route;
}

void Bus::addPath(int index)
{
	this->route.push_back(index);
}

void Bus::move(sf::RenderWindow& window)
{
	// TODO: Add decelerate at bus stop functionality. Problem: Current index increases by two at bus stops.
	if (this->city->checkDrive(this->current_index) == false) {
		/*if (this->current_index == this->stops[this->stopPointer]) {
			if (this->stopPointer == this->stops.size() - 1)
				this->stopPointer = 0;
			else
				this->stopPointer++;
			this->straight_velocity /= 10.0f;
		}*/
		this->circular_velocity /= 2.0f;
		this->straight_velocity /= 1.25f;
	}

	if (this->arrived_x && this->arrived_y) {
		if (this->city->checkDrive(this->current_index) == true) {
			auto nexts = this->city->giveNexts(current_index);
			auto last_index = current_index;
			int dest = this->route[++routePointer];

			if (dest == last_index)
				routePointer--;

			current_index = dest;
			if (routePointer == this->route.size() - 1)
				routePointer = 0;

			this->city->getPosition(current_index, x_dest, y_dest, dir_dest);
			
			this->isStopped = false;
		}
		else
		{
			this->isStopped = true;
		}
	}

	// Below is completely same as Car class.
	if (this->isStopped == true) {					// true when car was waiting at red light, and it started to accelerate
		this->straight_velocity = 0.1f;
	}
	if (this->straight_velocity < MAX_SPEED)			// Increase speed until a maximum.
		this->straight_velocity += ACCELERATION;


	// Going straight
	if (this->angle == 90 * this->dir_dest) {
		this->circular_velocity = 1.0f;					// Reset circular velocity if car is going straight.
		this->turn_direction = this->angle;

		// Move horizontally
		if (std::abs(this->x - this->x_dest) > X_STEP) {
			this->arrived_x = false;
			this->x += this->straight_velocity * ((this->x < this->x_dest) ? 1 : -1);
		}
		else this->arrived_x = true;

		// Move vertically
		if (std::abs(this->y - this->y_dest) > Y_STEP) {
			this->arrived_y = false;
			this->y += this->straight_velocity * ((this->y < this->y_dest) ? 1 : -1);
		}
		else this->arrived_y = true;

		this->sprite.setPosition(this->x, this->y);
	}

	// Turning around corner
	else {
		// angle_temp is ANGLE_STEP lower(or higher) value of vehicle angle.
		float angle_temp = 0;
		this->arrived_x = false;
		this->arrived_y = false;

		// If vehicle is turning up to right.
		if (this->angle >= 270.0f && this->dir_dest == 0) {
			angle_temp = this->angle + ANGLE_STEP * this->circular_velocity;
			if (angle_temp >= 360.0f) {
				angle_temp -= 360.0f;
			}
		}
		// If turning right to up.
		else if (this->angle <= 0.0f && this->dir_dest == 3) {
			angle_temp = this->angle - ANGLE_STEP * this->circular_velocity;
			if (angle_temp < -90.0f) {
				angle_temp += 360.0f;
			}
		}
		else if (this->angle <= 270.0f && this->angle >= 0) {
			if (this->angle < 90 * this->dir_dest) {
				angle_temp = this->angle + ANGLE_STEP * this->circular_velocity;
			}
			else {
				angle_temp = this->angle - ANGLE_STEP * this->circular_velocity;
			}
		}

		// offsetX and offsetY displacement in X/Y directions for small angle difference dTheta.
		float offsetX = 0, offsetY = 0;

		// Cases in which car turns right
		// Turning right-do-down, down-to-left, left-to-up and up-to-right.
		if ((this->turn_direction == 0.0f && this->dir_dest == 1) || (this->turn_direction == 90.0f && this->dir_dest == 2) || (this->turn_direction == 270.0f && this->dir_dest == 0) || (this->turn_direction == 180.0f && this->dir_dest == 3)) {
			offsetX = RADIUS * (std::sin(angle_temp * PI / 180.0f) - std::sin(this->angle * PI / 180.0f));
			offsetY = RADIUS * (std::cos(this->angle * PI / 180.0f) - std::cos(angle_temp * PI / 180.0f));
		}
		// Cases in which car turns left
		// Turning right-to-up, up-to-left, left-to-down and down-to-right;
		else if ((this->turn_direction == 0.0f && this->dir_dest == 3) || (this->turn_direction == 90.0f && this->dir_dest == 0) || (this->turn_direction == 270.0f && this->dir_dest == 2) || (this->turn_direction == 180.0f && this->dir_dest == 1)) {
			offsetX = RADIUS * (std::sin(this->angle * PI / 180.0f) - std::sin(angle_temp * PI / 180.0f));
			offsetY = RADIUS * (std::cos(angle_temp * PI / 180.0f) - std::cos(this->angle * PI / 180.0f));
		}

		this->sprite.move(offsetX, offsetY);
		this->angle = angle_temp;
		this->x = this->sprite.getPosition().x;
		this->y = this->sprite.getPosition().y;
	}
	this->sprite.setRotation(this->angle);
	window.draw(this->sprite);

}

void Bus::printPath()
{
	if (this->route.empty())
		std::cout << "Empty route" << std::endl;
	for (auto x : this->route) {
		std::cout << x << " > ";
	}
	std::cout << std::endl;
}

