/*#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

constexpr float PI = 3.14159265358979323846f;

// Klasy pomocnicze
class DrawablePoint2D;
class DrawableLineSegment;

// Funkcje pomocnicze
std::vector<sf::Vector2f> calculatePolygonPoints(int sides, float radius,
                                                  sf::Vector2f center, float startAngle = 0);
std::vector<sf::Vector2f> createLineHitbox(float x1, float y1, float x2, float y2,
                                            float thickness = 2.0f);

#endif // HELPERS_HPP*/