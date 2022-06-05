#include "../include/terrarium.h"

Terrarium::Terrarium(mapType newMapType) :sizeOfBoard(8){
	typeOfMap = newMapType;
	
	setUpInitialState();
	initializeFonts();
	if(prepareTextures())
		setUpTiles(); //setup tiles only when textures are loaded
	
}
bool Terrarium::prepareTextures()
{
	if (
		readTexture("media/textures/head.png", headTexture) &&
		readTexture("media/textures/snake.png", bodyTexture) &&
		readTexture("media/textures/trawa.png", grassTexture) &&
		readTexture("media/textures/owoc.png", fruitTexture) &&
		readTexture("media/textures/wall.png", wallTexture)
		)
		return true;

	else {
		std::cout << "Failed to read textures";
	return false;
}
}
bool Terrarium::initializeFonts()
{
	if (!arial.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
		std::cout << "Can't load font arial\n";
		return false;
	}
	return true;
}
bool Terrarium::readTexture(std::string name, sf::Texture &texture)
{
	if (!texture.loadFromFile(name)) {
		std::cout << "Loading texture error" <<name<< std::endl;
		return false;
	}
	texture.setSmooth(true);
	return true;
}
void Terrarium::setUpInitialState() {
	isEnd = false;
	headPos = sf::Vector2i(3,3);
	moveDirection = moveType::right;
	snakeLenght = 1;

	//setting up score display
	scoreText.setFont(arial);
	scoreText.setPosition(sf::Vector2f(sizeOfBoard * 50 - 40, 0));
	scoreText.setOrigin(sf::Vector2f(0,0));
	scoreText.setFillColor(sf::Color(0, 0, 0, 255));
	scoreText.setOutlineColor(sf::Color(255, 255, 255, 255));
	scoreText.setOutlineThickness(3);
}
void Terrarium::setUpTiles() {
	board.clear();
	
	switch (typeOfMap)
	{
	case Terrarium::mapType::borders://sets borders layout to board tiles
	{
		for (int i = 0; i < sizeOfBoard; i++) {
			firstRow.emplace_back(wallTexture, i * 50, 0, true);
		}
		board.push_back(firstRow);

		secondRow.emplace_back(wallTexture, 0, 50, true);
		for (int i = 1; i < sizeOfBoard - 1; i++) {
			secondRow.emplace_back(grassTexture, i * 50, 50, false);
		}
		secondRow.emplace_back(wallTexture, sizeOfBoard * 50 - 50, 50, true);
		board.push_back(secondRow);
		thirdRow.emplace_back(wallTexture, 0, 100, true);
		for (int i = 1; i < sizeOfBoard - 1; i++) {
			thirdRow.emplace_back(grassTexture, i * 50, 100, false);
		}
		thirdRow.emplace_back(wallTexture, sizeOfBoard * 50 - 50, 100, true);
		board.push_back(thirdRow);
		fourthRow.emplace_back(wallTexture, 0, 150, true);
		for (int i = 1; i < sizeOfBoard - 1; i++) {
			fourthRow.emplace_back(grassTexture, i * 50, 150, false);
		}
		fourthRow.emplace_back(wallTexture, sizeOfBoard * 50 - 50, 150, true);
		board.push_back(fourthRow);
		fifthRow.emplace_back(wallTexture, 0, 200, true);
		for (int i = 1; i < sizeOfBoard - 1; i++) {
			fifthRow.emplace_back(grassTexture, i * 50, 200, false);
		}
		fifthRow.emplace_back(wallTexture, sizeOfBoard * 50 - 50, 200, true);
		board.push_back(fifthRow);
		sixthRow.emplace_back(wallTexture, 0, 250, true);
		for (int i = 1; i < sizeOfBoard - 1; i++) {
			sixthRow.emplace_back(grassTexture, i * 50, 250, false);
		}
		sixthRow.emplace_back(wallTexture, sizeOfBoard * 50 - 50, 250, true);
		board.push_back(sixthRow);

		seventhRow.emplace_back(wallTexture, 0, 300, true);
		for (int i = 1; i < sizeOfBoard - 1; i++) {
			seventhRow.emplace_back(grassTexture, i * 50, 300, false);
		}
		seventhRow.emplace_back(wallTexture, sizeOfBoard * 50 - 50, 300, true);
		board.push_back(seventhRow);

		for (int i = 0; i < sizeOfBoard; i++) {
			eighthRow.emplace_back(wallTexture, i * 50, 350, true);
		}
		board.push_back(eighthRow);
	}
		break;
	case Terrarium::mapType::empty://sets empty layout to board tiles
	{
		for (int i = 0; i < sizeOfBoard; i++) {
			firstRow.emplace_back(grassTexture, i * 50, 0, false);
		}
		board.push_back(firstRow);
		for (int i = 0; i < sizeOfBoard; i++) {
			secondRow.emplace_back(grassTexture, i * 50, 50, false);
		}
		board.push_back(secondRow);
		for (int i = 0; i < sizeOfBoard; i++) {
			thirdRow.emplace_back(grassTexture, i * 50, 100, false);
		}
		board.push_back(thirdRow);

		for (int i = 0; i < sizeOfBoard; i++) {
			fourthRow.emplace_back(grassTexture, i * 50, 150, false);
		}
		board.push_back(fourthRow);

		for (int i = 0; i < sizeOfBoard; i++) {
			fifthRow.emplace_back(grassTexture, i * 50, 200, false);
		}
		board.push_back(fifthRow);

		for (int i = 0; i < sizeOfBoard; i++) {
			sixthRow.emplace_back(grassTexture, i * 50, 250, false);
		}
		board.push_back(sixthRow);


		for (int i = 0; i < sizeOfBoard; i++) {
			seventhRow.emplace_back(grassTexture, i * 50, 300, false);
		}
		board.push_back(seventhRow);

		for (int i = 0; i < sizeOfBoard; i++) {
			eighthRow.emplace_back(grassTexture, i * 50, 350, false);
		}
		board.push_back(eighthRow);
	}
		break;
	case Terrarium::mapType::maze://sets maze layout to board tiles
	{moveDirection = moveType::down;
		firstRow.emplace_back(grassTexture, 0, 0, false);
		firstRow.emplace_back(grassTexture, 50, 0, false);
		firstRow.emplace_back(grassTexture, 100, 0, false);
		firstRow.emplace_back(grassTexture, 150, 0, false);
		firstRow.emplace_back(wallTexture, 200, 0, true);
		firstRow.emplace_back(grassTexture, 250, 0, false);
		firstRow.emplace_back(grassTexture, 300, 0, false);
		firstRow.emplace_back(grassTexture, 350, 0, false);
		board.push_back(firstRow);

		secondRow.emplace_back(grassTexture, 0, 50, false);
		secondRow.emplace_back(grassTexture, 50, 50, false);
		secondRow.emplace_back(grassTexture, 100, 50, false);
		secondRow.emplace_back(grassTexture, 150, 50, false);
		secondRow.emplace_back(wallTexture, 200, 50, true);
		secondRow.emplace_back(grassTexture, 250, 50, false);
		secondRow.emplace_back(grassTexture, 300, 50, false);
		secondRow.emplace_back(grassTexture, 350, 50, false);
		board.push_back(secondRow);

		thirdRow.emplace_back(grassTexture, 0, 100, false);
		thirdRow.emplace_back(grassTexture, 50, 100, false);
		thirdRow.emplace_back(grassTexture, 100, 100, false);
		thirdRow.emplace_back(grassTexture, 150, 100, false);
		thirdRow.emplace_back(wallTexture, 200, 100, true);
		thirdRow.emplace_back(grassTexture, 250, 100, false);
		thirdRow.emplace_back(grassTexture, 300, 100, false);
		thirdRow.emplace_back(grassTexture, 350, 100, false);
		board.push_back(thirdRow);

		fourthRow.emplace_back(grassTexture, 0, 150, false);
		fourthRow.emplace_back(grassTexture, 50, 150, false);
		fourthRow.emplace_back(grassTexture, 100, 150, false);
		fourthRow.emplace_back(grassTexture, 150, 150, false);
		fourthRow.emplace_back(wallTexture, 200, 150, true);
		fourthRow.emplace_back(grassTexture, 250, 150, false);
		fourthRow.emplace_back(grassTexture, 300, 150, false);
		fourthRow.emplace_back(grassTexture, 350, 150, false);
		board.push_back(fourthRow);

		fifthRow.emplace_back(grassTexture, 0, 200, false);
		fifthRow.emplace_back(grassTexture, 50, 200, false);
		fifthRow.emplace_back(grassTexture, 100, 200, false);
		fifthRow.emplace_back(grassTexture, 150, 200, false);
		fifthRow.emplace_back(wallTexture, 200, 200, true);
		fifthRow.emplace_back(wallTexture, 250, 200, true);
		fifthRow.emplace_back(wallTexture, 300, 200, true);
		fifthRow.emplace_back(wallTexture, 350, 200, true);
		board.push_back(fifthRow);

		for (int i = 0; i < sizeOfBoard; i++) {
			sixthRow.emplace_back(grassTexture, i * 50, 250, false);
		}
		board.push_back(sixthRow);


		for (int i = 0; i < sizeOfBoard; i++) {
			seventhRow.emplace_back(grassTexture, i * 50, 300, false);
		}
		board.push_back(seventhRow);

		for (int i = 0; i < sizeOfBoard; i++) {
			eighthRow.emplace_back(grassTexture, i * 50, 350, false);
		}
		board.push_back(eighthRow);
	}
		break;
	default:
		break;
	}
}
void Terrarium::changeDirection(moveType newMove) {
	moveDirection = newMove;
}
void Terrarium::extendSnake() {//extend snake by 1
	snakeLenght++;
	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{
				if (board[i][j].snakeWeight > 0)
					board[i][j].snakeWeight++;
		}
	}
}
void Terrarium::generateFruit()
{
	//places fruit on random tile
	std::random_device dev;
	std::mt19937 generator(dev());
	std::uniform_int_distribution<> dist(0, sizeOfBoard - 1);
	int x,y;
	do {
		x = dist(generator);
		y = dist(generator);
	} while (board[x][y].isEmpty==false && board[x][y].isFruit==false);
	board[x][y].isFruit = true;
	board[x][y].setSprite(fruitTexture);
}



