#include "Elipses.hpp"
#include "../Helpers/Helpers.hpp"
#include <cmath>

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

void drawEllipseWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
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
}