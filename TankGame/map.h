#pragma once

#ifndef MAP_H_
#define MAP_H_

#include "pch.h"

class Map
{
private:
	sf::Texture map_texture;
	sf::Sprite map_sprite;
public:
	Map()
	{
		// make sand texture
		if (!map_texture.loadFromFile("beach_text.jpg"))
		{
			exit(2);
		}
		map_texture.setSmooth(true);
		map_sprite.setTexture(map_texture);
		map_sprite.setTextureRect(sf::IntRect(0, 0, 3000, 2000));

	}
	Map(const Map *other): map_sprite(other->map_sprite), map_texture(other->map_texture) {}   // copy constructor

	sf::Sprite &get_map() { return map_sprite; }  // map getter
};



#endif // !MAP_H_
