#include "Block.h"

// Constructor with parameters for width, height, color, weight, and stability
Block::Block(float width, float height, sf::Color color, float weight, bool isStable) 
    : weight(weight), isStable(isStable) {
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
}

// Move the block by a specified offset
void Block::move(float offsetX, float offsetY) {
    shape.move(offsetX, offsetY);
}

// Rotate the block by a specified angle
void Block::rotate(float angle) {
    shape.rotate(angle);
}

// Set the position of the block
void Block::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

// Get the current position of the block
sf::Vector2f Block::getPosition() const {
    return shape.getPosition();
}

// Get the bounding box of the block
sf::FloatRect Block::getBounds() const {
    return shape.getGlobalBounds();
}

// Draw the block on the specified render window
void Block::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

// Set the color of the block
void Block::setColor(sf::Color color) {
    shape.setFillColor(color);
}

// Check if the block is stable
bool Block::isBlockStable() const {
    return isStable;
}

// Get the weight of the block
float Block::getWeight() const {
    return weight;
}