#include "PrimitiveRenderer.hpp"
#include <cmath>
#include <functional>
#include <stack>
#include <utility>
#include <stdio.h>
#include <queue>

PrimitiveRenderer::PrimitiveRenderer(sf::RenderTarget* target) : target(target) {}

void PrimitiveRenderer::setTarget(sf::RenderTarget* target) {
    this->target = target;
}

void PrimitiveRenderer::drawPoint(float x, float y, sf::Color color) {
    if (!target) return;

    sf::Vertex point(sf::Vector2f(x, y), color);
    target->draw(&point, 1, sf::Points);
}

void PrimitiveRenderer::drawLine(float x1, float y1, float x2, float y2, sf::Color color) {
    if (!target) return;

    sf::Vertex line[] = {{sf::Vector2f(x1, y1), color}, {sf::Vector2f(x2, y2), color}};
    target->draw(line, 2, sf::Lines);
}

void PrimitiveRenderer::drawLineIncremental(float x1, float y1, float x2, float y2, sf::Color color) {
    if (!target) return;

    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = std::max(std::abs(dx), std::abs(dy));

    if (steps == 0) {
        drawPoint(x1, y1, color);
        return;
    }

    float xInc = dx / steps;
    float yInc = dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++) {
        drawPoint(x, y, color);
        x += xInc;
        y += yInc;
    }
}

void PrimitiveRenderer::drawPolyLine(const std::vector<sf::Vector2f> &points, bool closed, sf::Color color) {
    if (!target || points.size() < 2) return;

    for (size_t i = 0; i < points.size() - 1; i++)
        drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, color);

    if (closed) {
        drawLine(points.back().x, points.back().y, points.front().x, points.front().y, color);
    }
}

void PrimitiveRenderer::drawCircle(float x, float y, float radius, sf::Color color, sf::Color color2) {
    if (!target) return;

    sf::CircleShape shape(radius);
    shape.setFillColor(color);
    shape.setOutlineColor(color2);
    shape.setPosition(x, y);
    shape.setOrigin(radius, radius);
    target->draw(shape);
}

