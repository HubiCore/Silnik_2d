/**
 * @file Lines.hpp
 * @brief Nagłówki funkcji do rysowania linii z hitboxem i bez
 * @defgroup Lines Grupa funkcji linii
 *
 * Ten plik zawiera deklaracje funkcji do rysowania linii w grze.
 * Funkcje umożliwiają rysowanie linii z dodawaniem hitboxów do wykrywania kolizji
 * lub bez hitboxów dla elementów dekoracyjnych.
 */

#ifndef LINES_HPP
#define LINES_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>

/**
 * @brief Rysuje linię z hitboxem do wykrywania kolizji
 * @ingroup Lines
 *
 * Funkcja rysuje linię na ekranie i dodaje do gracza wielokąt kolizji
 * w kształcie prostokąta otaczającego linię.
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza
 * @param x1 Współrzędna X początku linii
 * @param y1 Współrzędna Y początku linii
 * @param x2 Współrzędna X końca linii
 * @param y2 Współrzędna Y końca linii
 * @param color Kolor linii
 * @param thickness Grubość linii (domyślnie 2.0)
 *
 * @see createLineHitbox()
 */
void drawLineWithHitbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness = 2.0f);

/**
 * @brief Rysuje linię bez hitboxu
 * @ingroup Lines
 * @warning Ta funkcja nie dodaje hitboxu - użyj dla elementów dekoracyjnych
 *
 * Funkcja rysuje linię na ekranie bez tworzenia hitboxu kolizji.
 * Idealna dla tła, efektów wizualnych i elementów nieinteraktywnych.
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza (nieużywana, zachowana dla spójności API)
 * @param x1 Współrzędna X początku linii
 * @param y1 Współrzędna Y początku linii
 * @param x2 Współrzędna X końca linii
 * @param y2 Współrzędna Y końca linii
 * @param color Kolor linii
 * @param thickness Grubość linii (domyślnie 2.0)
 *
 * @see drawLineWithHitbox()
 */
void drawLineWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness = 2.0f);

#endif // LINES_HPP