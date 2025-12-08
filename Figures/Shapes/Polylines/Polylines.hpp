/**
 * @file Polylines.hpp
 * @brief Deklaracje funkcji do rysowania polilinii
 * @defgroup Polylines Grupa funkcji polilinii
 *
 * Ten plik zawiera deklaracje funkcji do rysowania polilinii (łamanych) w grze.
 * Polilinia to sekwencja połączonych odcinków. Funkcje umożliwiają rysowanie
 * zarówno zamkniętych jak i otwartych polilinii z hitboxami lub bez.
 */

#ifndef POLYLINES_HPP
#define POLYLINES_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @brief Rysuje polilinię z hitboxami dla każdego segmentu
 * @ingroup Polylines
 *
 * Funkcja rysuje polilinię na ekranie i dodaje hitboxy kolizji dla każdego
 * segmentu linii. Dla zamkniętych polilinii dodaje również hitbox dla segmentu
 * zamykającego (od ostatniego do pierwszego punktu).
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza
 * @param points Wektor punktów definiujących polilinię (co najmniej 2 punkty)
 * @param closed Flaga określająca czy polilinia ma być zamknięta
 * @param color Kolor polilinii
 * @param thickness Grubość linii (domyślnie 2.0)
 *
 */
void drawPolylineWithHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness = 2.0f);

/**
 * @brief Rysuje polilinię bez hitboxów
 * @ingroup Polylines
 *
 * Funkcja rysuje polilinię na ekranie bez tworzenia hitboxów kolizji.
 * Szybsza i lżejsza wersja funkcji drawPolylineWithHitboxes, przeznaczona
 * dla elementów dekoracyjnych, tła lub obiektów nieinteraktywnych.
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza (parametr zachowany dla spójności API)
 * @param points Wektor punktów definiujących polilinię
 * @param closed Flaga określająca czy polilinia ma być zamknięta
 * @param color Kolor polilinii
 * @param thickness Grubość linii (domyślnie 2.0)
 *
 * @see drawPolylineWithHitboxes()
 */
void drawPolylineWithoutHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness = 2.0f);

#endif // POLYLINES_HPP