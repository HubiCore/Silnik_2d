/*#include "helpers.hpp"
#include "../Point2D.hpp"
#include "../LineSegment.hpp"
#include <cmath>

// ============================================================================
// HELPER CLASSES FOR DRAWING
// ============================================================================

class DrawablePoint2D : public Point2D {
private:
    sf::Color color;
public:
    DrawablePoint2D(float x = 0, float y = 0, sf::Color color = sf::Color::White)
        : Point2D(x, y), color(color) {}

    void setColor(sf::Color newColor) { color = newColor; }
    sf::Color getColor() const { return color; }

    void draw(class PrimitiveRenderer& renderer) const;
};

class DrawableLineSegment : public LineSegment {
private:
    sf::Color color;
public:
    DrawableLineSegment(const Point2D& p1, const Point2D& p2, sf::Color color = sf::Color::White)
        : LineSegment(p1, p2), color(color) {}

    void setColor(sf::Color newColor) { color = newColor; }
    sf::Color getColor() const { return color; }

    void draw(class PrimitiveRenderer& renderer) const;
};

// ============================================================================
// HELPER FUNCTIONS IMPLEMENTATION
// ============================================================================

std::vector<sf::Vector2f> calculatePolygonPoints(int sides, float radius,
                                                  sf::Vector2f center, float startAngle) {
    std::vector<sf::Vector2f> points;
    float angleStep = 2 * PI / sides;

    for (int i = 0; i < sides; ++i) {
        float angle = startAngle + i * angleStep;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);
        points.push_back(sf::Vector2f(x, y));
    }

    return points;
}

std::vector<sf::Vector2f> createLineHitbox(float x1, float y1, float x2, float y2,
                                            float thickness) {
    std::vector<sf::Vector2f> points;

    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt(dx * dx + dy * dy);

    if (length < 0.001f) {
        float halfThick = thickness / 2.0f;
        points.push_back(sf::Vector2f(x1 - halfThick, y1 - halfThick));
        points.push_back(sf::Vector2f(x1 + halfThick, y1 - halfThick));
        points.push_back(sf::Vector2f(x1 + halfThick, y1 + halfThick));
        points.push_back(sf::Vector2f(x1 - halfThick, y1 + halfThick));
        return points;
    }

    float nx = dx / length;
    float ny = dy / length;
    float px = -ny;
    float py = nx;
    float halfThickness = thickness / 2.0f;

    points.push_back(sf::Vector2f(
        x1 + px * halfThickness - nx * halfThickness,
        y1 + py * halfThickness - ny * halfThickness
    ));

    points.push_back(sf::Vector2f(
        x2 + px * halfThickness + nx * halfThickness,
        y2 + py * halfThickness + ny * halfThickness
    ));

    points.push_back(sf::Vector2f(
        x2 - px * halfThickness + nx * halfThickness,
        y2 - py * halfThickness + ny * halfThickness
    ));

    points.push_back(sf::Vector2f(
        x1 - px * halfThickness - nx * halfThickness,
        y1 - py * halfThickness - ny * halfThickness
    ));

    return points;
}

// Implementacje metod rysujących
void DrawablePoint2D::draw(PrimitiveRenderer& renderer) const {
    renderer.drawPoint(getX(), getY(), color);
}

void DrawableLineSegment::draw(PrimitiveRenderer& renderer) const {
    renderer.drawLine(getP1().getX(), getP1().getY(), getP2().getX(), getP2().getY(), color);
}*/