#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "terrarium.h"
#include <iostream>
int main()
{
    sf::Clock clock;
    sf::CircleShape shape(10);
    Terrarium terrarium = Terrarium(Terrarium::mapType::pusta);
    sf::Vector2f pos{};
    sf::RenderWindow window(
        sf::VideoMode(terrarium.rozmiarPlanszy*50, terrarium.rozmiarPlanszy * 50),
        "Snake");
    unsigned int fps = 5;
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
                break;
            default:
                break;
            }
        }
        window.clear();
        if (clock.getElapsedTime() >= sf::seconds(3)) {
            terrarium.generateFruit();
            clock.restart();
        }
        if (!terrarium.isEnd)
            terrarium.move();
        else {
            std::cout << "Koniec gry!" << std::endl;
            std::cout << "Twoj wynik to " <<terrarium.snakeLenght<< std::endl;
            window.close();
            system("Pause");
        }
        
        for (int i = 0; i < terrarium.rozmiarPlanszy; i++) {
            for (int j = 0; j < terrarium.rozmiarPlanszy; j++) {
                window.draw(terrarium.plansza[i][j]->sprite);
            }
        }
        window.display();
    }
    return 0;
}