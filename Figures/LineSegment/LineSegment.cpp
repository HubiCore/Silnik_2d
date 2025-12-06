#include "LineSegment.hpp"
#include <cmath>

LineSegment::LineSegment(const Point2D& a, const Point2D& b)
    : p1(a), p2(b) {}

Point2D LineSegment::getP1() const { return p1; }
Point2D LineSegment::getP2() const { return p2; }

void LineSegment::setP1(const Point2D& p) { p1 = p; }
void LineSegment::setP2(const Point2D& p) { p2 = p; }

void LineSegment::draw(PrimitiveRenderer& renderer) {
    renderer.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
}

void LineSegment::translate(float dx, float dy) {
    p1.translate(dx, dy);
    p2.translate(dx, dy);
}

void LineSegment::rotate(float angleDeg) {
    // rotate around midpoint
    float cx = (p1.getX() + p2.getX()) * 0.5f;
    float cy = (p1.getY() + p2.getY()) * 0.5f;

    const float rad = angleDeg * static_cast<float>(M_PI) / 180.f;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    auto rotateAroundCenter = [&](Point2D& p) {
        float x = p.getX() - cx;
        float y = p.getY() - cy;
        float nx = x * cosA - y * sinA;
        float ny = x * sinA + y * cosA;
        p.set(nx + cx, ny + cy);
    };

    rotateAroundCenter(p1);
    rotateAroundCenter(p2);
}

void LineSegment::scale(float factor) {
    // scale w.r.t midpoint
    float cx = (p1.getX() + p2.getX()) * 0.5f;
    float cy = (p1.getY() + p2.getY()) * 0.5f;

    auto scaleAroundCenter = [&](Point2D& p) {
        float nx = cx + (p.getX() - cx) * factor;
        float ny = cy + (p.getY() - cy) * factor;
        p.set(nx, ny);
    };

    scaleAroundCenter(p1);
    scaleAroundCenter(p2);
}
