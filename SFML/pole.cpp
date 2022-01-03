#include "pole.h"
#include <iostream>


	Pole::Pole(std::string textureName="", float x=0, float y=0, bool czySciana=0) {
		if (!setSprite(textureName))
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
	bool Pole::setSprite(std::string textureName) {
		if (!texture.loadFromFile(textureName)) {
			std::cout << "Blad ladowania textury" << std::endl;
			return false;
		}
		texture.setSmooth(true);
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		return true;
	}