void Terrarium::saveScoreToFile(std::string nameOfFile)
{
	std::ofstream plik(nameOfFile, std::ios::app);
	if (!plik.is_open())
		return;
	plik << "Score: "<<snakeLenght<<std::endl;
	plik.close();
}

void Terrarium::updateGameState(sf::RenderWindow &window,
	sf::Clock &gameClock, sf::Clock &fruitClock)
{

	//draw entire board
	for (int i = 0; i < sizeOfBoard; i++) {
		for (int j = 0; j < sizeOfBoard; j++) {
			window.draw(board[i][j].sprite);
		}
	}

	if (!isEnd) {
		//gameClock ensures every next move has an interval 
		if (gameClock.getElapsedTime() >= sf::milliseconds(moveInterval)) {
			scoreText.setString(std::to_string(snakeLenght));
			move();
			gameClock.restart();
		}
		if (fruitClock.getElapsedTime() >= sf::seconds(fruitInterval)) {
			generateFruit();
			fruitClock.restart();
		}
	}
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
	//std::cout << "X = " << headPos.x;
	//std::cout << ", Y = " << headPos.y << std::endl;
	
	//update tiles with approciate sprites and atributes
	for (int i = 0; i < sizeOfBoard; i++)
	{
		for (int j = 0; j < sizeOfBoard; j++)
		{
			if (board[i][j].snakeWeight == 1) {//empty tile when snake exits it
				board[i][j].setSprite(grassTexture);
				board[i][j].isEmpty = true;
				board[i][j].snakeWeight= 0;
			}else
			if (board[i][j].snakeWeight > 1)
				board[i][j].snakeWeight--;
		}
	}

	if(snakeLenght>1)
		board[headPos.x][headPos.y].setSprite(bodyTexture);


	//when at edge of board, snake teleports to opposite side
	switch (moveDirection)
	{
	case Terrarium::moveType::up:
		if (headPos.x-1 < 0)
			headPos.x = sizeOfBoard - 1;
		else {
			if (board[headPos.x - 1][headPos.y].isEmpty == true) {
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
			if (board[headPos.x + 1][headPos.y].isEmpty == true)
				headPos.x++;
			else
				endGame();
		}
		break;
	case Terrarium::moveType::right:
		if (headPos.y+1 >= sizeOfBoard)
			headPos.y = 0;
		else {
			if (board[headPos.x][headPos.y + 1].isEmpty == true) {
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
			if (board[headPos.x][headPos.y - 1].isEmpty == true)
				headPos.y--;
			else
				endGame();
		}
		break;
	default:
		break;
	}
	//tile with fruit extends snake
	if (board[headPos.x][headPos.y].isFruit) {
		extendSnake();
		board[headPos.x][headPos.y].isFruit = false;
	}

	board[headPos.x][headPos.y].snakeWeight = snakeLenght;
	board[headPos.x][headPos.y].isEmpty = false;
	board[headPos.x][headPos.y].setSprite(headTexture);
}
void Terrarium::endGame(){
	isEnd = true;
	std::cout << "Game over!" << std::endl;
	std::cout << "Your score: " << snakeLenght << std::endl;

	//game over message
	scoreText.setString("Game over!\nYour score: " + std::to_string(snakeLenght));
	scoreText.setOrigin(sf::Vector2f(scoreText.getGlobalBounds().width / 2,
		scoreText.getGlobalBounds().height / 2));
	scoreText.setPosition(sf::Vector2f(sizeOfBoard * 50 / 2, sizeOfBoard * 50 / 2));
	saveScoreToFile("scoreboard.txt");
	
}