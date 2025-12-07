#ifndef ELLIPSES_HPP
#define ELLIPSES_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// Funkcje dla elips
void drawEllipseWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments = 32);
void drawEllipseWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments = 32);
#endif // ELLIPSES_HPP