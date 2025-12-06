#include "Lines.hpp"
#include "../Helpers/Helpers.hpp"

void drawLineWithHitbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness) {
    // Rysuj linię
    DrawablePoint2D p1(x1, y1, color);
    DrawablePoint2D p2(x2, y2, color);
    DrawableLineSegment line(p1, p2, color);
    line.draw(renderer);

    // Dodaj hitbox (obrócony prostokąt)
    std::vector<sf::Vector2f> lineHitbox = createLineHitbox(x1, y1, x2, y2, thickness);
    player.addCollisionPolygon(lineHitbox);
}