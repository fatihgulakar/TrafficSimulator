#include "City.h"

bool City::bfs(int start, int end, int pred[], int dist[])
{
	// Helper function for finding shortest path between to waypoint
	std::list<int> queue;
	bool visited[48];
	for (int i = 0; i < 48; i++) {
		visited[i] = false;
		dist[i] = INT_MAX;
		pred[i] = -1;
	}

	visited[start] = true;
	dist[start] = 0;
	queue.push_back(start);


	while (!queue.empty()) {
		int node = queue.front();
		queue.pop_front();

		for (auto i = 0; i < this->adjList[node].size(); i++) {
			if (visited[this->adjList[node][i]] == false) {
				visited[this->adjList[node][i]] = true;
				dist[this->adjList[node][i]] = dist[node] + 1;
				pred[this->adjList[node][i]] = node;
				queue.push_back(this->adjList[node][i]);

				if (this->adjList[node][i] == end)
					return true;
			}
		}
	}

	return false;
	
}

City::City()
{
	std::cout << "City object is initialized" << std::endl;
	// First Row
	this->r[0] = new RoadTile(tRoadTileType::corner_topleft, 0, 0);
	this->r[1] = new RoadTile(tRoadTileType::straight_horizontal, 0, 1);
	this->r[2] = new RoadTile(tRoadTileType::t_top, 0, 2);
	this->r[3] = new RoadTile(tRoadTileType::straight_horizontal, 0, 3);
	this->r[4] = new RoadTile(tRoadTileType::corner_topright, 0, 4);

	// Second Row
	this->r[5] = new RoadTile(tRoadTileType::straight_vertical, 1, 0);
	this->r[6] = new RoadTile(tRoadTileType::straight_vertical, 1, 2);
	this->r[7] = new RoadTile(tRoadTileType::straight_vertical, 1, 4);

	// Third Row
	this->r[8] = new RoadTile(tRoadTileType::t_left, 2, 0);
	this->r[9] = new RoadTile(tRoadTileType::straight_horizontal, 2, 1);
	this->r[10] = new RoadTile(tRoadTileType::cross, 2, 2);
	this->r[11] = new RoadTile(tRoadTileType::straight_horizontal, 2, 3);
	this->r[12] = new RoadTile(tRoadTileType::t_right, 2, 4);

	// Fourth Row
	this->r[13] = new RoadTile(tRoadTileType::straight_vertical, 3, 0);
	this->r[14] = new RoadTile(tRoadTileType::straight_vertical, 3, 2);
	this->r[15] = new RoadTile(tRoadTileType::straight_vertical, 3, 4);

	// Fifth Row
	this->r[16] = new RoadTile(tRoadTileType::corner_bottomleft, 4, 0);
	this->r[17] = new RoadTile(tRoadTileType::straight_horizontal, 4, 1);
	this->r[18] = new RoadTile(tRoadTileType::t_bottom, 4, 2);
	this->r[19] = new RoadTile(tRoadTileType::straight_horizontal, 4, 3);
	this->r[20] = new RoadTile(tRoadTileType::corner_bottomright, 4, 4);

	int row = 0;
	this->w[0] = new Waypoint(tWaypointDir::right, tRoadTileType::corner_topleft, row, 0, 1, 1);
	this->w[1] = new Waypoint(tWaypointDir::right, tRoadTileType::straight_horizontal, row, 1, 0, 2);
	this->w[2] = new Waypoint(tWaypointDir::right, tRoadTileType::straight_horizontal, row, 1, 1, 3);
	this->w[3] = new Waypoint(tWaypointDir::right, tRoadTileType::t_top, row, 2, 0, 4);
	this->w[4] = new Waypoint(tWaypointDir::right, tRoadTileType::t_top, row, 2, 2, 5);
	this->w[5] = new Waypoint(tWaypointDir::right, tRoadTileType::straight_horizontal, row, 3, 0, 6);
	this->w[6] = new Waypoint(tWaypointDir::right, tRoadTileType::straight_horizontal, row, 3, 1, 7);
	this->w[7] = new Waypoint(tWaypointDir::right, tRoadTileType::corner_topright, row, 4, 0, 10);
	this->w[8] = new Waypoint(tWaypointDir::up, tRoadTileType::corner_topleft, row, 0, 0, 0);
	this->w[9] = new Waypoint(tWaypointDir::up, tRoadTileType::t_top, row, 2, 1, 4);
	this->w[10] = new Waypoint(tWaypointDir::down, tRoadTileType::corner_topright, row, 4, 1, 13);

	row = 1;
	this->w[11] = new Waypoint(tWaypointDir::up, tRoadTileType::straight_vertical, row, 0, 0, 8);
	this->w[12] = new Waypoint(tWaypointDir::up, tRoadTileType::straight_vertical, row, 2, 0, 9);
	this->w[13] = new Waypoint(tWaypointDir::down, tRoadTileType::straight_vertical, row, 4, 0, 16);
	this->w[14] = new Waypoint(tWaypointDir::up, tRoadTileType::straight_vertical, row, 0, 1, 11);
	this->w[15] = new Waypoint(tWaypointDir::up, tRoadTileType::straight_vertical, row, 2, 1, 12);
	this->w[16] = new Waypoint(tWaypointDir::down, tRoadTileType::straight_vertical, row, 4, 1, 19);

	row = 2;
	this->w[17] = new Waypoint(tWaypointDir::up, tRoadTileType::t_left, row, 0, 0, 14);
	this->w[18] = new Waypoint(tWaypointDir::up, tRoadTileType::cross, row, 2, 1, 15);
	this->w[19] = new Waypoint(tWaypointDir::down, tRoadTileType::t_right, row, 4, 0, 27, 30);
	this->w[20] = new Waypoint(tWaypointDir::left, tRoadTileType::t_left, row, 0, 1, 17, 28);
	this->w[21] = new Waypoint(tWaypointDir::left, tRoadTileType::straight_horizontal, row, 1, 0, 20);
	this->w[22] = new Waypoint(tWaypointDir::left, tRoadTileType::straight_horizontal, row, 1, 1, 21);
	this->w[23] = new Waypoint(tWaypointDir::left, tRoadTileType::cross, row, 2, 0, 22);
	this->w[24] = new Waypoint(tWaypointDir::left, tRoadTileType::cross, row, 2, 2, 18, 23);
	this->w[25] = new Waypoint(tWaypointDir::left, tRoadTileType::straight_horizontal, row, 3, 0, 24);
	this->w[26] = new Waypoint(tWaypointDir::left, tRoadTileType::straight_horizontal, row, 3, 1, 25);
	this->w[27] = new Waypoint(tWaypointDir::left, tRoadTileType::t_right, row, 4, 1, 26);
	this->w[28] = new Waypoint(tWaypointDir::down, tRoadTileType::t_left, row, 0, 2, 31);
	this->w[29] = new Waypoint(tWaypointDir::up, tRoadTileType::cross, row, 2, 3, 18, 23);
	this->w[30] = new Waypoint(tWaypointDir::down, tRoadTileType::t_right, row, 4, 2, 33);

	row = 3;
	this->w[31] = new Waypoint(tWaypointDir::down, tRoadTileType::straight_vertical, row, 0, 0, 34);
	this->w[32] = new Waypoint(tWaypointDir::up, tRoadTileType::straight_vertical, row, 2, 0, 29);
	this->w[33] = new Waypoint(tWaypointDir::down, tRoadTileType::straight_vertical, row, 4, 0, 36);
	this->w[34] = new Waypoint(tWaypointDir::down, tRoadTileType::straight_vertical, row, 0, 1, 37);
	this->w[35] = new Waypoint(tWaypointDir::up, tRoadTileType::straight_vertical, row, 2, 1, 32);
	this->w[36] = new Waypoint(tWaypointDir::down, tRoadTileType::straight_vertical, row, 4, 1, 39);

	row = 4;
	this->w[37] = new Waypoint(tWaypointDir::down, tRoadTileType::corner_bottomleft, row, 0, 0, 40);
	this->w[38] = new Waypoint(tWaypointDir::up, tRoadTileType::t_bottom, row, 2, 1, 35);
	this->w[39] = new Waypoint(tWaypointDir::down, tRoadTileType::corner_bottomright, row, 4, 1, 47);
	this->w[40] = new Waypoint(tWaypointDir::right, tRoadTileType::corner_bottomleft, row, 0, 1, 41);
	this->w[41] = new Waypoint(tWaypointDir::right, tRoadTileType::straight_horizontal, row, 1, 0, 42);
	this->w[42] = new Waypoint(tWaypointDir::right, tRoadTileType::straight_horizontal, row, 1, 1, 43);
	this->w[43] = new Waypoint(tWaypointDir::right, tRoadTileType::t_bottom, row, 2, 0, 38);
	this->w[44] = new Waypoint(tWaypointDir::left, tRoadTileType::t_bottom, row, 2, 2, 38);
	this->w[45] = new Waypoint(tWaypointDir::left, tRoadTileType::straight_horizontal, row, 3, 0, 44);
	this->w[46] = new Waypoint(tWaypointDir::left, tRoadTileType::straight_horizontal, row, 3, 1, 45);
	this->w[47] = new Waypoint(tWaypointDir::left, tRoadTileType::corner_bottomright, row, 4, 0, 46);

	this->adjList.resize(48);

	// Constructs the adjacency list using waypoints.
	for (auto i = 0; i < 48; i++){
		for (auto j = 0; j < 3; j++) {
			auto next = this->w[i]->get_next_indexes()[j];
			if (next != -1) {
				this->adjList[i].push_back(next);

			}
		}
	}

	// Traffic Lights
	this->t[0] = new TrafficLight(725, 172, 90, tLightState::green, this->w[3]);
	this->t[1] = new TrafficLight(850, 200, 0, tLightState::red, this->w[9]);
	this->t[2] = new TrafficLight(850, 680, 0, tLightState::green, this->w[29]);
	this->t[3] = new TrafficLight(875, 555, 3*90, tLightState::red, this->w[24]);
	this->t[4] = new TrafficLight(875, 1030, 3*90, tLightState::red, this->w[44]);
	this->t[5] = new TrafficLight(725, 1125, 1*90, tLightState::green, this->w[43]);

	// Traffic Light Groups
	this->tg[0] = new TrafficLightGroup(GROUP1_DURATION);
	this->tg[0]->add(this->t[0]);
	this->tg[0]->add(this->t[1]);

	this->tg[1] = new TrafficLightGroup(GROUP2_DURATION);
	this->tg[1]->add(this->t[2]);
	this->tg[1]->add(this->t[3]);

	this->tg[2] = new TrafficLightGroup(GROUP3_DURATION);
	this->tg[2]->add(this->t[4]);
	this->tg[2]->add(this->t[5]);

	// Get waypoint position, then initialize BusStop at that position
	float x, y, dir;
	this->w[2]->getPosition(x, y, dir);
	this->bs[0] = new BusStop(x, y, dir);

	this->w[6]->getPosition(x, y, dir);
	this->bs[1] = new BusStop(x, y, dir);

	this->w[30]->getPosition(x, y, dir);
	this->bs[2] = new BusStop(x, y, dir);

	this->w[35]->getPosition(x, y, dir);
	this->bs[3] = new BusStop(x, y, dir);

	this->w[21]->getPosition(x, y, dir);
	this->bs[4] = new BusStop(x, y, dir);

	this->w[14]->getPosition(x, y, dir);
	this->bs[5] = new BusStop(x, y, dir);

	this->w[46]->getPosition(x, y, dir);
	this->bs[6] = new BusStop(x, y, dir);

	this->w[15]->getPosition(x, y, dir);
	this->bs[7] = new BusStop(x, y, dir);


	this->city_time = sf::seconds(0.0f);
}

