#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "terrarium.h"
#include <iostream>
int main()
{
    Terrarium terrarium = Terrarium(Terrarium::mapType::pusta);
    int windowWidth= terrarium.rozmiarPlanszy * 50, windowHeight= terrarium.rozmiarPlanszy * 50;

    sf::Font arial;
    if (!arial.loadFromFile("C:/Windows/Fonts/Arial.ttf"))
        std::cout << "Nie udalo sie wczytaæ czcionki\n";
    sf::Text score;
    score.setFont(arial);
    score.setPosition(sf::Vector2f(350, 0));

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
                break;
            default:
                break;
            }
        }
        window.clear();
        for (int i = 0; i < terrarium.rozmiarPlanszy; i++) {
            for (int j = 0; j < terrarium.rozmiarPlanszy; j++) {
                window.draw(terrarium.plansza[i][j]->sprite);
            }
        }
        if (!terrarium.isEnd) {
            if (gameClock.getElapsedTime() >= sf::milliseconds(150)) {
                terrarium.move();
                gameClock.restart();
                score.setString(std::to_string(terrarium.snakeLenght));
            }
        }
        else {
            std::cout << "Koniec gry!" << std::endl;
            std::cout << "Twoj wynik to " <<terrarium.snakeLenght<< std::endl;
            score.setString("Koniec gry!\nTwoj wynik to " + std::to_string(terrarium.snakeLenght));
            score.setOrigin(sf::Vector2f(score.getGlobalBounds().width/2,score.getGlobalBounds().height/2));
            score.setPosition(sf::Vector2f(windowWidth/2, windowHeight/2));
            
            window.draw(score);
            window.display();
            sf::sleep(sf::milliseconds(5000));
            window.close();
            return 0;
        }

        if (fruitClock.getElapsedTime() >= sf::seconds(3)) {
            terrarium.generateFruit();
            fruitClock.restart();
        }

        
       
        
        window.draw(score);
        window.display();
    }
    return 0;
}