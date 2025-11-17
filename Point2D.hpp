#pragma once
#include "PrimitiveRenderer.hpp"

class Point2D {
private:
    float x, y;
public:
    Point2D(float x = 0, float y = 0);
    float getX() const;
    float getY() const;
    void set(float newX, float newY);
    void draw(PrimitiveRenderer& renderer, sf::Color color = sf::Color::White) const;
};
