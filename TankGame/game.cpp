#include "pch.h"
#include "game.h"

GameElements::GameElements(sf::RenderWindow& rw)
{
	window = &rw;
	
	tanks.add("One");
	tanks.add("Two");

	tanks.get_tank(ONE).setPosition(200.f, 200.f);
	tanks.get_tank(TWO).rotate(180);
	tanks.get_tank(TWO).setPosition(2800.f, 1800.f);

	game_turn_on();
}

GameElements::GameElements(GameElements* ref)
{
	map = ref->map;
	tanks = ref->tanks;
	window = ref->window;
	rounds = ref->rounds;
}

void GameElements::interaction(TANK tank)
{
	for (int i = 0; i < rounds.get_size(); i++)
	{
		if (check_if_round_hits(tank, rounds[i]))
		{
			tanks[tank].destroyed();
			game_turn_off();			// if tank destroyed turns the game off
		}
	}

	if (tanks[tank].get_id() == ONE)
	{
		if (check_if_tank_intersects(tank))
		{
			tanks[tank].set_position(300.f, 300.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !check_if_tank_intersects(tank))
			tanks[tank].move(FORWARD);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !check_if_tank_intersects(tank))
			tanks[tank].move(BACKWARD);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !check_if_tank_intersects(tank))
			tanks[tank].turn(LEFT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !check_if_tank_intersects(tank))
			tanks[tank].turn(RIGHT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) )
			shoot(tank);
	}
	else if (tanks[tank].get_id() == TWO)
	{
		if (check_if_tank_intersects(tank))
		{
			tanks[tank].set_position(1800.f, 1600.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			tanks[tank].move(FORWARD);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			tanks[tank].move(BACKWARD);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			tanks[tank].turn(LEFT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			tanks[tank].turn(RIGHT);
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
			shoot(tank);
	}
}

void GameElements::shoot(TANK tank)
{
	rounds.add(tanks[tank].get_id(), tanks[tank].get_position(), tanks[tank].get_rotation());
}



bool GameElements::check_if_tank_intersects(TANK tank)
{
	// THIS CHECKS IF ONE TANKS TOUCHES ANOTHER BUT CREATES A LOT OF BUGS
	if(tank == ONE)
		if ( Collision::PixelPerfectTest(*tanks[tank].getTank(), *tanks[TWO].getTank()) )
			return true;

	if (tank == TWO)
		if (Collision::PixelPerfectTest(*tanks[ONE].getTank(), *tanks[tank].getTank()))
			return true;

	{
		if (tanks[tank].get_position_x() <= 0)
			return true;

		else if (tanks[tank].get_position_y() <= 0)
			return true;

		else if (tanks[tank].get_position_x() >= WINDOW_WIDTH)
			return true;

		else if (tanks[tank].get_position_y() >= WINDOW_HEIGHT)
			return true;

		else
			return false;
	}
}

bool GameElements::check_if_round_collides(Round& round)
{
	if (round.get_position_x() <= 0)
		return true;

	else if (round.get_position_x() >= WINDOW_WIDTH)
		return true;

	else if (round.get_position_y() <= 0)
		return true;

	else if (round.get_position_y() >= WINDOW_HEIGHT)
		return true;

	else
		return false;
}

bool GameElements::check_if_round_hits(TANK tank, Round& round)
{
	if (Collision::PixelPerfectTest(*round.get_round(), *tanks[tank].getTank()) && round.get_rounds_tank_id() != tanks[tank].get_id())
	{
		return true;
	}
	return false;
}

void GameElements::change_round_rotation(Round& round)
{
	if (check_if_round_collides(round))                       // check if round collides with walls
	{
		round.set_rotation( sin(round.get_rotation() * 3.14159) * 180 );   // change the rotation so it bounces off
	}
}



void GameElements::draw_map()
{
	window->draw(map.get_map());
}

void GameElements::draw_tanks()
{
	interaction(ONE);
	interaction(TWO);
	window->draw(tanks.get_tank(ONE));
	window->draw(tanks.get_tank(TWO));
}

void GameElements::draw_rounds()
{
	for (int i = 0; i < rounds.get_size(); i++)                         // for each existing round
	{
		change_round_rotation(rounds[i]);
		rounds.get_round(i)->move(sf::Vector2f(cos(rounds.get_round(i)->getRotation() * 3.14159 / 180) * SPEED * 5, sin(rounds.get_round(i)->getRotation() * 3.14159 / 180) * SPEED * 5));
		window->draw(*rounds.get_round(i));
	}
}


void GameElements::reset_tanks()
{
	tanks[ONE].set_position(300.f, 300.f);
	tanks[TWO].set_position(2800.f, 1800.f);
	tanks[ONE].reset();
	tanks[TWO].reset();
}

void GameElements::reset_rounds()
{
	rounds.clear();
}
