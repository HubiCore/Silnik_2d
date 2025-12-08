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
    /**
     * @brief Inicjalizacja silnika graficznego
     *
     * Tworzy obiekt Engine i inicjalizuje go z następującymi parametrami:
     * - Tytuł okna: "2D Engine with Animated Player"
     * - Rozmiar: 800x600 pikseli
     * - Tryb pełnoekranowy: wyłączony
     * - Limit FPS: 144
     *
     * @return false w przypadku błędu inicjalizacji
     */
    Engine engine;
    if (!engine.init("2D Engine with Animated Player", 800, 600, false, 144)) {
        return -1;
    }

    // Configure engine
    /**
     * @brief Konfiguracja podstawowych ustawień silnika
     *
     * Ustawia kolor tła na szary (50,50,50) i włącza obsługę
     * urządzeń wejściowych.
     */
    engine.setClearColor(sf::Color(50, 50, 50));
    engine.enableMouse(true);
    engine.enableKeyboard(true);

    // Get window pointer
    /**
     * @brief Pobranie wskaźnika do okna renderującego
     *
     * @return sf::RenderWindow* Wskaźnik do obiektu okna
     * @retval nullptr jeśli okno nie zostało utworzone
     */
    sf::RenderWindow* window = engine.getWindow();
    if (!window) {
        engine.log("ERROR: getWindow() == nullptr!");
        return -1;
    }

    // Initialize renderer and buffer
    /**
     * @brief Inicjalizacja renderera i bufora tekstury
     *
     * Tworzy obiekt PrimitiveRenderer do rysowania prymitywów
     * oraz sf::RenderTexture jako bufor renderowania.
     *
     * @note Rozmiar bufora musi odpowiadać rozmiarowi okna
     */
    PrimitiveRenderer renderer(window);
    sf::RenderTexture buffer;
    if (!buffer.create(800, 600)) {
        engine.log("ERROR: Unable to create RenderTexture!");
        return -1;
    }

    // Set game boundaries
    /**
     * @brief Definicja granic obszaru gry
     *
     * Określa prostokątny obszar (0,0,800,600) jako granice,
     * w których może poruszać się gracz.
     */
    sf::FloatRect gameBounds(0, 0, 800, 600);

    // Create player
    /**
     * @brief Tworzenie obiektu gracza
     *
     * Inicjalizuje gracza na pozycji (400,300) z prędkością 5.0.
     * Ustawia granice ruchu zgodnie z gameBounds.
     */
    Player player(400.f, 300.f, 5.0f);
    player.setBoundaries(gameBounds);

    // Try to load animated sprite sheets
    /**
     * @section sprite_loading Ładowanie sprite'ów gracza
     *
     * Program próbuje załadować sprite'y z różnych ścieżek w następującej kolejności:
     * 1. Arkusze sprite'ów (nowa metoda)
     * 2. Pojedyncze animowane sprite'y (metoda fallback)
     * 3. Statyczne sprite'y (kompatybilność wsteczna)
     * 4. Placeholder'y (gdy brak plików)
     *
     * @see Player::loadSpriteSheets()
     * @see Player::loadAnimatedSprites()
     * @see Player::loadSprites()
     * @see Player::createPlaceholderSprites()
     */
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
    /**
     * @brief Konfiguracja prędkości animacji
     *
     * Ustawia czas wyświetlania jednej klatki animacji na 0.15 sekundy.
     * Odpowiada to około 6.67 klatek na sekundę dla animacji gracza.
     */
    player.setFrameTime(0.15f); // 0.15 seconds per frame

    // Display program information using engine's logging system
    /**
     * @section info_display Wyświetlanie informacji programu
     *
     * Wyświetla w konsoli informacje o:
     * - Załadowanych sprite'ach i parametrach animacji
     * - Dostępnych sterowaniach
     * - Skrótach klawiszowych
     */
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
    /**
     * @section main_loop Główna pętla gry
     *
     * Pętla główna realizuje następujące zadania:
     * 1. Pomiar czasu między klatkami (deltaTime)
     * 2. Aktualizacja FPS w tytule okna
     * 3. Aktualizacja stanu gracza
     * 4. Obsługa zdarzeń wejścia
     * 5. Renderowanie sceny do bufora
     * 6. Wyświetlanie bufora w oknie
     */
    engine.log("Main loop started.");
    sf::Clock clock;
    float fpsUpdateTimer = 0.f;
    int frameCount = 0;

    // MAIN GAME LOOP
    while (window->isOpen()) {
        /**
         * @brief Pomiar czasu między klatkami
         *
         * Oblicza czas, jaki upłynął od ostatniej klatki.
         * Używane do płynnej animacji i obliczania FPS.
         */
        float deltaTime = clock.restart().asSeconds();
        frameCount++;
        fpsUpdateTimer += deltaTime;

        // Update FPS display every second
        /**
         * @brief Aktualizacja wyświetlania FPS
         *
         * Co sekundę oblicza aktualne FPS i aktualizuje tytuł okna.
         */
        if (fpsUpdateTimer >= 1.0f) {
            float fps = frameCount / fpsUpdateTimer;
            engine.setWindowTitle("2D Engine with Animated Player - FPS: " + std::to_string(static_cast<int>(fps)));
            frameCount = 0;
            fpsUpdateTimer = 0.f;
        }

        // Update player state (includes animation)
        /**
         * @brief Aktualizacja stanu gracza
         *
         * Wywołuje Player::update() który:
         * - Aktualizuje animację na podstawie czasu
         * - Obsługuje ruch na podstawie wejścia
         * - Aktualizuje pozycję sprite'a
         */
        player.update();

        // Event handling
        /**
         * @section event_handling Obsługa zdarzeń
         *
         * Pobiera i przetwarza zdarzenia z kolejki SFML:
         * - Zamykanie okna
         * - Kliknięcia myszą (wypełnianie obszarów)
         * - Naciśnięcia klawiszy (sterowanie, debugowanie)
         */
        sf::Event event;
        while (window->pollEvent(event)) {
            // Window close event
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // Mouse click - area filling
            /**
             * @subsection mouse_events Zdarzenia myszy
             *
             * Obsługuje kliknięcia myszą dla algorytmów wypełniania:
             * - LPM: Flood fill (wypełnienie obszaru)
             * - PPM: Boundary fill (wypełnienie konturu)
             *
             * @param mouseX Współrzędna X kliknięcia
             * @param mouseY Współrzędna Y kliknięcia
             *
             * @see PrimitiveRenderer::floodFill0()
             * @see PrimitiveRenderer::boundaryFillIterative0()
             */
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
            /**
             * @subsection keyboard_events Zdarzenia klawiatury
             *
             * Obsługuje naciśnięcia klawiszy dla:
             * - Sterowania (ESC - wyjście)
             * - Debugowania (C, P, F, R)
             * - Kontroli animacji (1, 2, 3)
             *
             * @see Player::clearCollisionObjects()
             * @see Player::getPosition()
             * @see Player::getCurrentFrame()
             * @see Player::resetAnimation()
             * @see Player::setFrameTime()
             */
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
        /**
         * @section rendering Renderowanie sceny
         *
         * Renderuje wszystkie obiekty do bufora tekstury:
         * 1. Czyści bufar szarym kolorem
         * 2. Tworzy renderer dla bufora
         * 3. Rysuje wszystkie figury (w tym gracza)
         * 4. Wyświetla bufor
         */
        buffer.clear(sf::Color(50, 50, 50));
        PrimitiveRenderer bufferRenderer(&buffer);
        drawAllFigures(bufferRenderer, player);
        buffer.display();

        // Display buffer in window
        /**
         * @brief Wyświetlanie bufora w oknie
         *
         * Tworzy sprite z tekstury bufora i rysuje go w oknie.
         * Technika double-buffering zapewnia płynne wyświetlanie.
         */
        window->clear();
        sf::Sprite sprite(buffer.getTexture());
        window->draw(sprite);
        window->display();
    }

    // Program termination
    /**
     * @brief Zakończenie programu
     *
     * Loguje informację o zakończeniu głównej pętli
     * i zwraca kod sukcesu.
     */
    engine.log("Main loop ended.");
    return 0;
}