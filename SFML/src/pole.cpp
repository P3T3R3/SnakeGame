#include "../include/pole.h"
#include <iostream>

	Pole::Pole(sf::Texture&texture, float x, float y, bool isWall_=0):isWall(isWall_) {
		pos = sf::Vector2f(x, y);
		isEmpty = !isWall;
		isFruit = false;
		snakeWeight = 0;
		setSprite(texture);
		sprite.setPosition(pos);
	}
	bool Pole::setSprite(sf::Texture &texture) { 
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		return true;
	}