void City::getPosition(int current_next, float& x, float& y, float& dir)
{
	// Gives the waypoint position with global index
	this->w[current_next]->getPosition(x, y, dir);
}

void City::simulateAllLights(sf::Clock& clk)
{
	// Update all traffic lights based on how much time passed after last call, also update city's time.
	sf::Time currTime = clk.getElapsedTime();
	float deltaTime = (currTime - this->city_time).asSeconds();
	this->city_time = currTime;
	this->tg[0]->simulate(deltaTime);
	this->tg[1]->simulate(deltaTime);
	this->tg[2]->simulate(deltaTime);
}

void City::moveAllVehicles(sf::RenderWindow& window)
{
	// For all cars
	for (auto i = 0; i < vehicles.size(); i++) {
		vehicles[i]->move(window);
	}
}

void City::findShortestPath(Bus* b)
{
	// Determines shortest route of a Bus according to its stops.
	int pred[48], dist[48], start, end, crawl;

	auto routes = b->getStop();

	std::vector<int> subRoute;

	// Calculate bigger part of the route
	for (auto it = routes.begin(); it != routes.end(); it++) {

		// Find shortest path between two consecutive iterators.
		// If iterator is last but one, end becomes routes[0] to form cyclic path.
		if (it + 1 == routes.end()) {
			start = *(it);
			end = *(routes.begin());
		}
		else {
			start = *(it);
			end = *(std::next(it, 1));
		}
		

		// If two waypoint are not connected to each other, return
		// Of course, this does not apply for our simulator
		if (!this->bfs(start, end, pred, dist)) {
			std::cout << "Not connected " << std::endl;
			return;
		}

		// From end, iterate to begin and form the subRoute.
		crawl = end;
		while (pred[crawl] != -1) {
			subRoute.push_back(pred[crawl]);
			crawl = pred[crawl];
		}

		// Subroute is in reverse order, so we need to append it in reverse order too.
		for (auto it = subRoute.rbegin(); it != subRoute.rend(); it++) {
			b->addPath(*it);
		}

		// Do not forget to clear subRoute vector after inserting it.
		subRoute.clear();
	}
}

std::vector<int> City::giveNexts(int index)
{
	// Returns possible destination waypoint from given index, including -1 indexes.
	return this->w[index]->get_next_indexes();
}

void City::draw(sf::RenderWindow& window) 
{
	for (int i = 0; i <= 47; i++) {
		if (i <= 20) {
			r[i]->draw(window);
		}
		w[i]->draw(window);
	}
	for (int i = 0; i <= 5; i++) {
		t[i]->draw(window);
	}
	for (int i = 0; i <= 7; i++) {
		bs[i]->draw(window);
	}
}

bool City::checkDrive(int index)
{
	return this->w[index]->getDrive();
}

void City::checkAllCollision()
{	
	// Call collision detect method of each vehicle object.
	for (auto it1 = vehicles.begin(); it1 + 1 != vehicles.end(); it1++) {
		for (auto it2 = it1 + 1; it2 != vehicles.end(); it2++) {
			(*it1)->detectCollision(*it2);
		}
	}
}
