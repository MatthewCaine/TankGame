#include "pch.h"
#include "round.h"

int Round::counter()
{
	static int counter = 0;
	return counter++;
}

Round::Round(TANK i, sf::Vector2<float> pos, float rot) : ID(counter())
{
	round = sf::CircleShape(20.f);
	if(i == ONE)
		round.setFillColor(sf::Color::Magenta);
	else if(i == TWO)
		round.setFillColor(sf::Color::Cyan);

	round.setPosition(pos);
	round.setRotation(rot);
	tank_id = i;
}


// getters
sf::CircleShape *Round::get_round()
{
	return &round;
}

sf::FloatRect Round::get_bounds()
{
	return round.getGlobalBounds();
}

float Round::get_position_x()
{
	return round.getPosition().x;
}
float Round::get_position_y()
{
	return round.getPosition().y;
}
float Round::get_rotation()
{
	return round.getRotation();
}

// setters
void Round::set_rotation(float t)
{
	round.setRotation(t);
}

void Round::set_position(sf::Vector2<float> t)
{
	round.setPosition(t);
}

