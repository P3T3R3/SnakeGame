#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "terrarium.h"
#include <iostream>
struct Button {
    sf::Vector2f position;
    sf::Vector2f size;
    std::string name;
    sf::Text text;
    sf::RectangleShape shape;
    sf::Font arial;
    Button(sf::Vector2f position_, sf::Vector2f size_, std::string name_) {
        position = position_;
        size = size_;
        name = name_;
        if (!initializeFonts())
            return;

        text.setFont(arial);
        text.setString(name);
        text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2,
            text.getGlobalBounds().height / 2+10));
        text.setPosition(position);
        shape.setSize(size);
        shape.setFillColor(sf::Color(100, 200, 100, 255));
        shape.setOrigin(sf::Vector2f(shape.getGlobalBounds().width / 2,
            shape.getGlobalBounds().height / 2));
        shape.setPosition(position);
    }
    bool initializeFonts() {
        if (!arial.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
            std::cout << "Can't load font arial\n";
            return false;
        }
        return true;
    }
    bool isClicked(sf::Vector2i localPosition) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (shape.getGlobalBounds().contains(sf::Vector2f(localPosition))) {
                return true;
            }
        }
        return false;
    }
    void setString(std::string newName) {
        text.setString(newName);
        text.setOrigin(sf::Vector2f(text.getGlobalBounds().width / 2,
        text.getGlobalBounds().height / 2 + 10));
    }

};
int main()//przetwarza sterowanie u¿ytkownika, renderuje okno, tworzy obiekt gry
{

    bool isEnd=true;
    while (isEnd) {
        Terrarium::mapType selectedMapType = Terrarium::mapType::empty;
        sf::RenderWindow menu(sf::VideoMode(400, 400), "Menu");
        menu.setFramerateLimit(60);
        bool isGameStarted = false;
        Button startButton(sf::Vector2f(200, 150), sf::Vector2f(140.f, 50.f), "Start");
        Button mapTypeButton(sf::Vector2f(200, 225), sf::Vector2f(140.f, 50.f), "Empty");
        Button quitButton(sf::Vector2f(200, 350), sf::Vector2f(140.f, 50.f), "Exit");
        sf::Text gameName;
        gameName.setFont(startButton.arial);
        gameName.setCharacterSize(50);
        gameName.setFillColor(sf::Color(20, 255, 30, 255));
        gameName.setString("SNAKE");
        gameName.setStyle(sf::Text::Bold);
        gameName.setPosition(sf::Vector2f(200, 50));
        gameName.setOrigin(sf::Vector2f(gameName.getGlobalBounds().width / 2,
            gameName.getGlobalBounds().height / 2 + 10));
        while (menu.isOpen()) {
            sf::Event event;
            while (
                menu.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    menu.close();
                    break;
                }
                sf::Vector2i localPosition = sf::Mouse::getPosition(menu);
                if (startButton.isClicked(localPosition)) {
                    isGameStarted = true;
                    menu.close();
                }else
                if (mapTypeButton.isClicked(localPosition)) {
                    switch (selectedMapType) {
                    case Terrarium::mapType::empty:
                        selectedMapType = Terrarium::mapType::borders;
                        mapTypeButton.setString("Borders");
                        break;
                    case Terrarium::mapType::borders:
                        selectedMapType = Terrarium::mapType::maze;
                        mapTypeButton.setString("Maze");
                        break;
                    case Terrarium::mapType::maze:
                        selectedMapType = Terrarium::mapType::empty;
                        mapTypeButton.setString("Maze");
                        break;
                    }
                }
                else if (quitButton.isClicked(localPosition)) {
                    isEnd = false;
                    return 0;
                }
            }


            menu.clear();
            menu.draw(gameName);
            menu.draw(startButton.shape);
            menu.draw(startButton.text);
            menu.draw(mapTypeButton.shape);
            menu.draw(mapTypeButton.text);
            menu.draw(quitButton.shape);
            menu.draw(quitButton.text);
            menu.display();
        }

        if (isGameStarted) {

            Terrarium terrarium = Terrarium(selectedMapType);
            //obiekt ktory zajmuje sie logik¹ i wyœwietlaniem gry
            int windowWidth = terrarium.getRozmiarPlanszy() * 50,
                windowHeight = terrarium.getRozmiarPlanszy() * 50;
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
                            if (terrarium.getTypRuchu() != Terrarium::moveType::down)
                                terrarium.changeDirection(Terrarium::moveType::up);
                            break;
                        case sf::Keyboard::Down:
                            if (terrarium.getTypRuchu() != Terrarium::moveType::up)
                                terrarium.changeDirection(Terrarium::moveType::down);
                            break;
                        case sf::Keyboard::Right:
                            if (terrarium.getTypRuchu() != Terrarium::moveType::left)
                                terrarium.changeDirection(Terrarium::moveType::right);
                            break;
                        case sf::Keyboard::Left:
                            if (terrarium.getTypRuchu() != Terrarium::moveType::right)
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
                terrarium.updateGameState(&window, &gameClock, &fruitClock);
                window.display();
            }
        }
    }
    return 0;
}