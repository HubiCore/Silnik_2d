#include "Engine.hpp"
#include "PrimitiveRenderer.hpp"
#include "Point2D.hpp"
#include "LineSegment.hpp"
#include <vector>
#include <cmath>

void drawAllFigures(PrimitiveRenderer& renderer) {

    Point2D p1(100, 100);
    Point2D p2(200, 200);
    LineSegment line(p1, p2);

    std::vector<sf::Vector2f> polylinePoints = {
        {300, 100}, {400, 150}, {450, 250}, {350, 300}, {100, 300}
    };

    p1.draw(renderer, sf::Color::Yellow);
    renderer.drawPoint(150, 150, sf::Color::White);

    line.draw(renderer, false, sf::Color::Red);
    renderer.drawLine(250, 100, 400, 200, sf::Color::Green);
    renderer.drawLineIncremental(400, 100, 550, 200, sf::Color::Cyan);

    renderer.drawPolyLine(polylinePoints, true, sf::Color::Cyan);

    std::vector<sf::Vector2f> openLine = {{600, 100}, {650, 130}, {700, 200}};
    renderer.drawPolyLine(openLine, false, sf::Color::White);

    renderer.drawCircle(600, 200, 40, sf::Color::Green, sf::Color::White);
    renderer.drawCircleSymmetric(700, 350, 60, sf::Color::Red);

    renderer.drawElipse(600, 500, 100, 60, sf::Color::Magenta);
    renderer.drawEllipseSymmetric(900, 400, 80, 40, sf::Color::Yellow);

    renderer.drawPolygon(3, 60, {200, 400}, 0, sf::Color::Red);
    renderer.drawPolygon(4, 80, {350, 400}, M_PI / 4, sf::Color::Green);
    renderer.drawPolygon(6, 50, {500, 400}, 0, sf::Color::Red);

    renderer.drawPolygon(5, 80, {1300, 300}, 0, sf::Color::Red);
    renderer.drawPolygon(5, 100, {1000, 300}, 0, sf::Color::Red);

    renderer.floodFill0(200, 400, sf::Color(0, 255, 255, 150), sf::Color::Green);

}

int main()
{
    Engine engine;

    if (!engine.init("Simple engine", 800, 600, true, 144))
        return -1;

    engine.setClearColor(sf::Color(50, 50, 50));
    engine.enableMouse(true);
    engine.enableKeyboard(true);

    sf::RenderWindow* window = engine.getWindow();
    if (!window) {
        engine.log("ERROR: getWindow() == nullptr!");
        return -1;
    }

    PrimitiveRenderer renderer(window);

    sf::RenderTexture buffer;
    if (!buffer.create(800, 600)) {
        engine.log("ERROR: Unable to create RenderTexture!");
        return -1;
    }

    engine.log("Custom main loop started.");

    bool firstFrame = true;

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int mx = event.mouseButton.x;
                int my = event.mouseButton.y;

                engine.log("Mouse click at: " + std::to_string(mx) + ", " + std::to_string(my));

                buffer.clear(sf::Color(50, 50, 50));
                PrimitiveRenderer bufferRenderer(&buffer);
                drawAllFigures(bufferRenderer);

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    engine.log("Running FLOOD FILL...");
                    bufferRenderer.floodFill0(mx, my, sf::Color::Blue, sf::Color(50, 50, 50));
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    engine.log("Running BOUNDARY FILL...");
                    bufferRenderer.boundaryFillIterative0(mx, my, sf::Color::Yellow, sf::Color::Red);
                }

                buffer.display();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                engine.log("Key pressed: " + std::to_string(event.key.code));
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                else if (event.key.code == sf::Keyboard::R)
                {
                    buffer.clear(sf::Color(50, 50, 50));
                    PrimitiveRenderer bufferRenderer(&buffer);
                    drawAllFigures(bufferRenderer);
                    buffer.display();
                }
            }
        }

        if (firstFrame) {
            buffer.clear(sf::Color(50, 50, 50));
            PrimitiveRenderer bufferRenderer(&buffer);
            drawAllFigures(bufferRenderer);
            buffer.display();
            firstFrame = false;
        }

        window->clear();
        sf::Sprite sprite(buffer.getTexture());
        window->draw(sprite);
        window->display();
    }

    engine.log("Custom main loop ended.");
    return 0;
}