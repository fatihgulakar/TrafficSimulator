#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <list>
#include <string>

enum class tRoadTileType {
	corner_bottomleft, corner_bottomright, corner_topleft,
	corner_topright, cross, straight_horizontal, straight_vertical,
	t_bottom, t_left, t_right, t_top
};
enum class tCarType { car1, car2, car3, car4, car5, car6 };
enum class tWaypointDir { right, down, left, up };
enum class tLightState {red, green};


// Game map constants
constexpr auto X_MARGIN = 205;
constexpr auto Y_MARGIN = 3;
constexpr auto TILE_SIZE = 239;

constexpr auto FRAMES_PER_SEC = 40;

// Traffic Light Groups' duration times, in seconds
constexpr auto GROUP1_DURATION = 5.0f;
constexpr auto GROUP2_DURATION = 5.5f;
constexpr auto GROUP3_DURATION = 5.0f;

// Movement constants
constexpr auto X_STEP = 8;
constexpr auto Y_STEP = 8;
constexpr auto ANGLE_STEP = 2.8125f;
constexpr auto RADIUS = 99;
const auto PI = std::acos(-1.0f);

// Constants for smooth movement
constexpr auto ACCELERATION = 0.2f;
constexpr auto MAX_SPEED = 5.0f;
constexpr auto MIN_SPEED = 0.1f;

// To predetermine collision.
constexpr auto COLLISION_SCALE = 1.6f;

