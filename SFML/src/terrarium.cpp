#include "../include/terrarium.h"
#include <iostream>
#include <random>
Terrarium::Terrarium(mapType newMapType) {
	typeOfMap = newMapType;
	sizeOfBoard = 8;

	setUpInitialState();
	initializeFonts();
	prepareTextures();
	setUpTiles(); 
	
}
bool Terrarium::prepareTextures()
{
	if (
		readTexture("media/textures/head.png", &headTexture) &&
		readTexture("media/textures/snake.png", &bodyTexture) &&
		readTexture("media/textures/trawa.png", &grassTexture) &&
		readTexture("media/textures/owoc.png", &fruitTexture)&&
		readTexture("media/textures/wall.png",&wallTexture)
		)
		return true;
	else
		return false;
}
bool Terrarium::initializeFonts()
{
	if (!arial.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
		std::cout << "Can't load font arial\n";
		return false;
	}
	return true;
}
bool Terrarium::readTexture(std::string name, sf::Texture *texture)
{
	if (!texture->loadFromFile(name)) {
		std::cout << "Loading texture error" <<name<< std::endl;
		return false;
	}
	texture->setSmooth(true);
	return true;
}
void Terrarium::setUpInitialState() {
	isEnd = false;
	headPos = sf::Vector2i(3,3);
	moveDirection = moveType::right;
	snakeLenght = 1;
	scoreText.setFont(arial);
	scoreText.setPosition(sf::Vector2f(sizeOfBoard * 50 - 40, 0));
	scoreText.setOrigin(sf::Vector2f(0,0));
	scoreText.setFillColor(sf::Color(0, 0, 0, 255));
	scoreText.setOutlineColor(sf::Color(255, 255, 255, 255));
	scoreText.setOutlineThickness(3);
}
void Terrarium::setUpTiles() {
	board.clear();
	std::vector<Pole*> pierwszyRzad, drugiRzad, trzeciRzad, czwartyRzad, piatyRzad, szostyRzad, siodmyRzad, osmyRzad;;
	switch (typeOfMap)
	{
	case Terrarium::mapType::borders:
		for (int i = 0; i < sizeOfBoard; i++) {
			pierwszyRzad.push_back(new Pole(&wallTexture, i * 50, 0, true));
		}
		board.push_back(pierwszyRzad);

		drugiRzad.push_back(new Pole(&wallTexture,0, 50, true));
		for (int i = 1; i < sizeOfBoard-1; i++) {
			drugiRzad.push_back(new Pole(&grassTexture, i * 50, 50, false));
		}
		drugiRzad.push_back(new Pole(&wallTexture, sizeOfBoard*50-50, 50, true));
		board.push_back(drugiRzad);
		trzeciRzad.push_back(new Pole(&wallTexture, 0, 100, true));
		for (int i = 1; i < sizeOfBoard-1; i++) {
			trzeciRzad.push_back(new Pole(&grassTexture, i * 50, 100, false));
		}
		trzeciRzad.push_back(new Pole(&wallTexture, sizeOfBoard*50-50, 100, true));
		board.push_back(trzeciRzad);
		czwartyRzad.push_back(new Pole(&wallTexture, 0, 150, true));
		for (int i = 1; i < sizeOfBoard-1; i++) {
			czwartyRzad.push_back(new Pole(&grassTexture, i * 50, 150, false));
		}
		czwartyRzad.push_back(new Pole(&wallTexture, sizeOfBoard*50-50, 150, true));
		board.push_back(czwartyRzad);
		piatyRzad.push_back(new Pole(&wallTexture, 0, 200, true));
		for (int i = 1; i < sizeOfBoard-1; i++) {
			piatyRzad.push_back(new Pole(&grassTexture, i * 50, 200, false));
		}
		piatyRzad.push_back(new Pole(&wallTexture, sizeOfBoard*50-50, 200, true));
		board.push_back(piatyRzad);
		szostyRzad.push_back(new Pole(&wallTexture, 0, 250, true));
		for (int i = 1; i < sizeOfBoard-1; i++) {
			szostyRzad.push_back(new Pole(&grassTexture, i * 50, 250, false));
		}
		szostyRzad.push_back(new Pole(&wallTexture, sizeOfBoard*50-50, 250, true));
		board.push_back(szostyRzad);

		siodmyRzad.push_back(new Pole(&wallTexture, 0, 300, true));
		for (int i = 1; i < sizeOfBoard-1; i++) {
			siodmyRzad.push_back(new Pole(&grassTexture, i * 50, 300, false));
		}
		siodmyRzad.push_back(new Pole(&wallTexture,sizeOfBoard*50-50, 300, true));
		board.push_back(siodmyRzad);

		for (int i = 0; i < sizeOfBoard; i++) {
			osmyRzad.push_back(new Pole(&wallTexture, i * 50, 350, true));
		}
		board.push_back(osmyRzad);
		break;
	case Terrarium::mapType::empty:
		for (int i = 0; i < sizeOfBoard; i++) {
			pierwszyRzad.push_back(new Pole(&grassTexture, i * 50, 0, false));
		}
		board.push_back(pierwszyRzad);
		for (int i = 0; i < sizeOfBoard; i++) {
			drugiRzad.push_back(new Pole(&grassTexture, i * 50, 50, false));
		}
		board.push_back(drugiRzad);
		for (int i = 0; i < sizeOfBoard; i++) {
			trzeciRzad.push_back(new Pole(&grassTexture, i * 50, 100, false));
		}
		board.push_back(trzeciRzad);

		for (int i = 0; i < sizeOfBoard; i++) {
			czwartyRzad.push_back(new Pole(&grassTexture, i * 50, 150, false));
		}
		board.push_back(czwartyRzad);

		for (int i = 0; i < sizeOfBoard; i++) {
			piatyRzad.push_back(new Pole(&grassTexture, i * 50, 200, false));
		}
		board.push_back(piatyRzad);

		for (int i = 0; i < sizeOfBoard; i++) {
			szostyRzad.push_back(new Pole(&grassTexture, i * 50, 250, false));
		}
		board.push_back(szostyRzad);


		for (int i = 0; i < sizeOfBoard; i++) {
			siodmyRzad.push_back(new Pole(&grassTexture, i * 50, 300, false));
		}
		board.push_back(siodmyRzad);

		for (int i = 0; i < sizeOfBoard; i++) {
			osmyRzad.push_back(new Pole(&grassTexture, i * 50, 350, false));
		}
		board.push_back(osmyRzad);
		break;
	case Terrarium::mapType::maze:
		moveDirection = moveType::down;
		pierwszyRzad.push_back(new Pole(&grassTexture, 0, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 50, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 100, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 150, 0, false));
		pierwszyRzad.push_back(new Pole(&wallTexture, 200, 0, true));
		pierwszyRzad.push_back(new Pole(&grassTexture, 250, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 300, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 350, 0, false));
		board.push_back(pierwszyRzad);

		drugiRzad.push_back(new Pole(&grassTexture, 0, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 50, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 100, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 150, 50, false));
		drugiRzad.push_back(new Pole(&wallTexture, 200, 50, true));
		drugiRzad.push_back(new Pole(&grassTexture, 250, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 300, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 350, 50, false));
		board.push_back(drugiRzad);
		trzeciRzad.push_back(new Pole(&grassTexture, 0, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 50, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 100, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 150, 100, false));
		trzeciRzad.push_back(new Pole(&wallTexture, 200, 100, true));
		trzeciRzad.push_back(new Pole(&grassTexture, 250, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 300, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 350, 100, false));
		board.push_back(trzeciRzad);
		czwartyRzad.push_back(new Pole(&grassTexture, 0, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 50, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 100, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 150, 150, false));
		czwartyRzad.push_back(new Pole(&wallTexture, 200, 150, true));
		czwartyRzad.push_back(new Pole(&grassTexture, 250, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 300, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 350, 150, false));
		board.push_back(czwartyRzad);
		piatyRzad.push_back(new Pole(&grassTexture, 0, 200, false));
		piatyRzad.push_back(new Pole(&grassTexture, 50, 200, false));
		piatyRzad.push_back(new Pole(&grassTexture, 100, 200, false));
		piatyRzad.push_back(new Pole(&grassTexture, 150, 200, false));
		piatyRzad.push_back(new Pole(&wallTexture, 200, 200, true));
		piatyRzad.push_back(new Pole(&wallTexture, 250, 200, true));
		piatyRzad.push_back(new Pole(&wallTexture, 300, 200, true));
		piatyRzad.push_back(new Pole(&wallTexture, 350, 200, true));
		board.push_back(piatyRzad);

		for (int i = 0; i < sizeOfBoard; i++) {
			szostyRzad.push_back(new Pole(&grassTexture, i * 50, 250, false));
		}
		board.push_back(szostyRzad);


		for (int i = 0; i < sizeOfBoard; i++) {
			siodmyRzad.push_back(new Pole(&grassTexture, i * 50, 300, false));
		}
		board.push_back(siodmyRzad);

		for (int i = 0; i < sizeOfBoard; i++) {
			osmyRzad.push_back(new Pole(&grassTexture, i * 50, 350, false));
		}
		board.push_back(osmyRzad);
		break;
	default:
		break;
	}
}
void Terrarium::changeDirection(moveType newMove) {
	moveDirection = newMove;
}
void Terrarium::extendSnake() {
	snakeLenght++;
	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{
				if (board[i][j]->snakeWeight > 0)
					board[i][j]->snakeWeight++;
		}
	}
}
void Terrarium::generateFruit()
{
	//generuje owoc w losowym i wolnym miejscu na mapie
	std::random_device dev;
	std::mt19937 generator(dev());
	std::uniform_int_distribution<> dist(0, sizeOfBoard - 1);
	int x,y;
	do {
		x = dist(generator);
		y = dist(generator);
	} while (board[x][y]->isEmpty==false&& board[x][y]->isFruit==false);
	board[x][y]->isFruit = true;
	board[x][y]->setSprite(&fruitTexture);
}

