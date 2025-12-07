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
void drawCircleWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor = sf::Color::Transparent);
void drawCircleSymmetricWithoutHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color);
#endif // CIRCLES_HPP