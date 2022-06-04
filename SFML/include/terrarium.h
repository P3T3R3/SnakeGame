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
	sf::Vector2i headPos;
	int snakeLenght;
	//board
	const int sizeOfBoard;
	std::vector<Pole> pierwszyRzad, drugiRzad, trzeciRzad, czwartyRzad,
		piatyRzad, szostyRzad, siodmyRzad, osmyRzad;
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
	void restartGame();
};
#endif

