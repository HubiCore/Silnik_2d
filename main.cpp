#include "Engine.hpp"
#include "PrimitiveRenderer.hpp"
#include "Point2D.hpp"
#include "LineSegment.hpp"
#include "Player.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <map>

const float PI = 3.14159265358979323846f;

// ============================================================================
// HELPER CLASSES FOR DRAWING
// ============================================================================

/**
 * @class DrawablePoint2D
 * @brief Extends Point2D with drawing capability and color.
 */
class DrawablePoint2D : public Point2D {
private:
    sf::Color color;
public:
    DrawablePoint2D(float x = 0, float y = 0, sf::Color color = sf::Color::White)
        : Point2D(x, y), color(color) {}

    void setColor(sf::Color newColor) { color = newColor; }
    sf::Color getColor() const { return color; }

    void draw(PrimitiveRenderer& renderer) const {
        renderer.drawPoint(getX(), getY(), color);
    }
};

/**
 * @class DrawableLineSegment
 * @brief Extends LineSegment with drawing capability and color.
 */
class DrawableLineSegment : public LineSegment {
private:
    sf::Color color;
public:
    DrawableLineSegment(const Point2D& p1, const Point2D& p2, sf::Color color = sf::Color::White)
        : LineSegment(p1, p2), color(color) {}

    void setColor(sf::Color newColor) { color = newColor; }
    sf::Color getColor() const { return color; }

    void draw(PrimitiveRenderer& renderer) const {
        renderer.drawLine(getP1().getX(), getP1().getY(), getP2().getX(), getP2().getY(), color);
    }
};

// ============================================================================
// GEOMETRIC HELPER FUNCTIONS
// ============================================================================

/**
 * @brief Calculates vertices of a regular polygon.
 * @param sides Number of polygon sides (minimum 3)
 * @param radius Radius from center to vertex
 * @param center Center point of polygon
 * @param startAngle Starting angle in radians (default 0)
 * @return Vector of vertex points
 */
std::vector<sf::Vector2f> calculatePolygonPoints(int sides, float radius,
                                                  sf::Vector2f center, float startAngle = 0) {
    std::vector<sf::Vector2f> points;
    float angleStep = 2 * PI / sides;

    for (int i = 0; i < sides; ++i) {
        float angle = startAngle + i * angleStep;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);
        points.push_back(sf::Vector2f(x, y));
    }

    return points;
}

/**
 * @brief Creates precise hitbox for a line as a thin, rotated rectangle.
 * @param x1 Start X coordinate
 * @param y1 Start Y coordinate
 * @param x2 End X coordinate
 * @param y2 End Y coordinate
 * @param thickness Hitbox thickness in pixels (default 2px)
 * @return Vector of 4 rectangle points
 */
std::vector<sf::Vector2f> createLineHitbox(float x1, float y1, float x2, float y2,
                                            float thickness = 2.0f) {
    std::vector<sf::Vector2f> points;

    // Calculate line direction vector
    float dx = x2 - x1;
    float dy = y2 - y1;
    float length = std::sqrt(dx * dx + dy * dy);

    // Handle very short lines (almost points)
    if (length < 0.001f) {
        float halfThick = thickness / 2.0f;
        points.push_back(sf::Vector2f(x1 - halfThick, y1 - halfThick));
        points.push_back(sf::Vector2f(x1 + halfThick, y1 - halfThick));
        points.push_back(sf::Vector2f(x1 + halfThick, y1 + halfThick));
        points.push_back(sf::Vector2f(x1 - halfThick, y1 + halfThick));
        return points;
    }

    // Normalized direction vector
    float nx = dx / length;
    float ny = dy / length;

    // Perpendicular (normal) vector
    float px = -ny;
    float py = nx;

    // Half thickness for calculations
    float halfThickness = thickness / 2.0f;

    // Calculate 4 rectangle vertices
    points.push_back(sf::Vector2f(  // Top-left
        x1 + px * halfThickness - nx * halfThickness,
        y1 + py * halfThickness - ny * halfThickness
    ));

    points.push_back(sf::Vector2f(  // Top-right
        x2 + px * halfThickness + nx * halfThickness,
        y2 + py * halfThickness + ny * halfThickness
    ));

    points.push_back(sf::Vector2f(  // Bottom-right
        x2 - px * halfThickness + nx * halfThickness,
        y2 - py * halfThickness + ny * halfThickness
    ));

    points.push_back(sf::Vector2f(  // Bottom-left
        x1 - px * halfThickness - nx * halfThickness,
        y1 - py * halfThickness - ny * halfThickness
    ));

    return points;
}

