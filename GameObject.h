#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual void draw(sf::RenderWindow& window) const = 0; // Pure virtual function
    virtual void update() = 0; // Pure virtual function
    virtual sf::FloatRect getBounds() const = 0; // To get the bounding box of the object
    virtual sf::Vector2f getPosition() const = 0; // To get the position of the object
    virtual void setPosition(float x, float y) = 0; // To set the position of the object
    virtual ~GameObject() = default; // Virtual destructor for cleanup
};

#endif // GAMEOBJECT_H