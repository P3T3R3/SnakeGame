#include "pole.h"
#include <vector>
#include <fstream>
#ifndef TERRARIUM_H
#define TERRARIUM_H
class Terrarium
{
public:
	enum class mapType { empty, borders, maze };
	enum class moveType { up, down, right, left };
	Terrarium(mapType);
	void updateGameState(sf::RenderWindow*, sf::Clock*, sf::Clock*);
	int getRozmiarPlanszy();
	moveType getTypRuchu();
	void changeDirection(moveType);
private:
	bool isEnd;
	sf::Vector2i headPos;
	int snakeLenght;
	std::vector<std::vector<Pole *>> board;
	sf::Font arial;
	sf::Text scoreText;
	bool initializeFonts();
	sf::Texture grassTexture, bodyTexture, headTexture,fruitTexture,wallTexture;
	bool readTexture(std::string, sf::Texture *);
	bool prepareTextures();
	int rozmiarPlanszy;
	
	mapType typeOfMap;
	moveType moveDirection;
	void setUpInitialState();
	void setUpTiles();
	void move();
	void extendSnake();
	int generateRandomNumber();
	void generateFruit();
	

	void endGame();
	void zapiszWynikDoPliku(std::string nazwaPliku);
	void restartGame();
};
#endif

