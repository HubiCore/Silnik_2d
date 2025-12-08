/**
 * @file Lines.cpp
 * @brief Implementacje funkcji do rysowania linii
 *
 * Implementacja funkcji zadeklarowanych w Lines.hpp.
 * Zawiera logikę rysowania linii i zarządzania hitboxami.
 */

#include "Lines.hpp"
#include "../Helpers/Helpers.hpp"

/**
 * @brief Implementacja drawLineWithHitbox
 * @ingroup Lines
 *
 * Funkcja wykonuje dwa główne zadania:
 * 1. Rysuje linię na ekranie za pomocą PrimitiveRenderer
 * 2. Tworzy i dodaje hitbox kolizji do obiektu gracza
 *
 * @details Proces działania:
 * - Tworzy dwa punkty końcowe (DrawablePoint2D)
 * - Tworzy segment linii (DrawableLineSegment)
 * - Rysuje linię na rendererze
 * - Generuje hitbox jako obrócony prostokąt
 * - Dodaje hitbox do systemu kolizji gracza
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza
 * @param x1 Współrzędna X początku linii
 * @param y1 Współrzędna Y początku linii
 * @param x2 Współrzędna X końca linii
 * @param y2 Współrzędna Y końca linii
 * @param color Kolor linii
 * @param thickness Grubość linii
 *
 * @exception std::bad_alloc Jeśli alokacja pamięci dla hitboxa się nie powiedzie
 *
 * @note Funkcja używa createLineHitbox() z Helpers.hpp do generowania kształtu kolizji
 * @see DrawablePoint2D, DrawableLineSegment, createLineHitbox()
 */
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

/**
 * @brief Implementacja drawLineWithoutHitbox
 * @ingroup Lines
 *
 * Uproszczona wersja funkcji drawLineWithHitbox, która rysuje tylko linię
 * bez dodatkowych operacji związanych z kolizjami.
 *
 * @details Różnice w stosunku do drawLineWithHitbox:
 * - Nie wywołuje createLineHitbox()
 * - Nie dodaje wielokąta kolizji do gracza
 * - Jest szybsza i zużywa mniej pamięci
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza (parametr ignorowany)
 * @param x1 Współrzędna X początku linii
 * @param y1 Współrzędna Y początku linii
 * @param x2 Współrzędna X końca linii
 * @param y2 Współrzędna Y końca linii
 * @param color Kolor linii
 * @param thickness Grubość linii
 *
 * @note Użyj tej funkcji dla linii, które nie powinny kolidować z graczem
 */
void drawLineWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness) {
    // Rysuj linię
    DrawablePoint2D p1(x1, y1, color);
    DrawablePoint2D p2(x2, y2, color);
    DrawableLineSegment line(p1, p2, color);
    line.draw(renderer);
}