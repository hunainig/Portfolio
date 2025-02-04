// #include <SFML/Graphics.hpp>
// #include "MainMenu.h"
// #include "MainMenu.cpp"

// int main() {
//     sf::RenderWindow window(sf::VideoMode(400, 600), "Block Stacking Game");
//     MainMenu mainMenu(400, 600);
//     bool inMenu = true;

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }

//             if (inMenu) {
//                 if (event.type == sf::Event::KeyPressed) {
//                     if (event.key.code == sf::Keyboard::Up) {
//                         mainMenu.moveUp();
//                     } else if (event.key.code == sf::Keyboard::Down) {
//                         mainMenu.moveDown();
//                     } else if (event.key.code == sf::Keyboard::Enter) {
//                         int selected = mainMenu.getSelectedItemIndex();
//                         if (selected == 0) { // Start Game
//                             inMenu = false;
//                         } else if (selected == 1) { // Instructions
//                             // Display instructions (optional implementation)
//                         } else if (selected == 2) { // Exit
//                             window.close();
//                         }
//                     }
//                 }
//             }
//         }

//         window.clear(sf::Color::Black);
//         if (inMenu) {
//             mainMenu.draw(window);
//         } else {
//             // Game logic
//             GameLevel game;
//             game.handleInput(window);
//             game.update();
//             game.render(window);
//         }
//         window.display();
//     }

//     return 0;
// }
