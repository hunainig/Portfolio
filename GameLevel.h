#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "Tower.h"
#include "Block.h"
#include "EndGameScreen.h"

enum class GameState {
    MENU,
    GAME,
    INSTRUCTIONS,
    GAME_OVER
};

class GameLevel {
public:
    GameLevel();
    void run();
    void handleInput();
    void update();
    void render();
    void resetGame(); // Add this line to declare resetGame
    void updateHighScore(int currentScore);
    void resetHighScore();
    void createNewBlock();

private:
    sf::RenderWindow window;
    MainMenu mainMenu;
    GameState gameState;
    Block currentBlock;
    Tower tower;
    int score;
    float fallingSpeed;
    float floorPosition;
    bool gameOver;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    int highScore=0;

    bool isStable(const Block& newBlock, Block& baseBlock);
};

#endif // GAMELEVEL_H
