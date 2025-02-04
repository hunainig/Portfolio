#ifndef TOWER_H
#define TOWER_H

#include <vector>
#include "Block.h"

class Tower {
public:
    void addBlock(const Block& block);
    const std::vector<Block>& getBlocks() const;
    float getTopHeight() const;
    bool checkCollision(const Block& block) const;
    float getTopLeft() const;   // Returns the left edge of the top block
    float getTopRight() const;  // Returns the right edge of the top block
     // Returns the top height of the top block
    Block& getTopBlock();
    void draw(sf::RenderWindow& window) const;
    void clear();


private:
    std::vector<Block> blocks;
};

#endif // TOWER_H
