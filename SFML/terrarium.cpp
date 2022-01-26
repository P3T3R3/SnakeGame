#include "terrarium.h"
#include <iostream>
#include <random>
Terrarium::Terrarium(mapType rodzajMapy) {
	typMapy = rodzajMapy;
	rozmiarPlanszy = 8;

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
	scoreText.setFont(arial);
	scoreText.setPosition(sf::Vector2f(rozmiarPlanszy * 50 - 40, 0));
	scoreText.setOrigin(sf::Vector2f(0,0));
	scoreText.setFillColor(sf::Color(0, 0, 0, 255));
	scoreText.setOutlineColor(sf::Color(255, 255, 255, 255));
	scoreText.setOutlineThickness(3);
}
void Terrarium::setUpTiles() {
	plansza.clear();
	std::vector<Pole*> pierwszyRzad, drugiRzad, trzeciRzad, czwartyRzad, piatyRzad, szostyRzad, siodmyRzad, osmyRzad;;
	switch (typMapy)
	{
	case Terrarium::mapType::granice:
		for (int i = 0; i < rozmiarPlanszy; i++) {
			pierwszyRzad.push_back(new Pole(&wallTexture, i * 50, 0, true));
		}
		plansza.push_back(pierwszyRzad);

		drugiRzad.push_back(new Pole(&wallTexture,0, 50, true));
		for (int i = 1; i < rozmiarPlanszy-1; i++) {
			drugiRzad.push_back(new Pole(&grassTexture, i * 50, 50, false));
		}
		drugiRzad.push_back(new Pole(&wallTexture, rozmiarPlanszy*50-50, 50, true));
		plansza.push_back(drugiRzad);
		trzeciRzad.push_back(new Pole(&wallTexture, 0, 100, true));
		for (int i = 1; i < rozmiarPlanszy-1; i++) {
			trzeciRzad.push_back(new Pole(&grassTexture, i * 50, 100, false));
		}
		trzeciRzad.push_back(new Pole(&wallTexture, rozmiarPlanszy*50-50, 100, true));
		plansza.push_back(trzeciRzad);
		czwartyRzad.push_back(new Pole(&wallTexture, 0, 150, true));
		for (int i = 1; i < rozmiarPlanszy-1; i++) {
			czwartyRzad.push_back(new Pole(&grassTexture, i * 50, 150, false));
		}
		czwartyRzad.push_back(new Pole(&wallTexture, rozmiarPlanszy*50-50, 150, true));
		plansza.push_back(czwartyRzad);
		piatyRzad.push_back(new Pole(&wallTexture, 0, 200, true));
		for (int i = 1; i < rozmiarPlanszy-1; i++) {
			piatyRzad.push_back(new Pole(&grassTexture, i * 50, 200, false));
		}
		piatyRzad.push_back(new Pole(&wallTexture, rozmiarPlanszy*50-50, 200, true));
		plansza.push_back(piatyRzad);
		szostyRzad.push_back(new Pole(&wallTexture, 0, 250, true));
		for (int i = 1; i < rozmiarPlanszy-1; i++) {
			szostyRzad.push_back(new Pole(&grassTexture, i * 50, 250, false));
		}
		szostyRzad.push_back(new Pole(&wallTexture, rozmiarPlanszy*50-50, 250, true));
		plansza.push_back(szostyRzad);

		siodmyRzad.push_back(new Pole(&wallTexture, 0, 300, true));
		for (int i = 1; i < rozmiarPlanszy-1; i++) {
			siodmyRzad.push_back(new Pole(&grassTexture, i * 50, 300, false));
		}
		siodmyRzad.push_back(new Pole(&wallTexture,rozmiarPlanszy*50-50, 300, true));
		plansza.push_back(siodmyRzad);

		for (int i = 0; i < rozmiarPlanszy; i++) {
			osmyRzad.push_back(new Pole(&wallTexture, i * 50, 350, true));
		}
		plansza.push_back(osmyRzad);
		break;
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
	case Terrarium::mapType::labirynt:
		typRuchu = moveType::down;
		pierwszyRzad.push_back(new Pole(&grassTexture, 0, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 50, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 100, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 150, 0, false));
		pierwszyRzad.push_back(new Pole(&wallTexture, 200, 0, true));
		pierwszyRzad.push_back(new Pole(&grassTexture, 250, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 300, 0, false));
		pierwszyRzad.push_back(new Pole(&grassTexture, 350, 0, false));
		plansza.push_back(pierwszyRzad);

		drugiRzad.push_back(new Pole(&grassTexture, 0, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 50, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 100, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 150, 50, false));
		drugiRzad.push_back(new Pole(&wallTexture, 200, 50, true));
		drugiRzad.push_back(new Pole(&grassTexture, 250, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 300, 50, false));
		drugiRzad.push_back(new Pole(&grassTexture, 350, 50, false));
		plansza.push_back(drugiRzad);
		trzeciRzad.push_back(new Pole(&grassTexture, 0, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 50, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 100, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 150, 100, false));
		trzeciRzad.push_back(new Pole(&wallTexture, 200, 100, true));
		trzeciRzad.push_back(new Pole(&grassTexture, 250, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 300, 100, false));
		trzeciRzad.push_back(new Pole(&grassTexture, 350, 100, false));
		plansza.push_back(trzeciRzad);
		czwartyRzad.push_back(new Pole(&grassTexture, 0, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 50, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 100, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 150, 150, false));
		czwartyRzad.push_back(new Pole(&wallTexture, 200, 150, true));
		czwartyRzad.push_back(new Pole(&grassTexture, 250, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 300, 150, false));
		czwartyRzad.push_back(new Pole(&grassTexture, 350, 150, false));
		plansza.push_back(czwartyRzad);
		piatyRzad.push_back(new Pole(&grassTexture, 0, 200, false));
		piatyRzad.push_back(new Pole(&grassTexture, 50, 200, false));
		piatyRzad.push_back(new Pole(&grassTexture, 100, 200, false));
		piatyRzad.push_back(new Pole(&grassTexture, 150, 200, false));
		piatyRzad.push_back(new Pole(&wallTexture, 200, 200, true));
		piatyRzad.push_back(new Pole(&wallTexture, 250, 200, true));
		piatyRzad.push_back(new Pole(&wallTexture, 300, 200, true));
		piatyRzad.push_back(new Pole(&wallTexture, 350, 200, true));
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
	//generuje owoc w losowym i wolnym miejscu na mapie
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

void Terrarium::restartGame()
{
	setUpInitialState();
	setUpTiles();
}

void Terrarium::zapiszWynikDoPliku(std::string nazwaPliku)
{
	std::ofstream plik(nazwaPliku, std::ios::app);
	if (!plik.is_open())
		return;
	plik << "Wynik: "<<snakeLenght<<std::endl;
	plik.close();
}

void Terrarium::updateGameState(sf::RenderWindow *window, sf::Clock *gameClock, sf::Clock * fruitClock)
{
	/*
	Odpowiada za wyœwietlanie planszy i tempo gry(wywo³uje move(); i generateFruit(); 
	w odpowiednim czasie, ogranicza prêdkoœæ wê¿a i czêstotliwoœæ pojawiania siê owoców).
	Gdy gra siê skoñczy gra jest zamra¿ana.
	*/
	for (int i = 0; i < rozmiarPlanszy; i++) {
		for (int j = 0; j < rozmiarPlanszy; j++) {
			window->draw(plansza[i][j]->sprite);
		}
	}
	if (!isEnd) {
		if (gameClock->getElapsedTime() >= sf::milliseconds(200)) {
			scoreText.setString(std::to_string(snakeLenght));
			move();
			gameClock->restart();
		}
		if (fruitClock->getElapsedTime() >= sf::seconds(3)) {
			generateFruit();
			fruitClock->restart();
		}
	}
	/*else {
		sf::sleep(sf::milliseconds(1000));
		restartGame();
	}*/

	window->draw(scoreText);
}

int Terrarium::getRozmiarPlanszy()
{
	return rozmiarPlanszy;
}

Terrarium::moveType Terrarium::getTypRuchu()
{
	return typRuchu;
}

void Terrarium::move() {

	/*
	Zawiera algorytm, którego zadaniem jest sprawdzanie jak d³ugo poszczególny segment wê¿a pozostanie na danym polu.
	Sprawdza on „wagê” wê¿a, jeœli waga osi¹gnie 1 to dane pole jest resetowane do stanu pustego, a jeœli jest wiêksza od 1 to zostaje pomniejszona o 1. 
	Funkcja sprawdza równie¿ czy w¹¿ nie trafi w zajête pole(swoje cia³o lub œcianê), jeœli nie, to w¹¿ porusza siê na to miejsce, jeœli tak, to gra siê koñczy.
	Nowo zajête pole otrzymuje wagê pola równ¹ d³ugoœci wê¿a, a tekstura jest aktualizowana.Wejœcie wê¿a na owoc zwiêksza jego d³ugoœæ o 1.
	*/
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
	isEnd = true;
	std::cout << "Koniec gry!" << std::endl;
	std::cout << "Twoj wynik to " << snakeLenght << std::endl;
	scoreText.setString("Koniec gry!\nTwoj wynik to " + std::to_string(snakeLenght));
	scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().width / 2, scoreText.getGlobalBounds().height / 2));
	scoreText.setPosition(sf::Vector2f(rozmiarPlanszy * 50 / 2, rozmiarPlanszy * 50 / 2));
	zapiszWynikDoPliku("wyniki.txt");
	
}