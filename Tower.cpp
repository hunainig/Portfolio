#include "Tower.h"

void Tower::addBlock(const Block& block) {
    blocks.push_back(block);
}

const std::vector<Block>& Tower::getBlocks() const {
    return blocks;
}

// float Tower::getTopHeight() const {
//     if (blocks.empty()) return 0;
//     return blocks.back().getPosition().y + blocks.back().getBounds().height;
// }

bool Tower::checkCollision(const Block& block) const {
    for (const auto& b : blocks) {
        if (b.getBounds().intersects(block.getBounds())) {
            return true;
        }
    }
    return false;
}

float Tower::getTopLeft() const {
    if (blocks.empty()) {
        // If the tower is empty, return a default value (adjust if needed)
        return 0.0f;
    }
    // Return the left edge of the top block
    return blocks.back().getPosition().x;
}

float Tower::getTopRight() const {
    if (blocks.empty()) {
        // If the tower is empty, return a default value (adjust if needed)
        return 0.0f;
    }
    // Return the right edge of the top block
    return blocks.back().getPosition().x + blocks.back().getBounds().width;
}

float Tower::getTopHeight() const {
    if (blocks.empty()) {
        // If the tower is empty, return the ground level (adjust if needed)
        return 580.0f; // Assuming floorPosition is 580
    }
    // Return the top edge (height) of the top block
    return blocks.back().getPosition().y;
}

Block& Tower::getTopBlock() {
    if (blocks.empty()) {
        throw std::runtime_error("No blocks in the tower"); // Handle the case where there are no blocks
    }
    return blocks.back(); // Return the top block
}

void Tower::draw(sf::RenderWindow& window) const {
    for (const auto& block : blocks) {
        block.draw(window); // Assuming Block has a draw method
    }
}

void Tower::clear() {
    blocks.clear(); // Clear all blocks from the vector
}
