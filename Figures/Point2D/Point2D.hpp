#ifndef POINT2D_HPP
#define POINT2D_HPP

#include "../../Object/ShapeObject.hpp"
#include "../../Object/Renderer/PrimitiveRenderer.hpp"
#include <SFML/Graphics.hpp>

class Point2D : public ShapeObject {
public:
    Point2D(float x = 0.f, float y = 0.f);

    float getX() const;
    float getY() const;

    void set(float newX, float newY);

    // DrawableObject
    void draw(PrimitiveRenderer& renderer) override;
    std::string getType() const override { return "Point2D"; }
    void draw() override {} // NIEUŻYWANE – bo masz draw(renderer), ale musi istnieć


    // UpdatableObject (może być puste)
    void update() override {}

    // TransformableObject
    void translate(float dx, float dy) override;
    void rotate(float angleDeg) override; // rotate around origin (0,0)
    void scale(float factor) override;

    void setColor(const sf::Color& c) { color = c; }
    const sf::Color& getColor() const { return color; }

private:
    float x;
    float y;
    sf::Color color = sf::Color::White; // domyślny kolor; można dodać setter
};

#endif // POINT2D_HPP
