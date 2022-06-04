#include "button.h"
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "terrarium.h"
#pragma once
class Menu
{
	bool isEnd = true;
	unsigned int fps = 60;
public:
	void loop();
	Menu(unsigned int);

};

