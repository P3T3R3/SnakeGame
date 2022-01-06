#include "pole.h"
#include <iostream>

//std::string textureName=""
	Pole::Pole(sf::Texture*texture, float x=0, float y=0, bool czySciana=0) {
		if (!setSprite(texture))
			return;
		pos = sf::Vector2f(x, y);
		isWall = czySciana;
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
