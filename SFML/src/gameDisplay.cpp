#include "../include/gameDisplay.h"
GameDisplay::GameDisplay(unsigned int fps_):fps(fps_)
{
}
void GameDisplay::loop() {
    while (isEnd) {
        sf::RenderWindow menuWindow(sf::VideoMode(400, 400), "Menu");
        Terrarium::mapType selectedMapType = Terrarium::mapType::empty;
        menuWindow.setFramerateLimit(fps);
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

        while (menuWindow.isOpen()) {
            sf::Event event;
            while (
                menuWindow.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    menuWindow.close();
                    break;
                }
                sf::Vector2i localPosition = sf::Mouse::getPosition(menuWindow);
                if (startButton.isClicked(localPosition)) {
                    isGameStarted = true;
                    menuWindow.close();
                }
                else
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
                            mapTypeButton.setString("Empty");
                            break;
                        }
                    }
                    else if (quitButton.isClicked(localPosition)) {
                        isEnd = false;
                        return;
                    }
            }
            menuWindow.clear();
            menuWindow.draw(gameName);
            menuWindow.draw(startButton.shape);
            menuWindow.draw(startButton.text);
            menuWindow.draw(mapTypeButton.shape);
            menuWindow.draw(mapTypeButton.text);
            menuWindow.draw(quitButton.shape);
            menuWindow.draw(quitButton.text);
            menuWindow.display();
        }

        if (isGameStarted) {

            Terrarium terrarium = Terrarium(selectedMapType);
            //obiekt ktory zajmuje sie logik¹ gry
            int windowWidth = terrarium.getSizeOfBoard() * 50,
                windowHeight = terrarium.getSizeOfBoard() * 50;
            sf::Clock fruitClock, gameClock; //zegary gry
            sf::RenderWindow window(
                sf::VideoMode(windowWidth, windowHeight),
                "Snake");
            
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
                            if (terrarium.getMoveDirection() != Terrarium::moveType::down)
                                terrarium.changeDirection(Terrarium::moveType::up);
                            break;
                        case sf::Keyboard::Down:
                            if (terrarium.getMoveDirection() != Terrarium::moveType::up)
                                terrarium.changeDirection(Terrarium::moveType::down);
                            break;
                        case sf::Keyboard::Right:
                            if (terrarium.getMoveDirection() != Terrarium::moveType::left)
                                terrarium.changeDirection(Terrarium::moveType::right);
                            break;
                        case sf::Keyboard::Left:
                            if (terrarium.getMoveDirection() != Terrarium::moveType::right)
                                terrarium.changeDirection(Terrarium::moveType::left);
                            break;
                        default:
                            break;
                        }
                        //changing move direction is allowed only when snake turns 90 degrees
                        break;
                    default:
                        break;
                    }
                }
                window.clear();
                terrarium.updateGameState(window, gameClock, fruitClock);
                window.display();
            }
        }
    }
}