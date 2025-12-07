#include "Helpers.hpp"
#include <cmath>

/**
 * @file Helpers.cpp
 * @brief Implementacje klas i funkcji pomocniczych
 * @ingroup Graphics
 * @ingroup Geometry
 */

// ============================================================================
// HELPER CLASSES IMPLEMENTATION
// ============================================================================

// DrawablePoint2D
/**
 * @brief Konstruktor DrawablePoint2D - implementacja
 */
DrawablePoint2D::DrawablePoint2D(float x, float y, sf::Color color)
    : Point2D(x, y), color(color) {}

/**
 * @brief Ustawia kolor punktu - implementacja
 */
void DrawablePoint2D::setColor(sf::Color newColor) {
    color = newColor;
}

/**
 * @brief Pobiera kolor punktu - implementacja
 */
sf::Color DrawablePoint2D::getColor() const {
    return color;
}

/**
 * @brief Rysuje punkt za pomocą renderera - implementacja
 *
 * Wykorzystuje metodę drawPoint z PrimitiveRenderer do narysowania
 * punktu o aktualnych współrzędnych i kolorze.
 */
void DrawablePoint2D::draw(PrimitiveRenderer& renderer) const {
    renderer.drawPoint(getX(), getY(), color);
}

// DrawableLineSegment
/**
 * @brief Konstruktor DrawableLineSegment - implementacja
 */
DrawableLineSegment::DrawableLineSegment(const Point2D& p1, const Point2D& p2, sf::Color color)
    : LineSegment(p1, p2), color(color) {}

/**
 * @brief Ustawia kolor odcinka - implementacja
 */
void DrawableLineSegment::setColor(sf::Color newColor) {
    color = newColor;
}

/**
 * @brief Pobiera kolor odcinka - implementacja
 */
sf::Color DrawableLineSegment::getColor() const {
    return color;
}

/**
 * @brief Rysuje odcinek za pomocą renderera - implementacja
 *
 * Wykorzystuje metodę drawLine z PrimitiveRenderer do narysowania
 * odcinka między punktami p1 i p2 o aktualnym kolorze.
 */
void DrawableLineSegment::draw(PrimitiveRenderer& renderer) const {
    renderer.drawLine(getP1().getX(), getP1().getY(),
                      getP2().getX(), getP2().getY(), color);
}

// ============================================================================
// HELPER FUNCTIONS IMPLEMENTATION
// ============================================================================

/**
 * @brief Implementacja calculatePolygonPoints
 *
 * Szczegółowa implementacja generowania wierzchołków wielokąta foremnego.
 * Algorytm iteruje przez kąty w równych odstępach, obliczając współrzędne
 * wierzchołków na okręgu.
 */
std::vector<sf::Vector2f> calculatePolygonPoints(int sides, float radius,
                                                  sf::Vector2f center, float startAngle) {
    std::vector<sf::Vector2f> points;

    if (sides < 3) return points; // Minimalnie 3 boki

    float angleStep = 2 * PI / sides;

    for (int i = 0; i < sides; ++i) {
        float angle = startAngle + i * angleStep;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);
        points.push_back(sf::Vector2f(x, y));
    }

    return points;
}

/**
 * @brief Implementacja createLineHitbox
 *
 * Szczegółowa implementacja tworzenia prostokątnego hitboxu dla linii.
 * Algorytm oblicza wektory normalne do linii i tworzy prostokąt przez
 * przesunięcie punktów o połowę grubości w kierunkach normalnych.
 */
std::vector<sf::Vector2f> createLineHitbox(float x1, float y1, float x2, float y2,
                                            float thickness) {
    std::vector<sf::Vector2f> points;

    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt(dx * dx + dy * dy);

    // Obsługa przypadku bardzo krótkiej linii (punktu)
    if (length < 0.001f) {
        float halfThick = thickness / 2.0f;
        points.push_back(sf::Vector2f(x1 - halfThick, y1 - halfThick));
        points.push_back(sf::Vector2f(x1 + halfThick, y1 - halfThick));
        points.push_back(sf::Vector2f(x1 + halfThick, y1 + halfThick));
        points.push_back(sf::Vector2f(x1 - halfThick, y1 + halfThick));
        return points;
    }

    // Normalizacja wektora kierunkowego linii
    float nx = dx / length;
    float ny = dy / length;

    // Wektor prostopadły (normalny) do linii
    float px = -ny;
    float py = nx;

    float halfThickness = thickness / 2.0f;

    // Obliczanie 4 wierzchołków prostokąta
    // Lewy dolny (patrząc od p1 do p2)
    points.push_back(sf::Vector2f(
        x1 + px * halfThickness - nx * halfThickness,
        y1 + py * halfThickness - ny * halfThickness
    ));

    // Prawy dolny
    points.push_back(sf::Vector2f(
        x2 + px * halfThickness + nx * halfThickness,
        y2 + py * halfThickness + ny * halfThickness
    ));

    // Prawy górny
    points.push_back(sf::Vector2f(
        x2 - px * halfThickness + nx * halfThickness,
        y2 - py * halfThickness + ny * halfThickness
    ));

    // Lewy górny
    points.push_back(sf::Vector2f(
        x1 - px * halfThickness - nx * halfThickness,
        y1 - py * halfThickness - ny * halfThickness
    ));

    return points;
}