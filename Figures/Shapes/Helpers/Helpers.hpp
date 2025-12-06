#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "../../Point2D/Point2D.hpp"
#include "../../LineSegment/LineSegment.hpp"
#include "../../../Object/Renderer/PrimitiveRenderer.hpp"

constexpr float PI = 3.14159265358979323846f;

// ============================================================================
// HELPER CLASSES FOR DRAWING - deklaracje pełne
// ============================================================================

class DrawablePoint2D : public Point2D {
private:
    sf::Color color;
public:
    DrawablePoint2D(float x = 0, float y = 0, sf::Color color = sf::Color::White);
    void setColor(sf::Color newColor);
    sf::Color getColor() const;
    void draw(PrimitiveRenderer& renderer) const;
};

class DrawableLineSegment : public LineSegment {
private:
    sf::Color color;
public:
    DrawableLineSegment(const Point2D& p1, const Point2D& p2, sf::Color color = sf::Color::White);
    void setColor(sf::Color newColor);
    sf::Color getColor() const;
    void draw(PrimitiveRenderer& renderer) const;
};

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

std::vector<sf::Vector2f> calculatePolygonPoints(int sides, float radius,
                                                  sf::Vector2f center, float startAngle = 0);
std::vector<sf::Vector2f> createLineHitbox(float x1, float y1, float x2, float y2,
                                            float thickness = 2.0f);

#endif // HELPERS_HPP