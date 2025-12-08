/**
 * @file Points.cpp
 * @brief Implementacja funkcji rysowania punktów
 *
 * Ten plik zawiera implementację funkcji zadeklarowanych w Points.hpp.
 * Funkcje wykorzystują PrimitiveRenderer do rysowania i Player do zarządzania kolizjami.
 */

#include "Points.hpp"
#include "../Helpers/Helpers.hpp"

/**
 * @brief Implementacja rysowania punktu z hitboxem
 *
 * Szczegóły implementacji:
 * 1. Tworzy obiekt DrawablePoint2D
 * 2. Rysuje go za pomocą renderera
 * 3. Dodaje kolisty hitbox do systemu kolizji gracza
 *
 * @param renderer Referencja do obiektu renderera
 * @param player Referencja do obiektu gracza
 * @param x Współrzędna X
 * @param y Współrzędna Y
 * @param color Kolor punktu
 * @param hitboxRadius Promień hitboxu
 *
 */
void drawPointWithHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius) {
    // Rysuj punkt
    DrawablePoint2D point(x, y, color);
    point.draw(renderer);

    // Dodaj hitbox (małe kółko)
    player.addCollisionCircle(sf::Vector2f(x, y), hitboxRadius);
}

/**
 * @brief Implementacja rysowania punktu bez hitboxu
 *
 * Ta funkcja rysuje tylko wizualną reprezentację punktu
 * bez interakcji z systemem kolizji.
 *
 * @param renderer Referencja do obiektu renderera
 * @param player Referencja do obiektu gracza (nieużywana)
 * @param x Współrzędna X
 * @param y Współrzędna Y
 * @param color Kolor punktu
 * @param hitboxRadius Parametr ignorowany
 *
 * @code
 * DrawablePoint2D point(x, y, color);
 * point.draw(renderer);
 * @endcode
 */
void drawPointWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius) {
    // Rysuj punkt
    DrawablePoint2D point(x, y, color);
    point.draw(renderer);
}