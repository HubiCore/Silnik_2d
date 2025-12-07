#include "Polylines.hpp"
#include "../Helpers/Helpers.hpp"
#include <cmath>

void drawPolylineWithHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness) {
    // Rysuj polilinię
    renderer.drawPolyLine(points, closed, color);

    // Hitboxy dla każdego segmentu
    for (size_t i = 0; i < points.size() - 1; i++) {
        float x1 = points[i].x;
        float y1 = points[i].y;
        float x2 = points[i+1].x;
        float y2 = points[i+1].y;

        std::vector<sf::Vector2f> segmentHitbox = createLineHitbox(x1, y1, x2, y2, thickness);
        player.addCollisionPolygon(segmentHitbox);
    }



    // Hitbox dla zamykającego segmentu (jeśli polilinia jest zamknięta)
    if (closed && points.size() > 2) {
        float x1 = points.back().x;
        float y1 = points.back().y;
        float x2 = points.front().x;
        float y2 = points.front().y;

        std::vector<sf::Vector2f> closingHitbox = createLineHitbox(x1, y1, x2, y2, thickness);
        player.addCollisionPolygon(closingHitbox);
    }
}

void drawPolylineWithoutHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness) {
    // Rysuj polilinię
    renderer.drawPolyLine(points, closed, color);
}