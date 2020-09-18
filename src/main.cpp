#include "City.h"
#include "Car.h"
#include "Bus.h"
using namespace std;

int main() {

	// Setting windows
	sf::RenderWindow window(sf::VideoMode(1600, 1200), "Traffic Simulator", sf::Style::Close | sf::Style::Resize);
	window.setFramerateLimit(FRAMES_PER_SEC);
	sf::Clock deltaClock;
	sf::View view;
	view.reset(sf::FloatRect(0, 0, 1600, 1200));
	view.setViewport(sf::FloatRect(0, 0, 0.8f, 0.8f));
	window.setView(view);
	

	City city;

	Car car1(tCarType::car1, 0, &city);			// Waypoint 0
	Car car2(tCarType::car2, 25, &city);		// Waypoint 25
	Car car3(tCarType::car3, 17, &city);		// Waypoint 17
	Car car4(tCarType::car4, 36, &city);		// Waypoint 36
	Car car5(tCarType::car5, 21, &city);		// Waypoint 40
	Car car6(tCarType::car6, 16, &city);		// Waypoint 16

	Bus bus1(2, &city);
	Bus bus2(6, &city);

	// List of vehicles to move
	city.vehicles = { &car1, &car2, &car3, &car4, &car5, &car6, &bus1, &bus2 };									// Vector of vehicle objects

	// List of stops
	std::vector<int> busStops1 = { 2, 6, 30, 35, 21, 14 };
	std::vector<int> busStops2 = { 6, 30, 46, 35, 15 };

	// Assign the vector above to bus objects
	bus1.setStop(busStops1);
	bus2.setStop(busStops2);

	// Finds shortest path that goes each stop.
	city.findShortestPath(&bus1);
	city.findShortestPath(&bus2);

	std::cout << "-------Route of the first bus (The one with bigger route)------" << std::endl;
	bus1.printPath();

	std::cout << "-------Route of the second bus (Smaller route)------" << std::endl;
	bus2.printPath();

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Escape)
					window.close();
			}
		}

		window.clear(sf::Color::White);

		city.draw(window);

		// Advance time and change state of all traffic lights
		city.simulateAllLights(deltaClock);						

		// Move all in vehicles in city's vehicle vector
		city.moveAllVehicles(window);					

		// Check if there is any collision between collisions, and do something if that's the case
		city.checkAllCollision();																			
		
		window.display();
	}

	return 0;
}
