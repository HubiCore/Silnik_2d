#include "Engine.hpp"
#include "PrimitiveRenderer.hpp"
#include "Point2D.hpp"
#include "LineSegment.hpp"
#include "Player.hpp"
#include "drawAllFigures.hpp"  // Dodaj nagłówek z deklaracją funkcji
#include <vector>
#include <cmath>
#include <iostream>
#include <map>

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
    if (!player.loadSprites("D:/studia/Silnik2D/sprite")) {
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
                drawAllFigures(bufferRenderer, player);  // Użycie funkcji z drawAllFigures.cpp

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
        drawAllFigures(bufferRenderer, player);  // Użycie funkcji z drawAllFigures.cpp
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