#include "pole.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#ifndef TERRARIUM_H
#define TERRARIUM_H
class Terrarium
{
public:
	enum class mapType { empty, borders, maze };
	enum class moveType { up, down, right, left };

	Terrarium(mapType);

	void updateGameState(sf::RenderWindow&, sf::Clock&, sf::Clock&);
	void changeDirection(moveType);

	int getSizeOfBoard();

	moveType getMoveDirection();
	
private:
	
	bool isEnd;

	const unsigned int moveInterval=200;//in miliseconds
	const unsigned int fruitInterval = 3;//in seconds

	//snake
	sf::Vector2i headPos;
	int snakeLenght;

	//board
	const int sizeOfBoard;
	std::vector<Pole> firstRow, secondRow, thirdRow, fourthRow,
		fifthRow, sixthRow, seventhRow, eighthRow;
	std::vector<std::vector<Pole>> board;

	sf::Font arial;
	sf::Text scoreText;

	bool initializeFonts();
	sf::Texture grassTexture, bodyTexture, headTexture,fruitTexture,wallTexture;
	bool readTexture(std::string, sf::Texture &);
	bool prepareTextures();

	
	mapType typeOfMap;
	moveType moveDirection;

	void setUpInitialState();
	void setUpTiles();
	void move();
	void extendSnake();
	void generateFruit();
	void endGame();
	void saveScoreToFile(std::string nazwaPliku);
};
#endif

