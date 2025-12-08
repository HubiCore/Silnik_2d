/**
 * @file main.cpp
 * @brief Główny punkt wejścia programu 2D Engine z animowanym graczem
 * @mainpage 2D Engine z Animowanym Graczem
 *
 * @section intro_sec Wprowadzenie
 * Program implementuje interaktywny silnik graficzny 2D z animowanym graczem,
 * obsługą klawiatury, myszy oraz algorytmami wypełniania obszarów.
 *
 * @section features_sec Funkcje
 * - Animacja sprite'ów gracza w 4 kierunkach
 * - Wypełnianie obszarów (flood fill i boundary fill)
 * - System kolizji i hitboxów
 * - Renderowanie przez bufor tekstury
 * - Rozbudowany system debugowania
 * - Obsługa różnych formatów sprite'ów
 *
 * @author Autor programu
 * @date 2024
 * @version 1.0
 *
 * @copyright MIT License
 */

#include "Engine/Engine.hpp"
#include "Object/Renderer/PrimitiveRenderer.hpp"
#include "Figures/Point2D/Point2D.hpp"
#include "Figures/LineSegment/LineSegment.hpp"
#include "Player/Player.hpp"
#include "Figures/drawAllFigures/drawAllFigures.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <map>
#include <filesystem>

// ============================================================================
// MAIN FUNCTION - PROGRAM ENTRY POINT
// ============================================================================

/**
 * @brief Główna funkcja programu
 *
 * Funkcja inicjalizuje silnik graficzny, tworzy obiekt gracza, ładuje zasoby,
 * zarządza główną pętlą gry oraz obsługuje zdarzenia wejścia.
 *
 * @return int Kod zakończenia programu:
 *         - 0: Sukces
 *         - -1: Błąd inicjalizacji silnika
 *
 * @details Sekwencja działania:
 * 1. Inicjalizacja silnika graficznego
 * 2. Konfiguracja okna i renderera
 * 3. Tworzenie obiektu gracza i ładowanie sprite'ów
 * 4. Konfiguracja animacji i wyświetlenie informacji
 * 5. Główna pętla gry z obsługą zdarzeń
 * 6. Czyszczenie zasobów i zakończenie programu
 *
 * @note Wymaga biblioteki SFML do działania
 * @warning W przypadku braku sprite'ów używane są placeholder'y
 *
 * @see Engine
 * @see Player
 * @see PrimitiveRenderer
 * @see drawAllFigures()
 */
int main() {
    // Initialize graphics engine
    Engine engine;
    if (!engine.init("2D Engine with Animated Player", 800, 600, false, 144)) {
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

    // Try to load animated sprite sheets
    bool spritesLoaded = false;
    std::string loadedPath = "";

    // Check multiple paths
    std::vector<std::string> spritePaths = {
        "../Object/sprite",
    };

    for (const auto& path : spritePaths) {
        engine.log("Checking path: " + path);

        if (std::filesystem::exists(path)) {
            engine.log("Path exists, trying to load sprites...");

            // First try sprite sheets (new method)
            if (player.loadSpriteSheets(path)) {
                engine.log(" Sprite sheets loaded successfully from: " + path);
                spritesLoaded = true;
                loadedPath = path;
                break;
            } else {
                engine.log(" Sprite sheets not found in: " + path);
            }

            // Fallback to individual animated sprites
            if (player.loadAnimatedSprites(path)) {
                engine.log(" Individual animated sprites loaded from: " + path);
                spritesLoaded = true;
                loadedPath = path;
                break;
            } else {
                engine.log(" Individual animated sprites not found in: " + path);
            }

            // Fallback to static sprites (old method for compatibility)
            if (player.loadSprites(path)) {
                engine.log(" Static sprites loaded from: " + path);
                spritesLoaded = true;
                loadedPath = path;
                break;
            } else {
                engine.log(" Static sprites not found in: " + path);
            }
        } else {
            engine.log("Path does not exist: " + path);
        }
    }

    // If no sprites loaded, use placeholders
    if (!spritesLoaded) {
        engine.log("No external sprites found. Creating placeholder sprites.");
        player.createPlaceholderSprites();
        player.setDirection(Player::Direction::DOWN);
    } else {
        engine.log("Sprites loaded successfully from: " + loadedPath);
    }

    // Configure animation speed
    player.setFrameTime(0.15f); // 0.15 seconds per frame

    // Display program information using engine's logging system
    engine.log("========================================");
    engine.log("2D ENGINE WITH ANIMATED PLAYER");
    engine.log("========================================");

    if (spritesLoaded) {
        engine.log("ANIMATION INFO:");
        engine.log("  - Frames per direction: " + std::to_string(player.getFrameCount()));
        engine.log("  - Frame time: " + std::to_string(player.getFrameTime()) + " seconds");
        engine.log("  - Animation speed: " + std::to_string(1.0f / player.getFrameTime()) + " FPS");
    } else {
        engine.log("USING PLACEHOLDER ANIMATIONS (4 frames per direction)");
    }

    engine.log("");
    engine.log("CONTROLS:");
    engine.log("  - Movement:    W, A, S, D");
    engine.log("  - Animation:   Automatic based on movement");
    engine.log("  - Clear:       C (clear hitboxes)");
    engine.log("  - Fill:        LMB (flood fill), RMB (boundary fill)");
    engine.log("  - Exit:        ESC");
    engine.log("  - Debug:       P (position), F (frame info), R (reset animation)");
    engine.log("  - Animation Speed: 1 (fast), 2 (normal), 3 (slow)");
    engine.log("========================================");

    // Start main loop
    engine.log("Main loop started.");
    sf::Clock clock;
    float fpsUpdateTimer = 0.f;
    int frameCount = 0;
    buffer.clear(sf::Color(50, 50, 50));

    // MAIN GAME LOOP
    while (window->isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        frameCount++;
        fpsUpdateTimer += deltaTime;

        // Update FPS display every second
        if (fpsUpdateTimer >= 1.0f) {
            float fps = frameCount / fpsUpdateTimer;
            engine.setWindowTitle("2D Engine with Animated Player - FPS: " + std::to_string(static_cast<int>(fps)));
            frameCount = 0;
            fpsUpdateTimer = 0.f;
        }

        // Update player state (includes animation)
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
                    engine.log("All hitboxes cleared!");
                }

                // Show player position (debug)
                if (event.key.code == sf::Keyboard::P) {
                    sf::Vector2f pos = player.getPosition();
                    engine.log("Player position: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ")");
                }

                // Show animation info (debug)
                if (event.key.code == sf::Keyboard::F) {
                    engine.log("=== ANIMATION DEBUG ===");
                    engine.log("Current frame: " + std::to_string(player.getCurrentFrame()));
                    engine.log("Total frames: " + std::to_string(player.getFrameCount()));
                    engine.log("Frame time: " + std::to_string(player.getFrameTime()) + " seconds");
                    engine.log("Animation FPS: " + std::to_string(1.0f / player.getFrameTime()));
                }

                // Reset animation (debug)
                if (event.key.code == sf::Keyboard::R) {
                    player.resetAnimation();
                    engine.log("Animation reset to frame 0");
                }

                // Change animation speed (debug)
                if (event.key.code == sf::Keyboard::Num1) {
                    player.setFrameTime(0.05f);
                    engine.log("Animation speed: FAST (0.05s per frame)");
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    player.setFrameTime(0.15f);
                    engine.log("Animation speed: NORMAL (0.15s per frame)");
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    player.setFrameTime(0.3f);
                    engine.log("Animation speed: SLOW (0.3s per frame)");
                }
            }
        }

        // Draw current frame to buffer (all figures including player)
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