#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "../include/menu.h"
#include <iostream>

int main()//przetwarza sterowanie użytkownika, renderuje okno, tworzy obiekt gry
{
    Menu menu(60);
    menu.loop();
    return 0;
}