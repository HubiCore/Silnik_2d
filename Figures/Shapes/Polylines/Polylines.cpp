/**
 * @file Polylines.cpp
 * @brief Implementacje funkcji do rysowania polilinii
 * @ingroup Polylines
 *
 * Implementacja funkcji zadeklarowanych w Polylines.hpp.
 * Zawiera logikę rysowania polilinii i zarządzania hitboxami dla każdego segmentu.
 */

#include "Polylines.hpp"
#include "../Helpers/Helpers.hpp"
#include <cmath>

/**
 * @brief Implementacja drawPolylineWithHitboxes
 * @ingroup Polylines
 *
 * Funkcja wykonuje następujące kroki:
 * 1. Rysuje polilinię na rendererze
 * 2. Dla każdego segmentu (pary kolejnych punktów) tworzy hitbox
 * 3. Dodaje każdy hitbox do systemu kolizji gracza
 * 4. Dla zamkniętych polilinii dodaje dodatkowy hitbox dla segmentu zamykającego
 *
 * @details Algorytm:
 * - Dla N punktów tworzy N-1 segmentów (dla polilinii otwartej)
 * - Każdy segment jest przetwarzany przez createLineHitbox() do postaci wielokąta kolizji
 * - Hitboxy są dodawane do gracza jako niezależne wielokąty
 * - Dla closed=true, dodatkowo przetwarzany jest segment od punktu N-1 do punktu 0
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza
 * @param points Wektor punktów definiujących polilinię
 * @param closed Flaga określająca czy polilinia ma być zamknięta
 * @param color Kolor polilinii
 * @param thickness Grubość linii
 *
 * @note Złożoność czasowa: O(n) gdzie n to liczba punktów
 * @note Każdy segment ma niezależny hitbox - kolizje są sprawdzane dla każdego segmentu osobno
 * @see createLineHitbox(), renderer.drawPolyLine()
 */
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

/**
 * @brief Implementacja drawPolylineWithoutHitboxes
 * @ingroup Polylines
 *
 * Uproszczona wersja funkcji drawPolylineWithHitboxes, która tylko rysuje
 * polilinię bez operacji związanych z kolizjami. Idealna dla elementów,
 * które mają być tylko wizualne.
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza (nieużywana)
 * @param points Wektor punktów definiujących polilinię
 * @param closed Flaga określająca czy polilinia ma być zamknięta
 * @param color Kolor polilinii
 * @param thickness Grubość linii (parametr zachowany dla spójności API)
 */
void drawPolylineWithoutHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness) {
    // Rysuj polilinię
    renderer.drawPolyLine(points, closed, color);
}