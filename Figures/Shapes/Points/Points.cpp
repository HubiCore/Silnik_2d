#include "Points.hpp"
#include "../Helpers/Helpers.hpp"

void drawPointWithHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius) {
    // Rysuj punkt
    DrawablePoint2D point(x, y, color);
    point.draw(renderer);

    // Dodaj hitbox (małe kółko)
    player.addCollisionCircle(sf::Vector2f(x, y), hitboxRadius);
}

void drawPointWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius) {
    // Rysuj punkt
    DrawablePoint2D point(x, y, color);
    point.draw(renderer);
}