// ============================================================================
// MAIN DRAWING FUNCTION
// ============================================================================

/**
 * @brief Draws all geometric figures and creates precise hitboxes for them.
 * @param renderer Reference to renderer
 * @param player Reference to player (for adding hitboxes)
 */
void drawAllFigures(PrimitiveRenderer& renderer, Player& player) {
    // Clear previous hitboxes
    player.clearCollisionObjects();

    // ------------------------------------------------------------------------
    // POINTS - small circles as hitboxes
    // ------------------------------------------------------------------------
    {
        DrawablePoint2D p1(100, 100, sf::Color::Yellow);
        DrawablePoint2D p2(200, 200, sf::Color::White);
        p1.draw(renderer);
        renderer.drawPoint(150, 150, sf::Color::White);

        // Point hitboxes as small circles (5px radius)
        player.addCollisionCircle(sf::Vector2f(100, 100), 5);
        player.addCollisionCircle(sf::Vector2f(150, 150), 5);
    }

    // ------------------------------------------------------------------------
    // LINES - thin, rotated rectangles as hitboxes
    // ------------------------------------------------------------------------
    {
        DrawablePoint2D p1(100, 100, sf::Color::Yellow);
        DrawablePoint2D p2(200, 200, sf::Color::White);
        DrawableLineSegment line(p1, p2, sf::Color::Red);
        line.draw(renderer);

        // Precise line hitbox
        std::vector<sf::Vector2f> lineHitbox = createLineHitbox(100, 100, 200, 200, 2.0f);
        player.addCollisionPolygon(lineHitbox);
    }

    // ------------------------------------------------------------------------
    // POLYLINES - each segment with individual hitbox
    // ------------------------------------------------------------------------
    {
        // Closed polyline definition
        std::vector<sf::Vector2f> polylinePoints = {
            {300,100}, {400,150}, {450,250}, {350,300}, {100,300}
        };

        // Draw different line types
        renderer.drawLine(250, 100, 400, 200, sf::Color::Green);
        renderer.drawLineIncremental(400, 100, 550, 200, sf::Color::Cyan);
        renderer.drawPolyLine(polylinePoints, true, sf::Color::Cyan);

        // Hitboxes for straight lines
        std::vector<sf::Vector2f> line1Hitbox = createLineHitbox(250, 100, 400, 200, 2.0f);
        player.addCollisionPolygon(line1Hitbox);

        std::vector<sf::Vector2f> line2Hitbox = createLineHitbox(400, 100, 550, 200, 2.0f);
        player.addCollisionPolygon(line2Hitbox);

        // Hitboxes for each polyline segment
        for (size_t i = 0; i < polylinePoints.size() - 1; i++) {
            float x1 = polylinePoints[i].x;
            float y1 = polylinePoints[i].y;
            float x2 = polylinePoints[i+1].x;
            float y2 = polylinePoints[i+1].y;

            std::vector<sf::Vector2f> segmentHitbox = createLineHitbox(x1, y1, x2, y2, 2.0f);
            player.addCollisionPolygon(segmentHitbox);
        }

        // Hitbox for closing line (if polyline is closed)
        if (polylinePoints.size() > 2) {
            float x1 = polylinePoints.back().x;
            float y1 = polylinePoints.back().y;
            float x2 = polylinePoints.front().x;
            float y2 = polylinePoints.front().y;

            std::vector<sf::Vector2f> closingHitbox = createLineHitbox(x1, y1, x2, y2, 2.0f);
            player.addCollisionPolygon(closingHitbox);
        }
    }

    // ------------------------------------------------------------------------
    // CIRCLES - perfect circles as hitboxes
    // ------------------------------------------------------------------------
    {
        renderer.drawCircle(600, 200, 40, sf::Color::Green, sf::Color::White);
        player.addCollisionCircle(sf::Vector2f(600, 200), 40);

        renderer.drawCircleSymmetric(700, 350, 60, sf::Color::Red);
        player.addCollisionCircle(sf::Vector2f(700, 350), 60);
    }

    // ------------------------------------------------------------------------
    // ELLIPSES - polygon approximations as hitboxes
    // ------------------------------------------------------------------------
    {
        renderer.drawEllipseSymmetric(500, 100, 80, 40, sf::Color::Yellow);

        std::vector<sf::Vector2f> ellipsePoints;
        int ellipseSegments = 32;
        for (int i = 0; i < ellipseSegments; i++) {
            float angle = 2 * PI * i / ellipseSegments;
            float x = 500 + 80 * std::cos(angle);
            float y = 100 + 40 * std::sin(angle);
            ellipsePoints.push_back(sf::Vector2f(x, y));
        }
        player.addCollisionPolygon(ellipsePoints);
    }

    // ------------------------------------------------------------------------
    // REGULAR POLYGONS - exact shapes as hitboxes
    // ------------------------------------------------------------------------
    {
        // 1. Equilateral triangle (vertex at top)
        float triangleRadius = 60;
        float triangleSideLength = 2 * triangleRadius * std::sin(PI / 3);
        renderer.drawPolygon(3, triangleSideLength, sf::Vector2f(200, 400), -PI/2, sf::Color::Red);

        std::vector<sf::Vector2f> trianglePoints = calculatePolygonPoints(3, triangleRadius,
                                                                          sf::Vector2f(200, 400), -PI/2);
        player.addCollisionPolygon(trianglePoints);

        // 2. Square rotated 45 degrees
        float squareRadius = 80;
        float squareSideLength = 2 * squareRadius * std::sin(PI / 4);
        renderer.drawPolygon(4, squareSideLength, sf::Vector2f(350, 400), PI/4, sf::Color::Green);

        std::vector<sf::Vector2f> squarePoints = calculatePolygonPoints(4, squareRadius,
                                                                        sf::Vector2f(350, 400), PI/4);
        player.addCollisionPolygon(squarePoints);

        // 3. Hexagon (vertex to the right)
        float hexagonRadius = 50;
        float hexagonSideLength = 2 * hexagonRadius * std::sin(PI / 6);
        renderer.drawPolygon(6, hexagonSideLength, sf::Vector2f(500, 400), 0, sf::Color::Red);

        std::vector<sf::Vector2f> hexagonPoints = calculatePolygonPoints(6, hexagonRadius,
                                                                         sf::Vector2f(500, 400), 0);
        player.addCollisionPolygon(hexagonPoints);

        // 4. Larger pentagon (vertex at top)
        float pentagonRadius1 = 80;
        float pentagonSideLength1 = 2 * pentagonRadius1 * std::sin(PI / 5);
        renderer.drawPolygon(5, pentagonSideLength1, sf::Vector2f(650, 300), -PI/2, sf::Color::Red);

        std::vector<sf::Vector2f> pentagonPoints1 = calculatePolygonPoints(5, pentagonRadius1,
                                                                           sf::Vector2f(650, 300), -PI/2);
        player.addCollisionPolygon(pentagonPoints1);

        // 5. Smaller pentagon (vertex at top)
        float pentagonRadius2 = 60;
        float pentagonSideLength2 = 2 * pentagonRadius2 * std::sin(PI / 5);
        renderer.drawPolygon(5, pentagonSideLength2, sf::Vector2f(500, 300), -PI/2, sf::Color::Red);

        std::vector<sf::Vector2f> pentagonPoints2 = calculatePolygonPoints(5, pentagonRadius2,
                                                                           sf::Vector2f(500, 300), -PI/2);
        player.addCollisionPolygon(pentagonPoints2);
    }

    // ------------------------------------------------------------------------
    // AREA FILLING - visual effect only, no hitboxes
    // ------------------------------------------------------------------------
    {
        renderer.floodFill0(200, 400, sf::Color(0,255,255,150), sf::Color::Green);
    }

    // ------------------------------------------------------------------------
    // DRAW PLAYER (on top of everything)
    // ------------------------------------------------------------------------
    player.draw(renderer);
}

