/**
 * @file Points.hpp
 * @brief Deklaracja funkcji rysowania punktów z hitboxami i bez
 *
 * Plik zawiera funkcje do rysowania punktów graficznych z opcjonalnymi
 * hitboxami dla wykrywania kolizji z graczem.
 */

#ifndef POINTS_HPP
#define POINTS_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>

/**
 * @defgroup DrawingPoints Funkcje rysowania punktów
 * @{
 */

/**
 * @brief Rysuje punkt z kolistym hitboxem
 *
 * Funkcja rysuje punkt w określonym miejscu i dodaje kolisty hitbox
 * do systemu kolizji gracza. Punkt jest widoczny graficznie, a hitbox
 * służy do wykrywania kolizji.
 *
 * @code{.cpp}
 * // Przykład użycia:
 * drawPointWithHitbox(renderer, player, 100.0f, 150.0f, sf::Color::Red, 8.0f);
 * @endcode
 *
 * @param renderer Referencja do obiektu renderera primitywów
 * @param player Referencja do obiektu gracza (dla systemu kolizji)
 * @param x Współrzędna X punktu w pikselach
 * @param y Współrzędna Y punktu w pikselach
 * @param color Kolor punktu w formacie sf::Color
 * @param hitboxRadius Promień hitboxu w pikselach (domyślnie 5.0)
 *
 * @warning Hitbox jest dodawany do gracza - upewnij się, że obiekt Player
 *          zarządza pamięcią dla hitboxów prawidłowo
 *
 * @see Player::addCollisionCircle()
 * @see DrawablePoint2D
 */
void drawPointWithHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius = 5.0f);

/**
 * @brief Rysuje punkt bez hitboxu
 *
 * Funkcja rysuje punkt czysto wizualnie bez dodawania hitboxu.
 * Przydatne dla elementów dekoracyjnych lub tła.
 *
 * @param renderer Referencja do obiektu renderera primitywów
 * @param player Referencja do obiektu gracza (parametr zachowany dla zgodności interfejsu)
 * @param x Współrzędna X punktu w pikselach
 * @param y Współrzędna Y punktu w pikselach
 * @param color Kolor punktu w formacie sf::Color
 * @param hitboxRadius Parametr ignorowany, zachowany dla zgodności (domyślnie 5.0)
 *
 * @note Parametr player nie jest używany, ale pozostawiono go dla
 *       spójności z drawPointWithHitbox()
 *
 * @deprecated Rozważ użycie bezpośrednio DrawablePoint2D dla czysto wizualnych punktów
 */
void drawPointWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius = 5.0f);

/** @} */ // koniec grupy DrawingPoints

#endif // POINTS_HPP