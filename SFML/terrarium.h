#include "pole.h"
#include <vector>
#ifndef TERRARIUM_H
#define TERRARIUM_H
class Terrarium
{
public:
	bool isEnd;
	enum class mapType{ pusta, krzyz, labirynt };
	enum class moveType{up,down,right,left};
	sf::Vector2i headPos;
	sf::Vector2i tailPos;
	int snakeLenght;
	std::vector<std::vector<Pole *>> plansza;
	sf::Texture grassTexture, bodyTexture, headTexture,fruitTexture;
	bool readTexture(std::string name,sf::Texture *texture);
	void prepareTextures();
	int rozmiarPlanszy;
	Terrarium(mapType);
	mapType typMapy;
	moveType typRuchu;
	void setUpInitialState();
	void setUpTiles();

	void changeDirection(moveType);
	void move();
	void extendSnake();
	int generateRandomNumber();
	void generateFruit();

	void endGame();
};
#endif

