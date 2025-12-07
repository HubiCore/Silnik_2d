#include "Circles.hpp"

/**
 * @file Circles.cpp
 * @brief Implementacje funkcji do rysowania okręgów
 * @ingroup Graphics
 */

/**
 * @brief Implementacja drawCircleWithHitbox
 *
 * Rysuje okrąg z obramowaniem i wypełnieniem oraz dodaje dokładny okrągły hitbox.
 * Wykorzystuje podstawowy algorytm renderowania okręgów.
 */
void drawCircleWithHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor) {
    // Rysuj okrąg używając podstawowego algorytmu
    renderer.drawCircle(centerX, centerY, radius, outlineColor, fillColor);

    // Dodaj hitbox jako dokładny okrąg
    player.addCollisionCircle(sf::Vector2f(centerX, centerY), radius);
}

/**
 * @brief Implementacja drawCircleSymmetricWithHitbox
 *
 * Rysuje okrąg używając symetrycznego algorytmu (bardziej wydajnego) i dodaje
 * okrągły hitbox. Okrąg jest rysowany jednolitym kolorem.
 */
void drawCircleSymmetricWithHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color) {
    // Rysuj okrąg używając symetrycznego algorytmu (optymalizacja wydajności)
    renderer.drawCircleSymmetric(centerX, centerY, radius, color);

    // Dodaj hitbox jako dokładny okrąg
    player.addCollisionCircle(sf::Vector2f(centerX, centerY), radius);
}

/**
 * @brief Implementacja drawCircleWithoutHitbox
 *
 * Rysuje okrąg z obramowaniem i wypełnieniem bez dodawania hitboxu.
 * Przydatna dla obiektów dekoracyjnych lub efektów wizualnych.
 */
void drawCircleWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor) {
    // Rysuj okrąg bez dodawania hitboxu (tylko wizualnie)
    renderer.drawCircle(centerX, centerY, radius, outlineColor, fillColor);

    // Celowo pominięte: player.addCollisionCircle()
    // Obiekt jest tylko wizualny, bez kolizji
}

/**
 * @brief Implementacja drawCircleSymmetricWithoutHitbox
 *
 * Rysuje okrąg używając symetrycznego algorytmu bez dodawania hitboxu.
 * Najbardziej wydajna opcja dla obiektów czysto wizualnych.
 */
void drawCircleSymmetricWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color) {
    // Rysuj okrąg używając symetrycznego algorytmu (najszybsza opcja)
    renderer.drawCircleSymmetric(centerX, centerY, radius, color);

    // Celowo pominięte: player.addCollisionCircle()
    // Obiekt jest tylko wizualny, bez kolizji
}