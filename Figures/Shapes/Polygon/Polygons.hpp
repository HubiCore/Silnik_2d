/**
 * @file Polygons.hpp
 * @brief Deklaracja funkcji rysowania wielokątów z hitboxami i bez
 *
 * Plik zawiera funkcje do rysowania regularnych wielokątów z opcjonalnymi
 * hitboxami dla wykrywania kolizji z graczem. Wspiera różne liczby boków
 * i konfiguracje geometryczne.
 *
 * @see PrimitiveRenderer
 * @see Player
 * @see calculatePolygonPoints()
 */

#ifndef POLYGONS_HPP
#define POLYGONS_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @defgroup PolygonDrawing Funkcje rysowania wielokątów
 * @brief Funkcje do tworzenia i renderowania wielokątów foremnych
 * @{
 */

/**
 * @brief Rysuje wielokąt foremny z dokładnym hitboxem
 *
 * Funkcja rysuje wielokąt o podanej liczbie boków i dodaje precyzyjny
 * wielokątny hitbox do systemu kolizji gracza. Obliczenia geometryczne
 * są wykonywane automatycznie.
 *
 * @code{.cpp}
 * // Przykład: sześciokąt (hexagon) o boku 50px
 * drawPolygonWithHitbox(renderer, player,
 *                       6,               // liczba boków
 *                       50.0f,           // długość boku
 *                       sf::Vector2f(100, 100), // środek
 *                       0.0f,            // kąt początkowy (radiany)
 *                       sf::Color::Blue);
 * @endcode
 *
 * @param renderer Referencja do obiektu renderera primitywów
 * @param player Referencja do obiektu gracza (dla systemu kolizji)
 * @param sides Liczba boków wielokąta (minimum 3)
 * @param sideLength Długość pojedynczego boku w pikselach
 * @param center Środek wielokąta (współrzędne x, y)
 * @param startAngle Kąt początkowy w radianach (0 = pierwszy wierzchołek na prawo)
 * @param color Kolor wypełnienia wielokąta
 *
 * @warning Dla sides < 3 funkcja może zachowywać się nieprzewidywalnie
 * @note Hitbox jest dokładnym odwzorowaniem kształtu wielokąta
 *
 * @throws std::invalid_argument Jeśli sides < 3 lub sideLength <= 0
 *
 * @see renderer.drawPolygon()
 * @see Player::addCollisionPolygon()
 * @see calculatePolygonPoints()
 */
void drawPolygonWithHitbox(PrimitiveRenderer &renderer, Player &player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color);

/**
 * @brief Rysuje wielokąt foremny bez hitboxu
 *
 * Funkcja rysuje tylko wizualną reprezentację wielokąta
 * bez dodawania hitboxu do systemu kolizji.
 *
 * @param renderer Referencja do obiektu renderera primitywów
 * @param player Referencja do obiektu gracza (parametr dla zgodności interfejsu)
 * @param sides Liczba boków wielokąta (minimum 3)
 * @param sideLength Długość pojedynczego boku w pikselach
 * @param center Środek wielokąta (współrzędne x, y)
 * @param startAngle Kąt początkowy w radianach
 * @param color Kolor wypełnienia wielokąta
 *
 * @note Parametr player nie jest używany, ale pozostawiono go dla
 *       spójności z drawPolygonWithHitbox()
 *
 * @return void
 *
 * @deprecated Rozważ użycie bezpośrednio renderer.drawPolygon() dla czysto wizualnych wielokątów
 */
void drawPolygonWithoutHitbox(PrimitiveRenderer &renderer, Player &player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color);

/** @} */ // koniec grupy PolygonDrawing

#endif // POLYGONS_HPP