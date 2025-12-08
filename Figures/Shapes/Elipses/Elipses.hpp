#ifndef ELLIPSES_HPP
#define ELLIPSES_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @file Elipses.hpp
 * @brief Deklaracje funkcji do rysowania elips z obsługą kolizji
 * @ingroup Graphics
 */

/**
 * @brief Rysuje elipsę z hitboxem do wykrywania kolizji
 *
 * Funkcja rysuje elipsę za pomocą renderera
 * Hitbox jest aproksymowany wielokątem o określonej liczbie segmentów dla lepszej dokładności wykrywania kolizji.
 * @param renderer Referencja do obiektu renderera rysującego prymitywy
 * @param player Referencja do obiektu gracza, do którego dodawany jest hitbox
 * @param centerX Współrzędna X środka elipsy
 * @param centerY Współrzędna Y środka elipsy
 * @param radiusX Promień elipsy w osi X
 * @param radiusY Promień elipsy w osi Y
 * @param color Kolor elipsy w formacie SFML Color
 * @param segments Liczba segmentów używanych do aproksymacji elipsy (domyślnie 32)
 * @see drawEllipseWithoutHitbox()
 * @see PrimitiveRenderer::drawEllipseSymmetric()
 * @see Player::addCollisionPolygon()
 */
void drawEllipseWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments = 32);

/**
 * @brief Rysuje elipsę bez hitboxu kolizyjnego
 *
 * Funkcja rysuje elipsę za pomocą renderera bez dodawania hitboxu do gracza.
 * @param renderer Referencja do obiektu renderera rysującego prymitywy
 * @param player Referencja do obiektu gracza (parametr dla zachowania zgodności interfejsu)
 * @param centerX Współrzędna X środka elipsy
 * @param centerY Współrzędna Y środka elipsy
 * @param radiusX Promień elipsy w osi X
 * @param radiusY Promień elipsy w osi Y
 * @param color Kolor elipsy w formacie SFML Color
 * @param segments Liczba segmentów używanych do aproksymacji elipsy (domyślnie 32)
 *
 * @see drawEllipseWithHitbox()
 * @see PrimitiveRenderer::drawEllipseSymmetric()
 */
void drawEllipseWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments = 32);

#endif // ELLIPSES_HPP


