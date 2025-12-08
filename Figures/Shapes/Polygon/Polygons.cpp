/**
 * @file Polygons.cpp
 * @brief Implementacja funkcji rysowania wielokątów
 *
 * Ten plik zawiera implementację funkcji zadeklarowanych w Polygons.hpp.
 * Wykorzystuje obliczenia geometryczne do generowania wierzchołków
 * wielokątów foremnych.
 *
 */

#include "Polygons.hpp"
#include "../Helpers/Helpers.hpp"
#include <cmath>

/**
 * @brief Implementacja rysowania wielokąta z hitboxem
 *
 * Algorytm działania:
 * 1. Oblicza promień okręgu opisanego na podstawie długości boku
 * 2. Rysuje wielokąt za pomocą renderera
 * 3. Oblicza pozycje wierzchołków za pomocą calculatePolygonPoints()
 * 4. Dodaje wielokątny hitbox do systemu kolizji gracza
 *
 * Wzór matematyczny promienia:
 * @f[ r = \frac{s}{2 \sin(\pi / n)} @f]
 * gdzie:
 * - @f$ r @f$ - promień okręgu opisanego
 * - @f$ s @f$ - długość boku (sideLength)
 * - @f$ n @f$ - liczba boków (sides)
 *
 * @param renderer Referencja do obiektu renderera
 * @param player Referencja do obiektu gracza
 * @param sides Liczba boków wielokąta
 * @param sideLength Długość boku w pikselach
 * @param center Środek wielokąta
 * @param startAngle Kąt początkowy w radianach
 * @param color Kolor wielokąta
 *
 * @pre sides >= 3
 * @pre sideLength > 0
 *
 * @post Do gracza dodano hitbox w kształcie wielokąta
 * @post Wielokąt został narysowany na rendererze
 *
 *
 */
void drawPolygonWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color) {
    // Walidacja parametrów wejściowych
    if (sides < 3) {
        throw std::invalid_argument("Liczba boków musi być >= 3");
    }
    if (sideLength <= 0) {
        throw std::invalid_argument("Długość boku musi być > 0");
    }

    // Oblicz promień na podstawie długości boku
    // Wzór: r = s / (2 * sin(π / n))
    float radius = sideLength / (2 * std::sin(PI / sides));

    // Rysuj wielokąt
    renderer.drawPolygon(sides, sideLength, center, startAngle, color);

    // Oblicz punkty wielokąta dla hitboxa
    std::vector<sf::Vector2f> polygonPoints = calculatePolygonPoints(sides, radius, center, startAngle);

    // Dodaj hitbox (dokładny wielokąt)
    player.addCollisionPolygon(polygonPoints);
}

/**
 * @brief Implementacja rysowania wielokąta bez hitboxu
 *
 * Funkcja oblicza promień i rysuje wielokąt bez interakcji
 * z systemem kolizji. Przydatna dla elementów tła lub dekoracji.
 *
 * @param renderer Referencja do obiektu renderera
 * @param player Referencja do obiektu gracza (niewykorzystywana)
 * @param sides Liczba boków wielokąta
 * @param sideLength Długość boku w pikselach
 * @param center Środek wielokąta
 * @param startAngle Kąt początkowy w radianach
 * @param color Kolor wielokąta
 *
 * @note Obliczenia promienia są identyczne jak w drawPolygonWithHitbox()
 * @note Parametr player jest całkowicie ignorowany
 *
 * @deprecated Używaj bezpośrednio:
 * @code
 * float radius = sideLength / (2 * std::sin(PI / sides));
 * renderer.drawPolygon(sides, sideLength, center, startAngle, color);
 * @endcode
 */
void drawPolygonWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color) {
    // Walidacja parametrów
    if (sides < 3) {
        throw std::invalid_argument("Liczba boków musi być >= 3");
    }
    if (sideLength <= 0) {
        throw std::invalid_argument("Długość boku musi być > 0");
    }

    // Oblicz promień na podstawie długości boku
    float radius = sideLength / (2 * std::sin(PI / sides));

    // Rysuj wielokąt
    renderer.drawPolygon(sides, sideLength, center, startAngle, color);
}