void Terrarium::restartGame()
{
	setUpInitialState();
	setUpTiles();
}

void Terrarium::saveScoreToFile(std::string nameOfFile)
{
	std::ofstream plik(nameOfFile, std::ios::app);
	if (!plik.is_open())
		return;
	plik << "Score: "<<snakeLenght<<std::endl;
	plik.close();
}

void Terrarium::updateGameState(sf::RenderWindow &window, sf::Clock &gameClock, sf::Clock &fruitClock)
{
	for (int i = 0; i < sizeOfBoard; i++) {
		for (int j = 0; j < sizeOfBoard; j++) {
			window.draw(board[i][j]->sprite);
		}
	}
	if (!isEnd) {
		if (gameClock.getElapsedTime() >= sf::milliseconds(200)) {
			scoreText.setString(std::to_string(snakeLenght));
			move();
			gameClock.restart();
		}
		if (fruitClock.getElapsedTime() >= sf::seconds(3)) {
			generateFruit();
			fruitClock.restart();
		}
	}
	/*else {
		sf::sleep(sf::milliseconds(1000));
		restartGame();
	}*/

	window.draw(scoreText);
}

int Terrarium::getSizeOfBoard()
{
	return sizeOfBoard;
}

Terrarium::moveType Terrarium::getMoveDirection()
{
	return moveDirection;
}

