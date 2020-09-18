#include "Car.h"
#include "City.h"

Car::Car(tCarType t, int firstIndex, City* c) : Vehicle(firstIndex, c) {

	std::cout << "--> Derived Car object is initialized" << std::endl;

	// Loading the texture and setting it to the sprite based on type of vehicle.
	switch (t)
	{
	case tCarType::car1:
		if (!this->texture.loadFromFile("./images/vehicles/car1.png"))
			std::cout << "Invalid path" << std::endl;
		this->sprite.setTexture(this->texture);
		break;
	case tCarType::car2:
		if (!this->texture.loadFromFile("./images/vehicles/car2.png"))
			std::cout << "Invalid path" << std::endl;
		this->sprite.setTexture(this->texture);
		break;
	case tCarType::car3:
		if (!this->texture.loadFromFile("./images/vehicles/car3.png"))
			std::cout << "Invalid path" << std::endl;
		this->sprite.setTexture(this->texture);		
		break;
	case tCarType::car4:
		if (!this->texture.loadFromFile("./images/vehicles/car4.png"))
			std::cout << "Invalid path" << std::endl;
		this->sprite.setTexture(this->texture);		
		break;
	case tCarType::car5:
		if (!this->texture.loadFromFile("./images/vehicles/car5.png"))
			std::cout << "Invalid path" << std::endl;
		this->sprite.setTexture(this->texture);		
		break;
	case tCarType::car6:
		if (!this->texture.loadFromFile("./images/vehicles/car6.png"))
			std::cout << "Invalid path" << std::endl;
		this->sprite.setTexture(this->texture);		
		break;
	default:
		std::cout << "Invalid type of vehicle" << std::endl;
		break;
	}

	// After loading the texture, origin of sprite object is changed as center point of texture.
	this->sprite.setOrigin(sf::Vector2f(this->texture.getSize().x * 0.5f, this->texture.getSize().y * 0.5f));
}

void Car::move(sf::RenderWindow& window)
{
	// If red light is ahead, slow down
	if (this->city->checkDrive(this->current_index) == false){
		this->circular_velocity /= 2.0f;
		this->straight_velocity /= 1.25f;
	}
		
	// Arrived at destination, time to select new destination
	if (this->arrived_x && this->arrived_y) {
		if (this->city->checkDrive(this->current_index) == true) {

			// Choose random waypoint index until it is non-negative.
			auto nexts = this->city->giveNexts(current_index);
			if (nexts[1] == -1)
				current_index = nexts[0];

			else {
				int rand_index = 0;
				do {
					rand_index = rand() % 3;
					if (nexts[rand_index] >= 0) {
						current_index = nexts[rand_index];
						break;
					}
				} while (true);
			}

			this->city->getPosition(this->current_index, this->x_dest, this->y_dest, this->dir_dest);
			this->isStopped = false;
		}
		else
		{
			this->isStopped = true;
		}
	}

	// Below is completely same as Bus class.
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

