#include "Point2D.hpp"

Point2D::Point2D(float x, float y) : x(x), y(y) {}
    float Point2D::getX() const { return x;}
    float Point2D::getY() const { return y;}
    void Point2D::set(float newX, float newY) {x = newX;y = newY;}
    void Point2D::draw(PrimitiveRenderer& renderer, sf::Color color) const {
        renderer.drawPoint(x, y, color);
    }
