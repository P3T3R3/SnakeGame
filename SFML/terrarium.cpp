#include "terrarium.h"
#include <iostream>
#include <random>
Terrarium::Terrarium(mapType rodzajMapy) {
	typMapy = rodzajMapy;
	setUpInitialState();
	rozmiarPlanszy = 8;
	initializeFonts();
	scoreText.setFont(arial);
	scoreText.setPosition(sf::Vector2f(rozmiarPlanszy*50 - 40, 0));
	scoreText.setFillColor(sf::Color(0, 0, 0, 255));
	prepareTextures();
	setUpTiles(); 
	
}
bool Terrarium::prepareTextures()
{
	if (
		readTexture("media/textures/head.png", &headTexture) &&
		readTexture("media/textures/snake.png", &bodyTexture) &&
		readTexture("media/textures/trawa.png", &grassTexture) &&
		readTexture("media/textures/owoc.png", &fruitTexture)
		)
		return true;
	else
		return false;
}
bool Terrarium::initializeFonts()
{
	if (!arial.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
		std::cout << "Nie udalo sie wczytaæ czcionki\n";
		return false;
	}
	return true;
}
bool Terrarium::readTexture(std::string name, sf::Texture *texture)
{
	if (!texture->loadFromFile(name)) {
		std::cout << "Blad ladowania textury " <<name<< std::endl;
		return false;
	}
	texture->setSmooth(true);
	return true;
}
void Terrarium::setUpInitialState() {
	isEnd = false;
	headPos = sf::Vector2i(3,3);
	typRuchu = moveType::right;
	snakeLenght = 1;
}
void Terrarium::setUpTiles() {
	plansza.clear();
	std::vector<Pole*> pierwszyRzad, drugiRzad, trzeciRzad, czwartyRzad, piatyRzad, szostyRzad, siodmyRzad, osmyRzad;;
	switch (typMapy)
	{
	case Terrarium::mapType::pusta:
		for (int i = 0; i < rozmiarPlanszy; i++) {
			pierwszyRzad.push_back(new Pole(&grassTexture, i * 50, 0, false));
		}
		plansza.push_back(pierwszyRzad);
		for (int i = 0; i < rozmiarPlanszy; i++) {
			drugiRzad.push_back(new Pole(&grassTexture, i * 50, 50, false));
		}
		plansza.push_back(drugiRzad);
		for (int i = 0; i < rozmiarPlanszy; i++) {
			trzeciRzad.push_back(new Pole(&grassTexture, i * 50, 100, false));
		}
		plansza.push_back(trzeciRzad);
	
		for (int i = 0; i < rozmiarPlanszy; i++) {
			czwartyRzad.push_back(new Pole(&grassTexture, i * 50, 150, false));
		}
		plansza.push_back(czwartyRzad);
		
		for (int i = 0; i < rozmiarPlanszy; i++) {
			piatyRzad.push_back(new Pole(&grassTexture, i * 50, 200, false));
		}
		plansza.push_back(piatyRzad);
		
		for (int i = 0; i < rozmiarPlanszy; i++) {
			szostyRzad.push_back(new Pole(&grassTexture, i * 50, 250, false));
		}
		plansza.push_back(szostyRzad);

		
		for (int i = 0; i < rozmiarPlanszy; i++) {
			siodmyRzad.push_back(new Pole(&grassTexture, i * 50, 300, false));
		}
		plansza.push_back(siodmyRzad);

		for (int i = 0; i < rozmiarPlanszy; i++) {
			osmyRzad.push_back(new Pole(&grassTexture, i * 50, 350, false));
		}
		plansza.push_back(osmyRzad);
		break;
	case Terrarium::mapType::krzyz:
		break;
	case Terrarium::mapType::labirynt:
		break;
	default:
		break;
	}
}
void Terrarium::changeDirection(moveType nowyRuch) {
	typRuchu = nowyRuch;
}
void Terrarium::extendSnake() {
	snakeLenght++;
	for (int i = 0; i < rozmiarPlanszy; i++)
	{
		for (int j = 0; j < rozmiarPlanszy; j++)
		{
				if (plansza[i][j]->snakeWeight > 0)
					plansza[i][j]->snakeWeight++;
		}
	}
}
void Terrarium::generateFruit()
{
	std::random_device dev;
	std::mt19937 generator(dev());
	std::uniform_int_distribution<> dist(0, rozmiarPlanszy - 1);
	int x,y;
	do {
		x = dist(generator);
		y = dist(generator);
	} while (plansza[x][y]->isEmpty==false&& plansza[x][y]->isFruit==false);
	plansza[x][y]->isFruit = true;
	plansza[x][y]->setSprite(&fruitTexture);
}

