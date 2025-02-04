#include "MainMenu.h"

MainMenu::MainMenu(float width, float height) : selectedItemIndex(0) {
    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font!");
    }

    // Menu options
    std::vector<std::string> options = {"Start Game", "Instructions", "Exit"};

    // Configure menu options
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White); // Highlight first option
        text.setCharacterSize(40); // Larger font size for emphasis
        text.setStyle(sf::Text::Bold); // Make text bold
        text.setPosition(
            width / 2 - text.getGlobalBounds().width / 2,
            height / (options.size() + 1) * (i + 1)
        );
        menuOptions.push_back(text);
    }

    // Background rectangle
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(20, 30, 50)); // Deep blue-gray background
}

void MainMenu::draw(sf::RenderWindow& window) {
    window.clear();
    window.draw(background); // Draw background

    for (const auto& option : menuOptions) {
        window.draw(option); // Draw each menu option
    }
}

void MainMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuOptions[selectedItemIndex].setFillColor(sf::Color::White);  // Reset previous item's color
        selectedItemIndex--;
        menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);    // Highlight new item
    }
}

void MainMenu::moveDown() {
    if (selectedItemIndex + 1 < menuOptions.size()) {
        menuOptions[selectedItemIndex].setFillColor(sf::Color::White);  // Reset previous item's color
        selectedItemIndex++;
        menuOptions[selectedItemIndex].setFillColor(sf::Color::Red);    // Highlight new item
    }
}

int MainMenu::getSelectedItemIndex() const {
    return selectedItemIndex;
}

void MainMenu::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                moveUp();
            } else if (event.key.code == sf::Keyboard::Down) {
                moveDown();
            }
        }
    }
}
