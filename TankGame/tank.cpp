#include "pch.h"
#include "tank.h"

// constructors
Tank::Tank(std::string name) : tank_name(name), ID(tank_counter()), is_playing(true)
{
	drawTank();
}

void Tank::operator=(Tank* other)
{
	is_playing = other->is_playing;
	ID = other->ID;
	tank_name = other->tank_name;
	tank_texture = other->tank_texture;
	tank = other->tank;
}

Tank::Tank(const Tank* other) : ID(other->ID), tank_name(other->tank_name), tank(other->tank), tank_texture(other->tank_texture), is_playing(other->is_playing) {}


// getters
TANK Tank::get_id()
{
	switch (ID)
	{
	case 0:
		return ONE;
	case 1:
		return TWO;
	case 2:
		return THREE;
	case 3:
		return FOUR;
	default:
		exit(1);
	}
	
}

sf::FloatRect *Tank::getBounds()
{
	return &tank.getGlobalBounds();
}

sf::ConvexShape *Tank::getTank()
{
	return &tank;
}

const sf::Vector2f &Tank::get_position()
{
	return tank.getPosition();
}

const float &Tank::get_rotation()
{
	return tank.getRotation();
}

float Tank::get_position_x()
{
	return tank.getPosition().x;
}
float Tank::get_position_y()
{
	return tank.getPosition().y;
}

float Tank::get_local_bound_x()
{
	return tank.getLocalBounds().width;
}
float Tank::get_local_bound_y()
{
	return tank.getLocalBounds().height;
}

// setter
void Tank::set_position(float x, float y)
{
	tank.setPosition(x, y);
}
// Used in constructors
void Tank::drawTank()
{
	// take tank texture
	if (!tank_texture.loadFromFile("tank_1.jpg"))
	{
		exit(1);
	}

	// resize it to 8 points
	tank.setPointCount(9);

	// define the points making tank shape
	tank.setPoint(0, sf::Vector2f(210.f, 50.f));
	tank.setPoint(1, sf::Vector2f(210.f, 60.f));
	tank.setPoint(2, sf::Vector2f(150.f, 60.f));
	tank.setPoint(3, sf::Vector2f(150.f, 100.f));
	tank.setPoint(4, sf::Vector2f(0.f, 100.f));
	tank.setPoint(5, sf::Vector2f(0.f, 0.f));
	tank.setPoint(6, sf::Vector2f(150.f, 0.f));
	tank.setPoint(7, sf::Vector2f(150.f, 40.f));
	tank.setPoint(8, sf::Vector2f(210.f, 40.f));
	tank.setOrigin(150.f, 50.f);

	// assign texture to the tank
	if (get_id() == ONE)
		tank.setFillColor(sf::Color(0, 255, 0));
	else if (get_id() == TWO)
		tank.setFillColor(sf::Color(255, 0, 0));


}

int Tank::tank_counter()
{
	static int counter = 0;
	return counter++;
}

void Tank::turn(TURN way)
{
	if (is_playing)
	{
		if (way == LEFT)
		{
			Tank::tank.rotate(-SPEED);
		}
		else if (way == RIGHT)
		{
			Tank::tank.rotate(SPEED);
		}
	}
}

void Tank::move(MOVE way)
{
	if (is_playing)
	{
		if (way == FORWARD)
		{
			Tank::tank.move(sf::Vector2f(cos(tank.getRotation() * 3.14159 / 180) * SPEED, sin(tank.getRotation() * 3.14159 / 180) * SPEED));
		}

		else if (way == BACKWARD)
		{
			Tank::tank.move(sf::Vector2f(cos(tank.getRotation() * 3.14159 / 180) * -SPEED, sin(tank.getRotation() * 3.14159 / 180) * -SPEED));
		}
	}
}


void Tank::destroyed()  // if the tank is hit player cannot do anything
{
	is_playing = false;
}