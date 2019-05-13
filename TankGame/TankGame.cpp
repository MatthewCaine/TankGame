#pragma once
#include "pch.h"

int main()
{

	// creating the window displaying the game
	sf::RenderWindow main_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Hello World !", sf::Style::Default);
	main_window.setVerticalSyncEnabled(true);
	
	GameElements the_game(main_window);  // creating everything the game consists of

	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setCharacterSize(100);
	pauseMessage.setPosition(1200.f, 800.f);
	pauseMessage.setFillColor(sf::Color::White);
	pauseMessage.setString("Welcome to SFML pong!\nPress space to start the game");
	pauseMessage.setStyle(sf::Text::Bold | sf::Text::Underlined);

	bool is_playing = false;
	// The loop in which the game is happening
	while (main_window.isOpen())
	{
		sf::Event event;
		while (main_window.pollEvent(event))
		{
			// Window closed or escape key pressed: exit
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				main_window.close();
				break;
			}

			// Space key pressed: play
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
				if (!is_playing)
				{
					// (re)start the game
					is_playing = true;
					the_game.reset_tanks();
				}	
		}

		main_window.clear(sf::Color::Black);

		if (is_playing)
		{
			the_game.draw_map();
			the_game.draw_tanks();
			the_game.draw_rounds();
			if (event.key.code == sf::Keyboard::LControl)
				is_playing = false;
		}
		else
		{
			main_window.draw(pauseMessage);
		}

		main_window.display();
	}

	return EXIT_SUCCESS;
}


