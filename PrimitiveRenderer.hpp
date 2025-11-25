#ifndef PRIMITIVERENDERER_HPP
#define PRIMITIVERENDERER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class PrimitiveRenderer {
private:
    sf::RenderTarget* target;

public:
    PrimitiveRenderer(sf::RenderTarget* target = nullptr);

    void setTarget(sf::RenderTarget* target);
    sf::RenderTarget* getTarget() { return target; }

    void drawPoint(float x, float y, sf::Color color);
    void drawLine(float x1, float y1, float x2, float y2, sf::Color color);
    void drawLineIncremental(float x1, float y1, float x2, float y2, sf::Color color);
    void drawPolyLine(const std::vector<sf::Vector2f> &points, bool closed, sf::Color color);
    void drawCircle(float x, float y, float radius, sf::Color color, sf::Color color2 = sf::Color::Transparent);
    void drawCircleSymmetric(float x0, float y0, float R, sf::Color color);
    void drawElipse(float x0, float y0, float Rx, float Ry, sf::Color color);
    void drawEllipseSymmetric(float x0, float y0, float Rx, float Ry, sf::Color color);
    void drawPolygon(int sides, float sideLength, sf::Vector2f center, float startAngle, sf::Color color);

    void floodFill0(int sx, int sy, sf::Color fillColor, sf::Color backgroundColor);
    void boundaryFillIterative0(int sx, int sy, sf::Color fillColor, sf::Color boundaryColor);
};

#endif
