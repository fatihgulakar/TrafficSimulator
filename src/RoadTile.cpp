#include "RoadTile.h"
// row and col starts from 0
RoadTile::RoadTile(tRoadTileType t, int row, int col)
{
    std::cout << "RoadTile object is initialized" << std::endl;
	this->x = static_cast<float>(X_MARGIN + col * TILE_SIZE); 
	this->y = static_cast<float>(Y_MARGIN + row * TILE_SIZE);
	switch (t)
	{
    case tRoadTileType::corner_bottomleft:
        this->texture.loadFromFile("./images/roadpieces/corner-bottomleft.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::corner_bottomright:
        this->texture.loadFromFile("./images/roadpieces/corner-bottomright.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::corner_topleft:
        this->texture.loadFromFile("./images/roadpieces/corner-topleft.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::corner_topright:
        this->texture.loadFromFile("./images/roadpieces/corner-topright.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::cross:
        this->texture.loadFromFile("./images/roadpieces/cross.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::straight_horizontal:
        this->texture.loadFromFile("./images/roadpieces/straight-horizontal.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::straight_vertical:
        this->texture.loadFromFile("./images/roadpieces/straight-vertical.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::t_bottom:
        this->texture.loadFromFile("./images/roadpieces/t-bottom.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::t_left:
        this->texture.loadFromFile("./images/roadpieces/t-left.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::t_right:
        this->texture.loadFromFile("./images/roadpieces/t-right.png");
        this->sprite.setTexture(this->texture);
        break;
    case  tRoadTileType::t_top:
        this->texture.loadFromFile("./images/roadpieces/t-top.png");
        this->sprite.setTexture(this->texture);
        break;
    default:
        std::cout << "Invalid type of Road Tile type." << std::endl;
        break;
	}
}

void RoadTile::draw(sf::RenderWindow& window)
{
    this->sprite.setPosition(this->x, this->y);
    window.draw(this->sprite);
}
