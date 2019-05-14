#pragma once

/*
	THIS CLASS HAS DATA OF EACH TANK AND DRAWS IT
*/

#include "pch.h"
#include "universal.h"

#ifndef TANK_DRAWER_H_
#define TANK_DRAWER_H_

class Tank
{
private:

	static int tank_counter();
	int ID;

	std::string tank_name;
	sf::Texture * tank_texture;
	sf::ConvexShape tank; //the tank itself
	
	bool is_playing = true;

public:
	TANK get_id();

	Tank(std::string);
	Tank(const Tank*);
	void operator=(Tank*);

	void drawTank();              // Creation of the tank
	void set_position(float,float);

	sf::ConvexShape *getTank();   // Sprite of Tank
	sf::FloatRect getBounds();   // bounds of Tank
	const sf::Vector2f &get_position();
	const float &get_rotation();

	float get_position_x();
	float get_position_y();
	float get_local_bound_x();
	float get_local_bound_y();

	// interactions with the tank
	void turn(TURN);
	void move(MOVE);

	void destroyed();
	void reset();
};


#endif // !TANK_DRAWER
