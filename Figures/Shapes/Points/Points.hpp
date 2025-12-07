#ifndef POINTS_HPP
#define POINTS_HPP

#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>

// Funkcje dla punktów
void drawPointWithHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius = 5.0f);

void drawPointWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius = 5.0f);
#endif // POINTS_HPP