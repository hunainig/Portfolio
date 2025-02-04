// MainMenu.h
#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class MainMenu {
public:
    MainMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void handleInput(sf::RenderWindow& window); // Update this line
    void moveUp();
    void moveDown();
    int getSelectedItemIndex() const;

private:
    std::vector<sf::Text> menuOptions;
    int selectedItemIndex;
    sf::Font font;
    sf::RectangleShape background;
};

#endif // MAINMENU_H
