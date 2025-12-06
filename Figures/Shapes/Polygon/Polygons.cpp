#include "Polygons.hpp"
#include "../Helpers/Helpers.hpp"
#include <cmath>

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