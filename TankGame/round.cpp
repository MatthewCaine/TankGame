#include "pch.h"
#include "round.h"

int Round::counter()
{
	static int counter = 0;
	return counter++;
}

Round::Round(TANK i, sf::Vector2<float> pos, float rot) : ID(counter())
{
	round_texture = new sf::Texture();
	switch (i)
	{
	case ONE:
		if (!Collision::CreateTextureAndBitmask(*round_texture, "Textures/round_1.png"))
			exit(1);
		break;

	case TWO:
		if (!Collision::CreateTextureAndBitmask(*round_texture, "Textures/round_2.png"))
			exit(1);
		break;

	}

	round.setTexture(*round_texture);

	round.setPosition(pos);
	round.setRotation(rot);
	tank_id = i;
}


// getters
sf::Sprite *Round::get_round()
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

