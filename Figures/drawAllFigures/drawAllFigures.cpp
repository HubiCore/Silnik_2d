#include "../drawAllFigures/drawAllFigures.hpp"
#include "../../Engine/Engine.hpp"
#include "../Point2D/Point2D.hpp"
#include "../LineSegment/LineSegment.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <map>

const float PI = 3.14159265358979323846f;

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

    void draw(PrimitiveRenderer& renderer) const {
        renderer.drawPoint(getX(), getY(), color);
    }
};

class DrawableLineSegment : public LineSegment {
private:
    sf::Color color;
public:
    DrawableLineSegment(const Point2D& p1, const Point2D& p2, sf::Color color = sf::Color::White)
        : LineSegment(p1, p2), color(color) {}

    void setColor(sf::Color newColor) { color = newColor; }
    sf::Color getColor() const { return color; }

    void draw(PrimitiveRenderer& renderer) const {
        renderer.drawLine(getP1().getX(), getP1().getY(), getP2().getX(), getP2().getY(), color);
    }
};

// ============================================================================
// HELPER FUNCTIONS
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

// ============================================================================
// INDIVIDUAL SHAPE FUNCTIONS
// ============================================================================

void drawPointWithHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius) {
    // Rysuj punkt
    DrawablePoint2D point(x, y, color);
    point.draw(renderer);

    // Dodaj hitbox (małe kółko)
    player.addCollisionCircle(sf::Vector2f(x, y), hitboxRadius);
}

void drawLineWithHitbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness) {
    // Rysuj linię
    DrawablePoint2D p1(x1, y1, color);
    DrawablePoint2D p2(x2, y2, color);
    DrawableLineSegment line(p1, p2, color);
    line.draw(renderer);

    // Dodaj hitbox (obrócony prostokąt)
    std::vector<sf::Vector2f> lineHitbox = createLineHitbox(x1, y1, x2, y2, thickness);
    player.addCollisionPolygon(lineHitbox);
}

void drawPolylineWithHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness) {
    // Rysuj polilinię
    renderer.drawPolyLine(points, closed, color);

    // Hitboxy dla każdego segmentu
    for (size_t i = 0; i < points.size() - 1; i++) {
        float x1 = points[i].x;
        float y1 = points[i].y;
        float x2 = points[i+1].x;
        float y2 = points[i+1].y;

        std::vector<sf::Vector2f> segmentHitbox = createLineHitbox(x1, y1, x2, y2, thickness);
        player.addCollisionPolygon(segmentHitbox);
    }

    // Hitbox dla zamykającego segmentu (jeśli polilinia jest zamknięta)
    if (closed && points.size() > 2) {
        float x1 = points.back().x;
        float y1 = points.back().y;
        float x2 = points.front().x;
        float y2 = points.front().y;

        std::vector<sf::Vector2f> closingHitbox = createLineHitbox(x1, y1, x2, y2, thickness);
        player.addCollisionPolygon(closingHitbox);
    }
}

void drawCircleWithHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor) {
    // Rysuj okrąg
    renderer.drawCircle(centerX, centerY, radius, outlineColor, fillColor);

    // Dodaj hitbox (dokładne kółko)
    player.addCollisionCircle(sf::Vector2f(centerX, centerY), radius);
}

void drawCircleSymmetricWithHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color) {
    // Rysuj okrąg (wersja symetryczna)
    renderer.drawCircleSymmetric(centerX, centerY, radius, color);

    // Dodaj hitbox (dokładne kółko)
    player.addCollisionCircle(sf::Vector2f(centerX, centerY), radius);
}

void drawEllipseWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments) {
    // Rysuj elipsę
    renderer.drawEllipseSymmetric(centerX, centerY, radiusX, radiusY, color);

    // Przygotuj punkty dla przybliżenia wielokątem
    std::vector<sf::Vector2f> ellipsePoints;
    for (int i = 0; i < segments; i++) {
        float angle = 2 * PI * i / segments;
        float x = centerX + radiusX * std::cos(angle);
        float y = centerY + radiusY * std::sin(angle);
        ellipsePoints.push_back(sf::Vector2f(x, y));
    }

    // Dodaj hitbox (przybliżenie wielokątem)
    player.addCollisionPolygon(ellipsePoints);
}

void drawPolygonWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color) {
    // Oblicz promień na podstawie długości boku
    float radius = sideLength / (2 * std::sin(PI / sides));

    // Rysuj wielokąt
    renderer.drawPolygon(sides, sideLength, center, startAngle, color);

    // Oblicz punkty wielokąta dla hitboxa
    std::vector<sf::Vector2f> polygonPoints = calculatePolygonPoints(sides, radius, center, startAngle);

    // Dodaj hitbox (dokładny wielokąt)
    player.addCollisionPolygon(polygonPoints);
}

// ============================================================================
// PREDEFINED OBJECTS FUNCTIONS (funkcje dostępu do wcześniej zdefiniowanych obiektów)
// ============================================================================

void drawPredefinedPoints(PrimitiveRenderer& renderer, Player& player) {
    drawPointWithHitbox(renderer, player, 100, 100, sf::Color::Yellow);
    drawPointWithHitbox(renderer, player, 150, 150, sf::Color::White);
    drawPointWithHitbox(renderer, player, 200, 200, sf::Color::White);
}

void drawPredefinedLines(PrimitiveRenderer& renderer, Player& player) {
    drawLineWithHitbox(renderer, player, 100, 100, 200, 200, sf::Color::Red);
    drawLineWithHitbox(renderer, player, 250, 100, 400, 200, sf::Color::Green);
    drawLineWithHitbox(renderer, player, 400, 100, 550, 200, sf::Color::Cyan);
}

void drawPredefinedPolylines(PrimitiveRenderer& renderer, Player& player) {
    std::vector<sf::Vector2f> polylinePoints = {
        {300,100}, {400,150}, {450,250}, {350,300}, {100,300}
    };
    drawPolylineWithHitboxes(renderer, player, polylinePoints, true, sf::Color::Cyan, 2.0f);
}

void drawPredefinedCircles(PrimitiveRenderer& renderer, Player& player) {
    drawCircleWithHitbox(renderer, player, 600, 200, 40, sf::Color::Green, sf::Color::White);
    drawCircleSymmetricWithHitbox(renderer, player, 700, 350, 60, sf::Color::Red);
}

void drawPredefinedEllipses(PrimitiveRenderer& renderer, Player& player) {
    drawEllipseWithHitbox(renderer, player, 500, 100, 80, 40, sf::Color::Yellow);
}

void drawPredefinedPolygons(PrimitiveRenderer& renderer, Player& player) {
    // Trójkąt równoboczny (wierzchołek na górze)
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(200, 400), -PI/2, sf::Color::Red);

    // Kwadrat obrócony o 45 stopni
    drawPolygonWithHitbox(renderer, player, 4, 40, sf::Vector2f(10, 10), PI/4, sf::Color::Green);
    drawPolygonWithHitbox(renderer, player, 4, 40, sf::Vector2f(30, 30), PI/4, sf::Color::Green);

    // Sześciokąt (wierzchołek w prawo)
    drawPolygonWithHitbox(renderer, player, 6, 60, sf::Vector2f(600, 400), 0, sf::Color::Red);

    // Pięciokąt (wierzchołek na górze)
    drawPolygonWithHitbox(renderer, player, 5, 70, sf::Vector2f(600, 300), -PI/2, sf::Color::Red);
}

// ============================================================================
// MAIN DRAWING FUNCTION (teraz używa funkcji dostępu)
// ============================================================================

void drawAllFigures(PrimitiveRenderer& renderer, Player& player) {
    // Clear previous hitboxes
    player.clearCollisionObjects();

    // Rysuj wszystkie predefiniowane obiekty
    drawPredefinedPoints(renderer, player);
    drawPredefinedLines(renderer, player);
    drawPredefinedPolylines(renderer, player);
    drawPredefinedCircles(renderer, player);
    drawPredefinedEllipses(renderer, player);
    drawPredefinedPolygons(renderer, player);

    // ------------------------------------------------------------------------
    // AREA FILLING - visual effect only, no hitboxes
    // ------------------------------------------------------------------------
    renderer.floodFill0(200, 400, sf::Color(0,255,255,150), sf::Color::Green);

    // ------------------------------------------------------------------------
    // DRAW PLAYER (on top of everything)
    // ------------------------------------------------------------------------
    player.draw(renderer);
}