void Terrarium::move() {
	//std::cout << "X = " << headPos.x << std::endl;
	//std::cout << "Y = " << headPos.y << std::endl;
	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{
			if (board[i][j]->snakeWeight == 1) {
				board[i][j]->setSprite(&grassTexture);
				board[i][j]->isEmpty = true;
				board[i][j]->snakeWeight= 0;
			}else
			if (board[i][j]->snakeWeight > 1)
				board[i][j]->snakeWeight--;
		}
	}
	if(snakeLenght>1)
		board[headPos.x][headPos.y]->setSprite(&bodyTexture);
	switch (moveDirection)
	{
	case Terrarium::moveType::up:
		if (headPos.x-1 < 0)
			headPos.x = sizeOfBoard - 1;
		else {
			if (board[headPos.x - 1][headPos.y]->isEmpty == true) {
				headPos.x--;
			}
			else
				endGame();
		}
		break;
	case Terrarium::moveType::down:
		if (headPos.x+1 >= sizeOfBoard)
			headPos.x = 0;
		else {
			if (board[headPos.x + 1][headPos.y]->isEmpty == true)
				headPos.x++;
			else
				endGame();
		}
		break;
	case Terrarium::moveType::right:
		if (headPos.y+1 >= sizeOfBoard)
			headPos.y = 0;
		else {
			if (board[headPos.x][headPos.y + 1]->isEmpty == true) {
				headPos.y++;
			}
			else
				endGame();
		}
		break;
	case Terrarium::moveType::left:
		if (headPos.y-1 < 0)
			headPos.y = sizeOfBoard - 1;
		else {
			if (board[headPos.x][headPos.y - 1]->isEmpty == true)
				headPos.y--;
			else
				endGame();
		}
		break;
	default:
		break;
	}
	if (board[headPos.x][headPos.y]->isFruit) {
		extendSnake();
		board[headPos.x][headPos.y]->isFruit = false;
	}
	board[headPos.x][headPos.y]->snakeWeight = snakeLenght;
	board[headPos.x][headPos.y]->isEmpty=false;
	board[headPos.x][headPos.y]->setSprite(&headTexture);
}
void Terrarium::endGame(){
	isEnd = true;
	std::cout << "Game over!" << std::endl;
	std::cout << "Your score: " << snakeLenght << std::endl;
	scoreText.setString("Game over!\nYour score: " + std::to_string(snakeLenght));
	scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2));
	scoreText.setPosition(sf::Vector2f(sizeOfBoard * 50 / 2, sizeOfBoard * 50 / 2));
	saveScoreToFile("scoreboard.txt");
	
}