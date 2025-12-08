/**
* @file drawAllFigures.hpp
 * @brief Deklaracja głównej funkcji rysującej wszystkie figury w scenie
 * @defgroup DrawingFunctions Grupa funkcji rysujących
 * @defgroup MainDrawing Główna funkcja rysująca
 * @ingroup DrawingFunctions
 *
 * Ten plik zawiera deklarację głównej funkcji odpowiedzialnej za rysowanie
 * kompletnej sceny gry, włączając w to wszystkie kształty geometryczne
 * oraz zarządzanie hitboxami dla wykrywania kolizji.
 */

#ifndef DRAW_ALL_FIGURES_HPP
#define DRAW_ALL_FIGURES_HPP

#include "../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Główna funkcja rysująca wszystkie figury w scenie
 * @ingroup MainDrawing
 *
 * Funkcja odpowiedzialna za kompletne renderowanie sceny gry. Wykonuje następujące operacje:
 * 1. Czyści poprzednie hitboxy gracza
 * 2. Rysuje wszystkie typy figur geometrycznych (punkty, linie, polilinie, koła, elipsy, wielokąty)
 * 3. Dodaje odpowiednie hitboxy dla kolizji
 * 4. Wypełnia niektóre obszary kolorem (flood fill)
 * 5. Na końcu rysuje gracza na wierzchu wszystkiego
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza
 *
 * @note Funkcja jest wywoływana w każdej klatce gry
 * @note Kolejność rysowania ma znaczenie - później rysowane obiekty są na wierzchu
 *
 * @see PrimitiveRenderer, Player, drawPointWithHitbox, drawLineWithHitbox,
 *      drawPolylineWithHitboxes, drawCircleWithHitbox, drawEllipseWithHitbox,
 *      drawPolygonWithHitbox, renderer.floodFill0
 */
void drawAllFigures(PrimitiveRenderer& renderer, Player& player);

#endif // DRAW_ALL_FIGURES_HPP