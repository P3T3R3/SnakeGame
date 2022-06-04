#include "../include/pole.h"
#include <iostream>

	Pole::Pole(sf::Texture*texture, float x, float y, bool isWall_=0) {
		if (!setSprite(texture))
			return;
		pos = sf::Vector2f(x, y);
		isWall = isWall_;
		if (isWall)
			isEmpty = false;
		else
			isEmpty = true;
		isFruit = false;
		snakeWeight = 0;
		sprite.setPosition(pos);
	}
	bool Pole::setSprite(sf::Texture *texture) {
		sprite.setTexture(*texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		return true;
	}
