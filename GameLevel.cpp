#include "GameLevel.h"
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()


void GameLevel::update() {
    currentBlock.move(0, fallingSpeed); // Apply gravity

    if (tower.checkCollision(currentBlock) || 
        currentBlock.getPosition().y + currentBlock.getBounds().height >= floorPosition) {
        
        if (tower.getBlocks().empty() || 
            (currentBlock.getPosition().x + currentBlock.getBounds().width / 2 >= tower.getTopLeft() &&
             currentBlock.getPosition().x + currentBlock.getBounds().width / 2 <= tower.getTopRight())) {
            
            bool stable = tower.getBlocks().empty() || 
                          (currentBlock.isBlockStable() && isStable(currentBlock, tower.getTopBlock()));

            if (stable) {
                tower.addBlock(currentBlock);
                score += 10; // Increment score only if the block is stable
            // Change score text color based on score
            if (score % 50 == 0) { // Change color every 50 points
                scoreText.setFillColor(sf::Color::Green); // Change to green
            } else {
                scoreText.setFillColor(sf::Color::White); // Default color
            }
            // Check for high score update
            if (score > highScore) {
                highScore = score; // Update high score
            }

            createNewBlock();
            } else {
                // Change the base block color to red, but do not end the game
                isStable(currentBlock, tower.getTopBlock());
            }
        } else {
            if (tower.getBlocks().size() > 0) {
                gameState = GameState::GAME_OVER; // End the game if no valid placement
            }
        }
    }

    scoreText.setString("Score: " + std::to_string(score) + " | High Score: " + std::to_string(highScore));
}

bool GameLevel::isStable(const Block& newBlock, Block& baseBlock) {
    // Calculate the edges of the base block
    float baseLeftEdge = baseBlock.getPosition().x;
    float baseRightEdge = baseBlock.getPosition().x + baseBlock.getBounds().width;

    // Calculate the width of the base block
    float baseWidth = baseBlock.getBounds().width;

    // Calculate the overlap between the new block and the base block
    float newBlockLeftEdge = newBlock.getPosition().x;
    float newBlockRightEdge = newBlock.getPosition().x + newBlock.getBounds().width;

    // Determine the overlap
    float overlap = std::max(0.0f, std::min(newBlockRightEdge, baseRightEdge) - std::max(newBlockLeftEdge, baseLeftEdge));

    // Calculate the coverage percentage
    float coveragePercentage = overlap / baseWidth;

    // Check if the new block covers at least 30% of the base block
    bool stable = (coveragePercentage >= 0.3f);

    // Change the color of the base block based on stability
    if (!stable) {
        baseBlock.setColor(sf::Color::Red); // Change to red if unstable
    } else {
        baseBlock.setColor(sf::Color::Green); // Change back to green if stable
    }

    return stable;
}


GameLevel::GameLevel() 
    : window(sf::VideoMode(800, 600), "Stacking Game"),
      mainMenu(800, 600), 
      gameState(GameState::MENU), 
      currentBlock(50, 20, sf::Color::Yellow, 1.0f, true), // Initialize currentBlock
      tower(), // Initialize tower
      score(0), // Initialize score
      fallingSpeed(0.3), // Initialize falling speed
      floorPosition(600), // Initialize floor position
      gameOver(false), // Initialize game over status
      highScore(0) {
        resetHighScore();

    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Initialize currentBlock with a random horizontal position
    createNewBlock();

    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Failed to load font!");
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition(10, 10); // Position for score display

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(48); // Larger text for Game Over
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setString("Game Over!");
    gameOverText.setPosition(250, 250); // Position it at the center of the screen
}

