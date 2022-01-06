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
	int snakeLenght;
	std::vector<std::vector<Pole *>> plansza;
	sf::Font arial;
	sf::Text scoreText;
	bool initializeFonts();
	sf::Texture grassTexture, bodyTexture, headTexture,fruitTexture;
	bool readTexture(std::string, sf::Texture *);
	bool prepareTextures();
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
	void updateGameState(sf::RenderWindow *,sf::Clock*, sf::Clock*);

	void endGame();
};
#endif

