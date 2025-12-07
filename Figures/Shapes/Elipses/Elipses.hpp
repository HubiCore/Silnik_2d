#include "Elipses.hpp"
#include "../Helpers/Helpers.hpp"
#include <cmath>

/**
 * @file Elipses.cpp
 * @brief Implementacje funkcji do rysowania elips
 * @ingroup Graphics
 */

/**
 * @brief Implementacja funkcji drawEllipseWithHitbox
 *
 * Szczegółowa implementacja rysowania elipsy z hitboxem.
 * Algorytm używa aproksymacji wielokątem do tworzenia hitboxu.
 */
void drawEllipseWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments) {
    //Rysuj elipsę używając symetrycznego algorytmu renderera
    renderer.drawEllipseSymmetric(centerX, centerY, radiusX, radiusY, color);
    //Przygotuj punkty dla przybliżenia wielokątem
    std::vector<sf::Vector2f> ellipsePoints;
    for (int i = 0; i < segments; i++) {
        /// @var angle Kąt bieżącego punktu na elipsie
        float angle = 2 * PI * i / segments;
        /// @var x Współrzędna X punktu na elipsie
        float x = centerX + radiusX * std::cos(angle);
        /// @var y Współrzędna Y punktu na elipsie
        float y = centerY + radiusY * std::sin(angle);
        ellipsePoints.push_back(sf::Vector2f(x, y));
    }
    // Dodaj hitbox (przybliżenie wielokątem) do gracza
    player.addCollisionPolygon(ellipsePoints);
}
/**
 * @brief Implementacja funkcji drawEllipseWithoutHitbox
 *
 * Implementacja rysowania elipsy bez hitboxu.
 * Algorytm jest identyczny jak w drawEllipseWithHitbox, ale pomija dodawanie hitboxu.
 */
void drawEllipseWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments) {
    //Rysuj elipsę używając symetrycznego algorytmu renderera
    renderer.drawEllipseSymmetric(centerX, centerY, radiusX, radiusY, color);
    //Przygotuj punkty dla przybliżenia wielokątem
    std::vector<sf::Vector2f> ellipsePoints;
    for (int i = 0; i < segments; i++) {
        float angle = 2 * PI * i / segments; ///@var angle Kąt bieżącego punktu na elipsie (w radianach)
        float x = centerX + radiusX * std::cos(angle); /// @var x Współrzędna X punktu na elipsie
        float y = centerY + radiusY * std::sin(angle); /// @var y Współrzędna Y punktu na elipsie
        ellipsePoints.push_back(sf::Vector2f(x, y));
    }
}