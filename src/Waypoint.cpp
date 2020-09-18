#include "Waypoint.h"

Waypoint::Waypoint(tWaypointDir dir, tRoadTileType type, int row, int col, int idx, int next1, int next2, int next3)
{
    std::cout << "Waypoint object is initialized" << std::endl;
    this->next1 = next1;
    this->next2 = next2;
    this->next3 = next3;
    this->dir = static_cast<int>(dir); // dir is tWaypoint enum class, so casting it to "int" is needed.

    this->canDrive = true;
	switch (dir)
	{
    case tWaypointDir::down:
        this->texture.loadFromFile("./images/waypoints/down.png");
        this->sprite.setTexture(this->texture);
        break;
    case tWaypointDir::up:
        this->texture.loadFromFile("./images/waypoints/up.png");
        this->sprite.setTexture(this->texture);
        break;
    case tWaypointDir::left:
        this->texture.loadFromFile("./images/waypoints/left.png");
        this->sprite.setTexture(this->texture);
        break;
    case tWaypointDir::right:
        this->texture.loadFromFile("./images/waypoints/right.png");
        this->sprite.setTexture(this->texture);
        break;
    default:
        std::cout << "Invalid type of direction." << std::endl;
        break;
	}
    
    // x_internal and y_internal are coordinates of a waypoint in regards to Road Tile it belongs to. 
    auto x_internal = 0;
    auto y_internal = 0;

    switch (type)
    {
    case tRoadTileType::corner_bottomleft:
        x_internal = (idx == 0 ? 118 : 218);
        y_internal = (idx == 0 ? 20 : 121);
        break;
    case tRoadTileType::corner_bottomright:
        x_internal = (idx == 0 ? 20 : 118);
        y_internal = (idx == 0 ? 121 : 20);
        break;
    case tRoadTileType::corner_topleft:
        x_internal = (idx == 0 ? 118 : 218);
        y_internal = (idx == 0 ? 218 : 121);
        break;
    case tRoadTileType::corner_topright:
        x_internal = (idx == 0 ? 20 : 118);
        y_internal = (idx == 0 ? 121 : 218);
        break;
    case tRoadTileType::cross:
        x_internal = ((idx == 1 || idx == 3) ? 118 : (idx == 0) ? 20 : 218);
        y_internal = ((idx == 0 || idx == 2) ? 121 : (idx == 1) ? 20 : 218);
        break;
    case tRoadTileType::straight_horizontal:
        x_internal = (idx == 0 ? 20 : 172);
        y_internal = 121;
        break;
    case tRoadTileType::straight_vertical:
        x_internal = 118;
        y_internal = (idx == 0 ? 20 : 172);
        break;
    case tRoadTileType::t_bottom:
        x_internal = (idx == 0 ? 20 : (idx == 1) ? 118 : 218);
        y_internal = ((idx == 0 || idx == 2) ? 121 : 20);
        break;
    case tRoadTileType::t_left:
        x_internal = ((idx == 0 || idx == 2) ? 118 : 218);
        y_internal = (idx == 0 ? 20 : (idx == 1) ? 121 : 218);
        break;
    case tRoadTileType::t_right:
        x_internal = ((idx == 0 || idx == 2) ? 118 : 20);
        y_internal = (idx == 0 ? 20 : (idx == 1) ? 121 : 218);
        break;
    case tRoadTileType::t_top:
        x_internal = (idx == 0 ? 20 : (idx == 1) ? 118 : 218);
        y_internal = ((idx == 0 || idx == 2) ? 121 : 218);
        break;
    default:
        break;
    }

    // Global coordinates of waypoint
    this->x = static_cast<float>(x_internal + X_MARGIN + col * TILE_SIZE);
    this->y = static_cast<float>(y_internal + Y_MARGIN + row * TILE_SIZE);

    this->sprite.setOrigin(sf::Vector2f(this->texture.getSize().x * 0.5, this->texture.getSize().y * 0.5));
    

}

void Waypoint::getPosition(float& x, float& y, float& dir) {
    x = this->x;
    y = this->y;
    dir = static_cast<float>(this->dir);
}

void Waypoint::draw(sf::RenderWindow& window)
{
    this->sprite.setPosition(this->x, this->y);
    window.draw(this->sprite);
}

bool Waypoint::getDrive()
{
	return this->canDrive;
}

void Waypoint::setDrive(bool status)
{
    this->canDrive = status;
}

std::vector<int> Waypoint::get_next_indexes()
{
    return {this->next1, this->next2, this->next3};
}
