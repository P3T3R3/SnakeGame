#include <SFML/Graphics.hpp>
#ifndef POLE_H
#define POLE_H
class Pole
{
private:
	bool isWall;
public:
	Pole(std::string,float, float, bool);
	int snakeWeight;
	bool isEmpty, isFruit;
	sf::Vector2f pos;
	sf::Texture texture;
	sf::Sprite sprite;
	bool setSprite(std::string);
};

#endif