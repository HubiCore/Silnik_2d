#include "Circles.hpp"

void drawCircleWithHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor) {
    // Rysuj okrąg
    renderer.drawCircle(centerX, centerY, radius, outlineColor, fillColor);
    
    // Dodaj hitbox (dokładne kółko)
    player.addCollisionCircle(sf::Vector2f(centerX, centerY), radius);
}

void drawCircleSymmetricWithHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color) {
    // Rysuj okrąg (wersja symetryczna)
    renderer.drawCircleSymmetric(centerX, centerY, radius, color);
    
    // Dodaj hitbox (dokładne kółko)
    player.addCollisionCircle(sf::Vector2f(centerX, centerY), radius);
}

void drawCircleWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor) {
    // Rysuj okrąg
    renderer.drawCircle(centerX, centerY, radius, outlineColor, fillColor);
}

void drawCircleSymmetricWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color) {
    // Rysuj okrąg (wersja symetryczna)
    renderer.drawCircleSymmetric(centerX, centerY, radius, color);
}