void GameLevel::run() {
    while (window.isOpen()) {
        handleInput();
        if (gameState == GameState::GAME && !gameOver) {
            update();
        }
        render();
    }
}
void GameLevel::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (gameState == GameState::MENU) {
            mainMenu.handleInput(window);

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Down) {
                    mainMenu.moveDown();
                }
                if (event.key.code == sf::Keyboard::Up) {
                    mainMenu.moveUp();
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    int selectedItemIndex = mainMenu.getSelectedItemIndex();
                    if (selectedItemIndex == 0) {
                        gameState = GameState::GAME;
                    } else if (selectedItemIndex == 1) {
                        gameState = GameState::INSTRUCTIONS;
                    } else if (selectedItemIndex == 2) {
                        window.close();
                    }
                }
            }
        } else if (gameState == GameState::INSTRUCTIONS) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                gameState = GameState::MENU;
            }
        } else if (gameState == GameState::GAME) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left) {
                    currentBlock.move(-30, 0);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    currentBlock.move(30, 0);
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        } else if (gameState == GameState::GAME_OVER) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::R) {
                    resetGame();
                    gameState = GameState::GAME;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }
    }
}



void GameLevel::render() {
    window.clear();

    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setFillColor(sf::Color(20, 30, 50)); // Dark blue

    window.draw(background);

    if (gameState == GameState::MENU) {
        mainMenu.draw(window);
    } else if (gameState == GameState::INSTRUCTIONS) {
        sf::Text instructionText;
        instructionText.setFont(font);
        instructionText.setCharacterSize(24);
        instructionText.setFillColor(sf::Color::White);
        instructionText.setStyle(sf::Text::Bold);
        instructionText.setString("Instructions:\n\n"
                                   "1. Use Left and Right arrow keys to move the falling block.\n"
                                   "2. Stack blocks to build a tower.\n"
                                   "3. Avoid missing the blocks!\n"
                                   "4. Press Escape to return to the main menu.\n"
                                   "\n"
                                   "Hunain, Faiz and Rafay hope that you enjoy the game! <3"
                                   );
        instructionText.setPosition(50, 50);
        window.draw(instructionText);
    } else if (gameState == GameState::GAME) {
        for (const auto& block : tower.getBlocks()) {
            block.draw(window);
        }
        currentBlock.draw(window);
        window.draw(scoreText);
    } else if (gameState == GameState::GAME_OVER) {
        window.draw(gameOverText);
        sf::Text restartText;
        restartText.setFont(font);
        restartText.setCharacterSize(24);
        restartText.setFillColor(sf::Color::White);
        restartText.setStyle(sf::Text::Bold);
        restartText.setString("Press R to Restart or Escape to Exit");
        restartText.setPosition(200, 350);
        window.draw(restartText);

        sf::Text scoreDisplay;
        scoreDisplay.setFont(font);
        scoreDisplay.setCharacterSize(24);
        scoreDisplay.setFillColor(sf::Color::White);
        scoreDisplay.setStyle(sf::Text::Bold);
        scoreDisplay.setString("Your Score: " + std::to_string(score) + 
                               "\nHigh Score: " + std::to_string(highScore));
        scoreDisplay.setPosition(200, 400);
        window.draw(scoreDisplay);
    }

    window.display();
}


void GameLevel::resetGame() {
    score = 0; // Reset score
    gameOver = false; // Reset game over status

    // Clear the tower of blocks
    tower.clear(); // Assuming you have a clear method in the Tower class to reset it

    // Create a new block at the top of the window
    createNewBlock(); // Create a new block at the starting position

    // Reset the position of the current block to the top of the window
    currentBlock.setPosition(window.getSize().x / 2 - currentBlock.getBounds().width / 2, 0); // Center the new block at the top
}

void GameLevel::updateHighScore(int currentScore) {
    if (currentScore > highScore) {
        highScore = currentScore;  // Update high score if current score is higher
    }
}
void GameLevel::resetHighScore() {
    highScore = 0;  // Reset the high score when the game is restarted or exited
}

void GameLevel::createNewBlock() {
    // Create a new block with random properties
    float width = 50 + std::rand() % 100; // Random width between 50 and 150
    float height = 20; // Fixed height
    sf::Color color = sf::Color::Yellow; // Fixed color for simplicity
    bool isStable = true; // Assume new blocks are stable for now

    // Generate a random horizontal position for the block
    float randomX = std::rand() % (static_cast<int>(window.getSize().x - width)); // Ensure the block is within window bounds

    currentBlock = Block(width, height, color, 1.0f, isStable); // Initialize currentBlock with all parameters
    currentBlock.setPosition(randomX, 0); // Set the position of the block at the top of the window}
}