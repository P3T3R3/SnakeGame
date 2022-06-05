#include <SFML/Graphics.hpp>
#ifndef TILE_H
#define TILE_H
class Tile
{
private:
	const bool isWall;
public:
	Tile(sf::Texture&,float, float, bool);
	int snakeWeight; //how many moves snake stays
	bool isEmpty, isFruit;
	sf::Vector2f pos;
	sf::Sprite sprite;
	bool setSprite(sf::Texture &);
};

#endif