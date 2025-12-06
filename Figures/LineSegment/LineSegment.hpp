#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "../../Object/ShapeObject.hpp"
#include "../Point2D/Point2D.hpp"
#include "../../Object/Renderer/PrimitiveRenderer.hpp"
#include <SFML/Graphics.hpp>

class LineSegment : public ShapeObject {
public:
    LineSegment(const Point2D& a = Point2D(), const Point2D& b = Point2D());

    Point2D getP1() const;
    Point2D getP2() const;

    void setP1(const Point2D& p);
    void setP2(const Point2D& p);

    // DrawableObject
    void draw(PrimitiveRenderer& renderer) override;
    std::string getType() const override { return "LineSegment"; }
    void draw() override {}


    // UpdatableObject
    void update() override {}

    // TransformableObject
    void translate(float dx, float dy) override;
    void rotate(float angleDeg) override; // rotate around midpoint
    void scale(float factor) override;     // scale around midpoint

    void setColor(const sf::Color& c) { color = c; }
    const sf::Color& getColor() const { return color; }

private:
    Point2D p1;
    Point2D p2;
    sf::Color color = sf::Color::White;
};

#endif // LINESEGMENT_HPP
