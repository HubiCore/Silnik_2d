#ifndef POLYGONS_HPP
#define POLYGONS_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// Funkcje dla wielokątów
void drawPolygonWithHitbox(PrimitiveRenderer &renderer, Player &player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color);

void drawPolygonWithoutHitbox(PrimitiveRenderer &renderer, Player &player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color);
#endif // POLYGONS_HPP