#include "button.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "terrarium.h"
#pragma once
class GameDisplay
{
	bool isEnd = true;
	unsigned int fps = 60;
public:
	void loop();
	GameDisplay()=default;
	GameDisplay(unsigned int);

};

