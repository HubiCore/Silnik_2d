#include "LineSegment.hpp"

LineSegment::LineSegment(Point2D a, Point2D b) : p1(a), p2(b) {}
Point2D LineSegment::getP1() const {return p1;}
Point2D LineSegment::getP2() const {return p2;}
void LineSegment::setP1(Point2D p) {p1 = p;}
void LineSegment::setP2(Point2D p) {p2 = p;}

void LineSegment::draw(PrimitiveRenderer& renderer, bool incremental, sf::Color color) const {
    if (incremental)
        renderer.drawLineIncremental(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
    else
        renderer.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);

}