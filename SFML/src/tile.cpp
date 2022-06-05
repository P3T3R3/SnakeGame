#include "../include/tile.h"
#include <iostream>

	Tile::Tile(sf::Texture&texture, float x, float y, bool isWall_=0):isWall(isWall_) {
		pos = sf::Vector2f(x, y);
		isEmpty = !isWall;
		isFruit = false;
		snakeWeight = 0;
		setSprite(texture);
		sprite.setPosition(pos);
	}
	bool Tile::setSprite(sf::Texture &texture) { 
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		return true;
	}
