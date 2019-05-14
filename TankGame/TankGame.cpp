#pragma once
#include "pch.h"

int main()
{

	// creating the window displaying the game
	sf::RenderWindow main_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game Of Tanks", sf::Style::Default);
	main_window.setVerticalSyncEnabled(true);
	
	GameElements the_game(main_window);  // creating everything the game consists of



	sf::Font font;
	if (!font.loadFromFile("ComicSans.ttf"))
		return EXIT_FAILURE;

	// Initialize the pause message
	sf::Text pauseMessage;
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(100);
	pauseMessage.setPosition(800.f, 800.f);
	pauseMessage.setFillColor(sf::Color::Red);
	pauseMessage.setString("Welcome to Game Of Tanks!\nPress enter to start the game");
	pauseMessage.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::Text gameOverMessage;
	gameOverMessage.setFont(font);
	gameOverMessage.setCharacterSize(100);
	gameOverMessage.setPosition(800.f, 800.f);
	gameOverMessage.setFillColor(sf::Color::Yellow);
	gameOverMessage.setString("           Game over !!! \n Press Enter to Play Again");


	sf::Text PlayerOneMsg;
	PlayerOneMsg.setFont(font);
	PlayerOneMsg.setCharacterSize(50);
	PlayerOneMsg.setPosition(100.f, 1800.f);
	PlayerOneMsg.setFillColor(sf::Color::White);
	PlayerOneMsg.setString("Player One: \nWSAD + Spacebar");

	sf::Text PlayerTwoMsg;
	PlayerTwoMsg.setFont(font);
	PlayerTwoMsg.setCharacterSize(50);
	PlayerTwoMsg.setPosition(2600.f, 1800.f);
	PlayerTwoMsg.setFillColor(sf::Color::White);
	PlayerTwoMsg.setString("     Player Two:\nArrows + RCtrl");





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

			// Enter key pressed: play
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Enter))
			{
				// (re)start the game
				if (!is_playing)
				{
					is_playing = true;
				}
				// After Game Over
				else if (!the_game.get_game_state())
				{
					is_playing = true;
					the_game.reset_tanks();
					the_game.reset_rounds();
					the_game.game_turn_on();
				}
			}
			if (event.key.code == sf::Keyboard::LControl)
				is_playing = false;
		}

		main_window.clear(sf::Color::Black);

		if (is_playing)
		{
			the_game.draw_map();
			the_game.draw_tanks();
			the_game.draw_rounds();
			
		}
		if (!is_playing && the_game.get_game_state())
		{
			main_window.draw(pauseMessage);
			main_window.draw(PlayerOneMsg);
			main_window.draw(PlayerTwoMsg);
		}

		if (!the_game.get_game_state())
		{
			main_window.draw(gameOverMessage);
			
		}

		main_window.display();
	}

	return EXIT_SUCCESS;
}


