// Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
class Block {
public:
    Block(float width, float height, sf::Color color, float weight, bool isStable);
    void move(float offsetX, float offsetY);
    void rotate(float angle);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void draw(sf::RenderWindow& window) const;
    void setColor(sf::Color color);
    bool isBlockStable() const;
    float getWeight() const;

private:
    sf::RectangleShape shape;
    float weight;
    bool isStable;
};

#endif // BLOCK_H
