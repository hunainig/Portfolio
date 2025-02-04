#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameLevel.h"
#include "MainMenu.h" // Ensure MainMenu is included

int main() {
    try {
        GameLevel game; // Create an instance of the GameLevel class
        game.run(); // Start the game loop
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl; // Catch any exceptions and print the error message
        return EXIT_FAILURE; // Return failure status if an error occurs
    }
    return EXIT_SUCCESS; // Return success status
}
