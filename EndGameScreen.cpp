#include "EndGameScreen.h"

EndGameScreen::EndGameScreen(float width, float height, int finalScore, int highScore) {
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font!");
    }

    // Set up the score text
    scoreText.setFont(font);
    scoreText.setString("Final Score: " + std::to_string(finalScore));
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(width / 2 - scoreText.getGlobalBounds().width / 2, height / 2 - 40);

    // Set up the high score text
    highScoreText.setFont(font);
    highScoreText.setString("High Score: " + std::to_string(highScore));
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(sf::Color::Yellow);
    highScoreText.setPosition(width / 2 - highScoreText.getGlobalBounds().width / 2, height / 2);

    // Set up the exit text
    exitText.setFont(font);
    exitText.setString("Press Enter to Restart or Escape to Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    exitText.setPosition(width / 2 - exitText.getGlobalBounds().width / 2, height / 2 + 40);
}

void EndGameScreen::draw(sf::RenderWindow& window) {
    window.clear(sf::Color::Black);
    window.draw(scoreText);
    window.draw(highScoreText);
    window.draw(exitText);
    window.display();
}

bool EndGameScreen::handleInput(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter) {
            return true; // Restart game
        }
        if (event.key.code == sf::Keyboard::Escape) {
            return false; // Exit game
        }
    }
    return false; // Do nothing
}
