#include "Point2D.hpp"
#include <cmath>

Point2D::Point2D(float x_, float y_)
    : x(x_), y(y_) {}

float Point2D::getX() const { return x; }
float Point2D::getY() const { return y; }

void Point2D::set(float newX, float newY) {
    x = newX;
    y = newY;
}

void Point2D::draw(PrimitiveRenderer& renderer) {
    renderer.drawPoint(x, y, color);
}

void Point2D::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

void Point2D::rotate(float angleDeg) {
    // rotate around origin (0,0)
    const float rad = angleDeg * static_cast<float>(M_PI) / 180.f;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    float nx = x * cosA - y * sinA;
    float ny = x * sinA + y * cosA;

    x = nx;
    y = ny;
}

void Point2D::scale(float factor) {
    x *= factor;
    y *= factor;
}
