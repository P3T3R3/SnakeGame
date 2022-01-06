#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "terrarium.h"
#include <iostream>
int main()
{
    Terrarium terrarium = Terrarium(Terrarium::mapType::pusta); 
    //obiekt ktory zajmuje sie logik¹ i wyœwietlaniem gry
    int windowWidth= terrarium.rozmiarPlanszy * 50,
        windowHeight= terrarium.rozmiarPlanszy * 50;
    sf::Clock fruitClock, gameClock; //zegary gry
    sf::RenderWindow window(
        sf::VideoMode(windowWidth, windowHeight),
        "Snake");
    unsigned int fps = 60;
    window.setFramerateLimit(fps);
    while (window.isOpen())
    {
        sf::Event event;
        while (
            window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Up:
                    if(terrarium.typRuchu!= Terrarium::moveType::down)
                    terrarium.changeDirection(Terrarium::moveType::up);
                    break;
                case sf::Keyboard::Down:
                    if (terrarium.typRuchu != Terrarium::moveType::up)
                    terrarium.changeDirection(Terrarium::moveType::down);
                    break;
                case sf::Keyboard::Right:
                    if (terrarium.typRuchu != Terrarium::moveType::left)
                    terrarium.changeDirection(Terrarium::moveType::right);
                    break;
                case sf::Keyboard::Left:
                    if (terrarium.typRuchu != Terrarium::moveType::right)
                    terrarium.changeDirection(Terrarium::moveType::left);
                    break;
                }
                //zmiana kierunku poruszania siê wê¿a
                //niedozwolona jest zmiana kierunku o 180 stopni
                break;
            default:
                break;
            }
        }
        window.clear();
        terrarium.updateGameState(&window,&gameClock,&fruitClock);
        window.display();
    }
    return 0;
}