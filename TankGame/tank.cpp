#include "pch.h"
#include "tank.h"

// constructors
Tank::Tank(std::string name) : tank_name(name), ID(tank_counter()), is_playing(true)
{
	drawTank();
}

void Tank::operator=(Tank* other)
{
	*tank_texture = std::move(*other->tank_texture);
	is_playing = other->is_playing;
	ID = other->ID;
	tank_name = other->tank_name;
	tank = other->tank;
}


Tank::Tank(const Tank* other) : ID(other->ID), tank_name(other->tank_name), tank(other->tank), tank_texture(new sf::Texture(*other->tank_texture)), is_playing(other->is_playing) {}


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

sf::Sprite *Tank::getTank()
{
	return &tank;
}

const sf::Vector2f Tank::get_position()		// return the middle point of front of the tank (it's purely for shooting purposes)
{
	sf::Vector2f pos = tank.getPosition();
	pos.y = pos.y + 298.3287 * sin(tank.getRotation()  * 3.14159 / 180);
	pos.x = pos.x + 298.3287 * cos(tank.getRotation()  * 3.14159 / 180);
	return pos;
}

const float Tank::get_rotation()
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


sf::FloatRect Tank::getBounds()
{
	return tank.getGlobalBounds();
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
	tank_texture = new sf::Texture();
	// take tank texture
	if (get_id() == ONE)
	{
		if (!tank_texture->loadFromFile("Textures/tank_1.png"))
		{
			exit(1);
		}
	}
	else if (get_id() == TWO)
	{
		if (!tank_texture->loadFromFile("Textures/tank_2.png"))
		{
			exit(1);
		}
	}


	// assign texture to the tank
	if (get_id() == ONE)
		tank.setTexture(*tank_texture);
	else if (get_id() == TWO)
		tank.setTexture(*tank_texture);

	tank.setTextureRect(sf::IntRect(0, 0, 290, 140));
	tank.setOrigin(sf::Vector2f(0.f, 70.f));           // sets the operating point in the middle of back axis
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

void Tank::reset()
{ 
	is_playing = true; 
}