void Terrarium::updateGameState(sf::RenderWindow *window, sf::Clock *gameClock, sf::Clock * fruitClock)
{
	for (int i = 0; i < rozmiarPlanszy; i++) {
		for (int j = 0; j < rozmiarPlanszy; j++) {
			window->draw(plansza[i][j]->sprite);
		}
	}
	if (!isEnd) {
		if (gameClock->getElapsedTime() >= sf::milliseconds(150)) {
			move();
			gameClock->restart();
			scoreText.setString(std::to_string(snakeLenght));
		}
	}
	else {
		std::cout << "Koniec gry!" << std::endl;
		std::cout << "Twoj wynik to " << snakeLenght << std::endl;
		scoreText.setString("Koniec gry!\nTwoj wynik to " + std::to_string(snakeLenght));
		scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2));
		scoreText.setPosition(sf::Vector2f(rozmiarPlanszy*50 / 2, rozmiarPlanszy*50 / 2));

		window->draw(scoreText);
		window->display();
		window->close();
	}

	if (fruitClock->getElapsedTime() >= sf::seconds(3)) {
		generateFruit();
		fruitClock->restart();
	}

	window->draw(scoreText);
}

void Terrarium::move() {
	//std::cout << "X = " << headPos.x << std::endl;
	//std::cout << "Y = " << headPos.y << std::endl;
	for (int i = 0; i < rozmiarPlanszy; i++)
	{
		for (int j = 0; j < rozmiarPlanszy; j++)
		{
			if (plansza[i][j]->snakeWeight == 1) {
				plansza[i][j]->setSprite(&grassTexture);
				plansza[i][j]->isEmpty = true;
				plansza[i][j]->snakeWeight= 0;
			}else
			if (plansza[i][j]->snakeWeight > 1)
				plansza[i][j]->snakeWeight--;
		}
	}
	if(snakeLenght>1)
		plansza[headPos.x][headPos.y]->setSprite(&bodyTexture);
	switch (typRuchu)
	{
	case Terrarium::moveType::up:
		if (headPos.x-1 < 0)
			headPos.x = rozmiarPlanszy - 1;
		else {
			if (plansza[headPos.x - 1][headPos.y]->isEmpty == true) {
				headPos.x--;
			}
			else
				endGame();
		}
		break;
	case Terrarium::moveType::down:
		if (headPos.x+1 >= rozmiarPlanszy)
			headPos.x = 0;
		else {
			if (plansza[headPos.x + 1][headPos.y]->isEmpty == true)
				headPos.x++;
			else
				endGame();
		}
		break;
	case Terrarium::moveType::right:
		if (headPos.y+1 >= rozmiarPlanszy)
			headPos.y = 0;
		else {
			if (plansza[headPos.x][headPos.y + 1]->isEmpty == true) {
				headPos.y++;
			}
			else
				endGame();
		}
		break;
	case Terrarium::moveType::left:
		if (headPos.y-1 < 0)
			headPos.y = rozmiarPlanszy - 1;
		else {
			if (plansza[headPos.x][headPos.y - 1]->isEmpty == true)
				headPos.y--;
			else
				endGame();
		}
		break;
	default:
		break;
	}
	if (plansza[headPos.x][headPos.y]->isFruit) {
		extendSnake();
		plansza[headPos.x][headPos.y]->isFruit = false;
	}
	plansza[headPos.x][headPos.y]->snakeWeight = snakeLenght;
	plansza[headPos.x][headPos.y]->isEmpty=false;
	plansza[headPos.x][headPos.y]->setSprite(&headTexture);
}
void Terrarium::endGame(){
	//plansza.clear();
	isEnd = true;
}