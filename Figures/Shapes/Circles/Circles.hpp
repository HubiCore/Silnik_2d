#ifndef CIRCLES_HPP
#define CIRCLES_HPP


#include "../../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../../Player/Player.hpp"
#include <SFML/Graphics.hpp>

// Funkcje dla okręgów
void drawCircleWithHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor = sf::Color::Transparent);
void drawCircleSymmetricWithHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color);
void drawPredefinedCircles(PrimitiveRenderer& renderer, Player& player);

#endif // CIRCLES_HPP