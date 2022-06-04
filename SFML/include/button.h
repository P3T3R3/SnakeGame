#include <iostream>
#include <SFML/Graphics.hpp>
#pragma once
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
            text.getGlobalBounds().height / 2 + 10));
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