// ============================================================================
// MAIN FUNCTION - PROGRAM ENTRY POINT
// ============================================================================

int main() {
    // Initialize graphics engine
    Engine engine;
    if (!engine.init("2D Engine with Precise Hitboxes", 800, 600, false, 144)) {
        return -1;
    }

    // Configure engine
    engine.setClearColor(sf::Color(50, 50, 50));
    engine.enableMouse(true);
    engine.enableKeyboard(true);

    // Get window pointer
    sf::RenderWindow* window = engine.getWindow();
    if (!window) {
        engine.log("ERROR: getWindow() == nullptr!");
        return -1;
    }

    // Initialize renderer and buffer
    PrimitiveRenderer renderer(window);
    sf::RenderTexture buffer;
    if (!buffer.create(800, 600)) {
        engine.log("ERROR: Unable to create RenderTexture!");
        return -1;
    }

    // Set game boundaries
    sf::FloatRect gameBounds(0, 0, 800, 600);

    // Create player
    Player player(400.f, 300.f, 5.0f);
    player.setBoundaries(gameBounds);

    // Load player sprites
    if (!player.loadSprites("C:/Users/huber/Desktop/Studia/Sprite")) {
        engine.log("Using placeholder sprites.");
    } else {
        engine.log("Player sprites loaded!");
    }

    // Display program information
    std::cout << "========================================" << std::endl;
    std::cout << "2D ENGINE WITH PRECISE HITBOXES" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "HITBOX SYSTEM:" << std::endl;
    std::cout << "  - Points:      Small circles (5px radius)" << std::endl;
    std::cout << "  - Lines:       Thin rotated rectangles (2px)" << std::endl;
    std::cout << "  - Circles:     Perfect circles" << std::endl;
    std::cout << "  - Ellipses:    Polygon approximations (32 segments)" << std::endl;
    std::cout << "  - Polygons:    Exact shapes" << std::endl;
    std::cout << std::endl;
    std::cout << "CONTROLS:" << std::endl;
    std::cout << "  - Movement:    W, A, S, D" << std::endl;
    std::cout << "  - Clear:       C (clear hitboxes)" << std::endl;
    std::cout << "  - Fill:        LMB (flood fill), RMB (boundary fill)" << std::endl;
    std::cout << "  - Exit:        ESC" << std::endl;
    std::cout << "  - Debug:       P (position), D (info)" << std::endl;
    std::cout << "========================================" << std::endl;

    // Start main loop
    engine.log("Main loop started.");
    sf::Clock clock;

    // MAIN GAME LOOP
    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Update player state
        player.update();

        // Event handling
        sf::Event event;
        while (window->pollEvent(event)) {
            // Window close event
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Mouse click - area filling
            if (event.type == sf::Event::MouseButtonPressed) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                // Draw everything to buffer
                buffer.clear(sf::Color(50, 50, 50));
                PrimitiveRenderer bufferRenderer(&buffer);
                drawAllFigures(bufferRenderer, player);

                // Fill based on mouse button
                if (event.mouseButton.button == sf::Mouse::Left) {
                    bufferRenderer.floodFill0(mouseX, mouseY, sf::Color::Blue, sf::Color(50, 50, 50));
                    engine.log("Flood fill at (" + std::to_string(mouseX) + ", " +
                               std::to_string(mouseY) + ")");
                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    bufferRenderer.boundaryFillIterative0(mouseX, mouseY, sf::Color::Yellow, sf::Color::Red);
                    engine.log("Boundary fill at (" + std::to_string(mouseX) + ", " +
                               std::to_string(mouseY) + ")");
                }

                buffer.display();
            }

            // Key press events
            if (event.type == sf::Event::KeyPressed) {
                // Exit program
                if (event.key.code == sf::Keyboard::Escape) {
                    window->close();
                }

                // Clear hitboxes (debug)
                if (event.key.code == sf::Keyboard::C) {
                    player.clearCollisionObjects();
                    std::cout << "All hitboxes cleared!" << std::endl;
                }

                // Show player position (debug)
                if (event.key.code == sf::Keyboard::P) {
                    sf::Vector2f pos = player.getPosition();
                    std::cout << "Player position: (" << pos.x << ", " << pos.y << ")" << std::endl;
                }
            }
        }

        // Draw current frame to buffer
        buffer.clear(sf::Color(50, 50, 50));
        PrimitiveRenderer bufferRenderer(&buffer);
        drawAllFigures(bufferRenderer, player);
        buffer.display();

        // Display buffer in window
        window->clear();
        sf::Sprite sprite(buffer.getTexture());
        window->draw(sprite);
        window->display();
    }

    // Program termination
    engine.log("Main loop ended.");
    return 0;
}