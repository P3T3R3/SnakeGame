#include "terrarium.h"
#include <iostream>
#include <random>
Terrarium::Terrarium(mapType typMapy) {
	typMapy = typMapy;
	rozmiarPlanszy = 8;
	setUpInitialState();
	setUpTiles(); 
	isEnd = false;
	typRuchu = moveType::right;
	snakeLenght = 5;
}
void Terrarium::prepareTextures()
{
	
}
bool Terrarium::readTexture(std::string name, sf::Texture *texture)
{
	if (!texture->loadFromFile(name)) {
		std::cout << "Blad ladowania textury" << std::endl;
		return false;
	}
	texture->setSmooth(true);
	return true;
}
void Terrarium::setUpInitialState() {
	tailPos = headPos = sf::Vector2i(3,3);
}
void Terrarium::setUpTiles() {
	plansza.clear();
	std::vector<Pole*> pierwszyRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		pierwszyRzad.push_back(new Pole("media/textures/trawa.jpg", i*50, 0, false));
	}
	plansza.push_back(pierwszyRzad);

	std::vector<Pole*> drugiRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		drugiRzad.push_back(new Pole("media/textures/trawa.jpg", i * 50, 50, false));
	}
	plansza.push_back(drugiRzad);

	std::vector<Pole*> trzeciRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		trzeciRzad.push_back(new Pole("media/textures/trawa.jpg", i * 50, 100, false));
	}
	plansza.push_back(trzeciRzad);

	std::vector<Pole*> czwartyRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		czwartyRzad.push_back(new Pole("media/textures/trawa.jpg", i * 50, 150, false));
	}
	plansza.push_back(czwartyRzad);

	std::vector<Pole*> piatyRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		piatyRzad.push_back(new Pole("media/textures/trawa.jpg", i * 50, 200, false));
	}
	plansza.push_back(piatyRzad);

	std::vector<Pole*> szostyRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		szostyRzad.push_back(new Pole("media/textures/trawa.jpg", i * 50, 250, false));
	}
	plansza.push_back(szostyRzad);

	std::vector<Pole*> siodmyRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		siodmyRzad.push_back(new Pole("media/textures/trawa.jpg", i * 50, 300, false));
	}
	plansza.push_back(siodmyRzad);

	std::vector<Pole*> osmyRzad;
	for (int i = 0; i < rozmiarPlanszy; i++) {
		osmyRzad.push_back(new Pole("media/textures/trawa.jpg", i * 50, 350, false));
	}
	plansza.push_back(osmyRzad);
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
int Terrarium::generateRandomNumber()
{
	int a, b;
	std::random_device dev;
	std::mt19937 generator(dev());
	std::uniform_int_distribution<> dist(0, rozmiarPlanszy - 1);
	return dist(generator);
}
void Terrarium::generateFruit()
{
	int x,y;
	do {
		x = generateRandomNumber();
		y = generateRandomNumber();
	} while (plansza[x][y]->isEmpty==false&& plansza[x][y]->isFruit==false);
	plansza[x][y]->isFruit = true;
	plansza[x][y]->setSprite("media/textures/owoc.png");
}

void Terrarium::move() {
	//std::cout << "X = " << headPos.x << std::endl;
	//std::cout << "Y = " << headPos.y << std::endl;
	for (int i = 0; i < rozmiarPlanszy; i++)
	{
		for (int j = 0; j < rozmiarPlanszy; j++)
		{
			if (plansza[i][j]->snakeWeight == 1) {
				plansza[i][j]->setSprite("media/textures/trawa.jpg");
				plansza[i][j]->isEmpty = true;
				plansza[i][j]->snakeWeight= 0;
			}else
			if (plansza[i][j]->snakeWeight > 1)
				plansza[i][j]->snakeWeight--;
		}
	}
	plansza[headPos.x][headPos.y]->setSprite("media/textures/snake.png");
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
	plansza[headPos.x][headPos.y]->setSprite("media/textures/head.png");
}
void Terrarium::endGame(){
	//plansza.clear();
	isEnd = true;
}