void PrimitiveRenderer::drawCircleSymmetric(float x0, float y0, float R, sf::Color color) {
    if (!target) return;

    float x = 0, y = R;
    float d = 3 - 2 * R;

    auto draw8 = [&](float x, float y) {
        drawPoint(x0 + x, y0 + y, color);
        drawPoint(x0 - x, y0 + y, color);
        drawPoint(x0 + x, y0 - y, color);
        drawPoint(x0 - x, y0 - y, color);
        drawPoint(x0 + y, y0 + x, color);
        drawPoint(x0 - y, y0 + x, color);
        drawPoint(x0 + y, y0 - x, color);
        drawPoint(x0 - y, y0 - x, color);
    };

    while (x <= y) {
        draw8(x, y);
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void PrimitiveRenderer::drawElipse(float x0, float y0, float Rx, float Ry, sf::Color color) {
    if (!target) return;

    sf::ConvexShape elipse;
    unsigned int detail = 100;
    elipse.setPointCount(detail);

    for (unsigned int i = 0; i < detail; ++i) {
        float rad = 2 * M_PI * i / detail;
        float x = std::cos(rad) * Rx;
        float y = std::sin(rad) * Ry;
        elipse.setPoint(i, sf::Vector2f(x, y));
    }

    elipse.setPosition(x0, y0);
    elipse.setFillColor(color);
    elipse.setOrigin(Rx, Ry);
    target->draw(elipse);
}

void PrimitiveRenderer::drawEllipseSymmetric(float x0, float y0, float Rx, float Ry, sf::Color color) {
    if (!target) return;

    float Rx2 = Rx * Rx;
    float Ry2 = Ry * Ry;
    float x = 0, y = Ry;

    float p1 = Ry2 - (Rx2 * Ry) + (0.25f * Rx2);
    float dx = 2 * Ry2 * x;
    float dy = 2 * Rx2 * y;

    while (dx < dy) {
        drawPoint(x0 + x, y0 + y, color);
        drawPoint(x0 - x, y0 + y, color);
        drawPoint(x0 + x, y0 - y, color);
        drawPoint(x0 - x, y0 - y, color);

        if (p1 < 0) {
            x++;
            dx = 2 * Ry2 * x;
            p1 = p1 + dx + Ry2;
        } else {
            x++;
            y--;
            dx = 2 * Ry2 * x;
            dy = 2 * Rx2 * y;
            p1 = p1 + dx - dy + Ry2;
        }
    }

    float p2 = Ry2 * (x + 0.5f) * (x + 0.5f) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2;
    while (y >= 0) {
        drawPoint(x0 + x, y0 + y, color);
        drawPoint(x0 - x, y0 + y, color);
        drawPoint(x0 + x, y0 - y, color);
        drawPoint(x0 - x, y0 - y, color);

        if (p2 > 0) {
            y--;
            dy = 2 * Rx2 * y;
            p2 = p2 + Rx2 - dy;
        } else {
            y--;
            x++;
            dx = 2 * Ry2 * x;
            dy = 2 * Rx2 * y;
            p2 = p2 + dx - dy + Rx2;
        }
    }
}

void PrimitiveRenderer::drawPolygon(int sides, float sideLength, sf::Vector2f center, float startAngle, sf::Color color) {
    if (!target || sides < 3) return;

    std::vector<sf::Vector2f> points;
    float radius = sideLength / (2 * sin(M_PI / sides));
    float angleStep = 2 * M_PI / sides;

    for (int i = 0; i < sides; ++i) {
        float angle = startAngle + i * angleStep;
        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        points.push_back(sf::Vector2f(x, y));
    }

    drawPolyLine(points, true, color);
}

void PrimitiveRenderer::floodFill0(int sx, int sy, sf::Color fillColor, sf::Color backgroundColor) {
    if (!target) return;

    int w = target->getSize().x;
    int h = target->getSize().y;
    if (sx < 0 || sy < 0 || sx >= w || sy >= h) return;

    sf::Texture tex;
    tex.create(w, h);

    sf::Image img;
    if (dynamic_cast<sf::RenderWindow*>(target)) {
        tex.update(*dynamic_cast<sf::RenderWindow*>(target));
        img = tex.copyToImage();
    } else if (dynamic_cast<sf::RenderTexture*>(target)) {
        img = dynamic_cast<sf::RenderTexture*>(target)->getTexture().copyToImage();
    } else {
        return;
    }

    sf::Color startColor = img.getPixel(sx, sy);
    if (startColor == fillColor) return;

    std::queue<std::pair<int, int>> queue;
    queue.push({sx, sy});

    while (!queue.empty()) {
        auto [x, y] = queue.front();
        queue.pop();

        if (x < 0 || y < 0 || x >= w || y >= h) continue;
        if (img.getPixel(x, y) != startColor) continue;

        img.setPixel(x, y, fillColor);

        queue.push({x + 1, y});
        queue.push({x - 1, y});
        queue.push({x, y + 1});
        queue.push({x, y - 1});
    }

    sf::Texture filledTexture;
    filledTexture.loadFromImage(img);
    sf::Sprite filledSprite(filledTexture);
    target->draw(filledSprite);
}

void PrimitiveRenderer::boundaryFillIterative0(int sx, int sy, sf::Color fillColor, sf::Color boundaryColor) {
    if (!target) return;

    int w = target->getSize().x;
    int h = target->getSize().y;
    if (sx < 0 || sy < 0 || sx >= w || sy >= h) return;

    sf::Texture tex;
    tex.create(w, h);

    sf::Image img;
    if (dynamic_cast<sf::RenderWindow*>(target)) {
        tex.update(*dynamic_cast<sf::RenderWindow*>(target));
        img = tex.copyToImage();
    } else if (dynamic_cast<sf::RenderTexture*>(target)) {
        img = dynamic_cast<sf::RenderTexture*>(target)->getTexture().copyToImage();
    } else {
        return;
    }

    std::queue<std::pair<int, int>> pixels;
    pixels.push({sx, sy});

    while (!pixels.empty()) {
        auto [x, y] = pixels.front();
        pixels.pop();

        if (x < 0 || y < 0 || x >= w || y >= h) continue;

        sf::Color current = img.getPixel(x, y);
        if (current == fillColor || current == boundaryColor) continue;

        img.setPixel(x, y, fillColor);

        pixels.push({x, y - 1});
        pixels.push({x, y + 1});
        pixels.push({x - 1, y});
        pixels.push({x + 1, y});
    }

    sf::Texture filledTexture;
    filledTexture.loadFromImage(img);
    sf::Sprite filledSprite(filledTexture);
    target->draw(filledSprite);
}