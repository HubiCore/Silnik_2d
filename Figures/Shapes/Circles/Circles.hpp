#ifndef CIRCLES_HPP
#define CIRCLES_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>

/**
 * @file Circles.hpp
 * @brief Deklaracje funkcji do rysowania okręgów z obsługą kolizji
 * @ingroup Graphics
 */

/**
 * @defgroup CircleFunctions Funkcje okręgów
 * @brief Zbiór funkcji do rysowania okręgów z różnymi opcjami renderowania i kolizji
 */

/**
 * @brief Rysuje okrąg z obramowaniem i wypełnieniem wraz z hitboxem kolizyjnym
 *
 * Funkcja rysuje okrąg używając podstawowego algorytmu renderera i dodaje
 * dokładny kolisty hitbox do gracza. Okrąg może mieć określony kolor obramowania
 * i wypełnienia.
 *
 * @param renderer Referencja do obiektu renderera prymitywów
 * @param player Referencja do obiektu gracza, do którego dodawany jest hitbox
 * @param centerX Współrzędna X środka okręgu
 * @param centerY Współrzędna Y środka okręgu
 * @param radius Promień okręgu
 * @param outlineColor Kolor obramowania okręgu
 * @param fillColor Kolor wypełnienia okręgu (domyślnie przezroczysty)
 *
 * @note Hitbox jest dokładnym okręgiem, co ułatwia precyzyjne wykrywanie kolizji
 * @warning Duża liczba okręgów z hitboxami może wpłynąć na wydajność
 *
 * @see drawCircleWithoutHitbox()
 * @see drawCircleSymmetricWithHitbox()
 * @see PrimitiveRenderer::drawCircle()
 * @see Player::addCollisionCircle()
 *
 * @ingroup CircleFunctions
 */
void drawCircleWithHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor = sf::Color::Transparent);

/**
 * @brief Rysuje okrąg używając symetrycznego algorytmu z hitboxem kolizyjnym
 *
 * Funkcja rysuje okrąg używając symetrycznego algorytmu renderera (szybszego
 * i bardziej efektywnego) i dodaje dokładny kolisty hitbox do gracza.
 * Okrąg jest rysowany jednolitym kolorem.
 *
 * @param renderer Referencja do obiektu renderera prymitywów
 * @param player Referencja do obiektu gracza, do którego dodawany jest hitbox
 * @param centerX Współrzędna X środka okręgu
 * @param centerY Współrzędna Y środka okręgu
 * @param radius Promień okręgu
 * @param color Kolor okręgu
 *
 * @note Algorytm symetryczny jest optymalizowany pod kątem wydajności
 * @see drawCircleSymmetricWithoutHitbox()
 * @see drawCircleWithHitbox()
 * @see PrimitiveRenderer::drawCircleSymmetric()
 *
 * @ingroup CircleFunctions
 */
void drawCircleSymmetricWithHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color);

/**
 * @brief Rysuje okrąg z obramowaniem i wypełnieniem bez hitboxu kolizyjnego
 *
 * Funkcja rysuje okrąg używając podstawowego algorytmu renderera, ale bez
 * dodawania hitboxu do gracza. Przydatna dla obiektów dekoracyjnych lub tła.
 *
 * @param renderer Referencja do obiektu renderera prymitywów
 * @param player Referencja do obiektu gracza (zachowanie zgodności interfejsu)
 * @param centerX Współrzędna X środka okręgu
 * @param centerY Współrzędna Y środka okręgu
 * @param radius Promień okręgu
 * @param outlineColor Kolor obramowania okręgu
 * @param fillColor Kolor wypełnienia okręgu (domyślnie przezroczysty)
 *
 * @note Funkcja nie modyfikuje stanu gracza
 * @see drawCircleWithHitbox()
 * @see drawCircleSymmetricWithoutHitbox()
 *
 * @ingroup CircleFunctions
 */
void drawCircleWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor = sf::Color::Transparent);

/**
 * @brief Rysuje okrąg używając symetrycznego algorytmu bez hitboxu kolizyjnego
 *
 * Funkcja rysuje okrąg używając symetrycznego algorytmu renderera bez dodawania
 * hitboxu do gracza. Optymalna dla rysowania wielu obiektów dekoracyjnych.
 *
 * @param renderer Referencja do obiektu renderera prymitywów
 * @param player Referencja do obiektu gracza (zachowanie zgodności interfejsu)
 * @param centerX Współrzędna X środka okręgu
 * @param centerY Współrzędna Y środka okręgu
 * @param radius Promień okręgu
 * @param color Kolor okręgu
 *
 * @note Najbardziej wydajna opcja dla okręgów bez kolizji
 * @see drawCircleSymmetricWithHitbox()
 * @see drawCircleWithoutHitbox()
 *
 * @ingroup CircleFunctions
 */
void drawCircleSymmetricWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color);

#endif // CIRCLES_HPP