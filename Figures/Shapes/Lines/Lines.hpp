#ifndef LINES_HPP
#define LINES_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>

// Funkcje dla linii
void drawLineWithHitbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness = 2.0f);

void drawLineWithHitoutbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness = 2.0f);
#endif // LINES_HPP