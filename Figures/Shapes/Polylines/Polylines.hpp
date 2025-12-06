#ifndef POLYLINES_HPP
#define POLYLINES_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// Funkcje dla polilinii
void drawPolylineWithHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness = 2.0f);
void drawPredefinedPolylines(PrimitiveRenderer& renderer, Player& player);

#endif // POLYLINES_HPP