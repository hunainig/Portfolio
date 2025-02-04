#ifndef ENDGAMESCREEN_H
#define ENDGAMESCREEN_H

#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <string>

class EndGameScreen {
public:
    EndGameScreen(float width, float height, int finalScore, int highScore);
    void draw(sf::RenderWindow& window);
    bool handleInput(sf::Event event);

private:
    sf::Font font;
    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Text exitText;
};

#endif // ENDGAMESCREEN_H
