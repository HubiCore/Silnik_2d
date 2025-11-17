#pragma once
#include "Point2D.hpp"

class LineSegment {
private:
    Point2D p1, p2;
public:
    LineSegment(Point2D a, Point2D b);
    Point2D getP1() const;
    Point2D getP2() const;
    void setP1(Point2D p);
    void setP2(Point2D p);
    void draw(PrimitiveRenderer& renderer, bool incremental, sf::Color color = sf::Color::Green) const;
};
