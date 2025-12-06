#ifndef DRAW_ALL_FIGURES_HPP
#define DRAW_ALL_FIGURES_HPP

#include "../../Object/Renderer/PrimitiveRenderer.hpp"
#include "../../Player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

// Deklaracja głównej funkcji rysującej
void drawAllFigures(PrimitiveRenderer& renderer, Player& player);

// Funkcje dla poszczególnych kształtów
void drawPointWithHitbox(PrimitiveRenderer& renderer, Player& player,
                         float x, float y, sf::Color color, float hitboxRadius = 5.0f);
void drawLineWithHitbox(PrimitiveRenderer& renderer, Player& player,
                        float x1, float y1, float x2, float y2,
                        sf::Color color, float thickness = 2.0f);
void drawPolylineWithHitboxes(PrimitiveRenderer& renderer, Player& player,
                              const std::vector<sf::Vector2f>& points,
                              bool closed, sf::Color color, float thickness = 2.0f);
void drawCircleWithHitbox(PrimitiveRenderer& renderer, Player& player,
                          float centerX, float centerY, float radius,
                          sf::Color outlineColor, sf::Color fillColor = sf::Color::Transparent);
void drawCircleSymmetricWithHitbox(PrimitiveRenderer& renderer, Player& player,
                                   float centerX, float centerY, float radius,
                                   sf::Color color);
void drawEllipseWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           float centerX, float centerY, float radiusX, float radiusY,
                           sf::Color color, int segments = 32);
void drawPolygonWithHitbox(PrimitiveRenderer& renderer, Player& player,
                           int sides, float sideLength,
                           sf::Vector2f center, float startAngle,
                           sf::Color color);

// Funkcje dostępu do predefiniowanych obiektów
void drawPredefinedPoints(PrimitiveRenderer& renderer, Player& player);
void drawPredefinedLines(PrimitiveRenderer& renderer, Player& player);
void drawPredefinedPolylines(PrimitiveRenderer& renderer, Player& player);
void drawPredefinedCircles(PrimitiveRenderer& renderer, Player& player);
void drawPredefinedEllipses(PrimitiveRenderer& renderer, Player& player);
void drawPredefinedPolygons(PrimitiveRenderer& renderer, Player& player);

// Funkcje pomocnicze
std::vector<sf::Vector2f> createLineHitbox(float x1, float y1, float x2, float y2,
                                            float thickness = 2.0f);
std::vector<sf::Vector2f> calculatePolygonPoints(int sides, float radius,
                                                  sf::Vector2f center, float startAngle = 0);

#endif // DRAW_ALL_FIGURES_HPP