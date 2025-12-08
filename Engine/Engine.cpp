/**
 * @file Engine.cpp
 * @brief Implementacja klasy Engine
 * @ingroup Engine
 *
 * Implementacja metod klasy Engine zdefiniowanych w Engine.hpp.
 * Zawiera logikę inicjalizacji okna, pętli głównej, obsługi zdarzeń i logowania.
 */

#include "Engine.hpp"
#include "../Object/Renderer/PrimitiveRenderer.hpp"
#include "../Figures/Point2D/Point2D.hpp"
#include "../Figures/LineSegment/LineSegment.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

/**
 * @brief Konstruktor klasy Engine
 *
 * Inicjalizuje parametry silnika i otwiera plik logów.
 * Ustawia domyślne wartości: okno 800x600, 60 FPS, wyłączoną mysz.
 */
Engine::Engine() : fullscreen(false), mouseEnabled(false), keyboardEnabled(true),
                   fps(60), isRunning1(false), clearColor(sf::Color::Black) {
    logFile.open("engine_log.txt", std::ios::out);
    log("Engine created.");
}

/**
 * @brief Destruktor klasy Engine
 *
 * Zapewnia poprawne zamknięcie silnika i zamknięcie pliku logów.
 */
Engine::~Engine() {
    shutdown();
}

/**
 * @brief Inicjalizuje silnik i tworzy główne okno
 * @param title Tytuł okna
 * @param screenWidth Szerokość okna w pikselach
 * @param screenHeight Wysokość okna w pikselach
 * @param fullscreenMode Czy uruchomić w trybie pełnoekranowym
 * @param targetFps Docelowa liczba klatek na sekundę
 * @return true jeśli inicjalizacja się powiodła, false w przeciwnym razie
 *
 * Tworzy okno SFML z podanymi parametrami. W przypadku błędu loguje go.
 */
bool Engine::init(const std::string& title, unsigned int screenWidth,
                  unsigned int screenHeight, bool fullscreenMode, unsigned int targetFps) {
    fullscreen = fullscreenMode;
    fps = targetFps;

    sf::VideoMode mode(screenWidth, screenHeight);
    if (fullscreen && !mode.isValid()) {
        logError("Invalid fullscreen video mode");
        return false;
    }

    unsigned int style = fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    window.create(mode, title, style);

    if (!window.isOpen()) {
        logError("Could not create window");
        return false;
    }

    window.setFramerateLimit(fps);
    window.setKeyRepeatEnabled(false);

    log("Engine initialized successfully.");
    log("Resolution: " + std::to_string(screenWidth) + "x" + std::to_string(screenHeight));
    log("Fullscreen: " + std::string(fullscreen ? "yes" : "no"));
    log("Target FPS: " + std::to_string(fps));

    return true;
}

/**
 * @brief Ustawia kolor czyszczenia okna
 * @param color Kolor tła okna
 */
void Engine::setClearColor(const sf::Color& color) {
    clearColor = color;
    log("Set clear color.");
}

/**
 * @brief Ustawia tytuł okna
 * @param title Nowy tytuł okna
 */
void Engine::setWindowTitle(const std::string& title) {
    window.setTitle(title);
}

/**
 * @brief Włącza lub wyłącza obsługę myszy
 * @param enable true aby włączyć mysz, false aby wyłączyć
 *
 * Po włączeniu myszy, kursor jest wyśrodkowany i pokazywany.
 */
void Engine::enableMouse(bool enable) {
    mouseEnabled = enable;
    sf::Mouse::setPosition({static_cast<int>(window.getSize().x / 2),
                           static_cast<int>(window.getSize().y / 2)}, window);
    window.setMouseCursorVisible(enable);
    log(std::string("Mouse ") + (enable ? "enabled" : "disabled"));
}

/**
 * @brief Włącza lub wyłącza obsługę klawiatury
 * @param enable true aby włączyć klawiaturę, false aby wyłączyć
 */
void Engine::enableKeyboard(bool enable) {
    keyboardEnabled = enable;
    log(std::string("Keyboard ") + (enable ? "enabled" : "disabled"));
}

/**
 * @brief Pobiera wskaźnik do okna SFML
 * @return Wskaźnik do sf::RenderWindow
 */
sf::RenderWindow* Engine::getWindow() {
    return &window;
}

/**
 * @brief Pobiera rozmiar okna
 * @return Rozmiar okna jako sf::Vector2u
 */
sf::Vector2u Engine::getWindowSize() const {
    return window.getSize();
}

/**
 * @brief Rozpoczyna nową klatkę (czyści okno)
 */
void Engine::beginFrame() {
    window.clear(clearColor);
}

/**
 * @brief Kończy klatkę (wyświetla zawartość)
 *
 * Aktualizuje również czas delta i całkowity czas działania.
 */
void Engine::endFrame() {
    window.display();
    deltaTime = frameClock.restart();
    elapsedTime += deltaTime;
}

/**
 * @brief Pobiera czas od ostatniej klatki
 * @return Czas delta w sekundach
 */
float Engine::getDeltaTime() const {
    return deltaTime.asSeconds();
}

/**
 * @brief Pobiera całkowity czas działania silnika
 * @return Całkowity czas w sekundach
 */
float Engine::getElapsedTime() const {
    return elapsedTime.asSeconds();
}

/**
 * @brief Sprawdza, czy klawisz jest wciśnięty
 * @param key Sprawdzany klawisz
 * @return true jeśli klawisz jest wciśnięty, false w przeciwnym razie
 */
bool Engine::isKeyPressed(sf::Keyboard::Key key) const {
    return keyboardEnabled && sf::Keyboard::isKeyPressed(key);
}

/**
 * @brief Sprawdza, czy przycisk myszy jest wciśnięty
 * @param button Sprawdzany przycisk myszy
 * @return true jeśli przycisk jest wciśnięty, false w przeciwnym razie
 */
bool Engine::isMouseButtonPressed(sf::Mouse::Button button) const {
    return mouseEnabled && sf::Mouse::isButtonPressed(button);
}

/**
 * @brief Pobiera pozycję myszy względem okna
 * @return Pozycja myszy w pikselach okna
 */
sf::Vector2i Engine::getMousePosition() const {
    if (!mouseEnabled) return sf::Vector2i(-1, -1);
    return sf::Mouse::getPosition(window);
}

/**
 * @brief Pobiera pozycję myszy w koordynatach świata (z uwzględnieniem widoku)
 * @return Pozycja myszy w koordynatach świata
 */
sf::Vector2f Engine::getMouseWorldPosition() const {
    if (!mouseEnabled) return sf::Vector2f(-1.f, -1.f);
    sf::Vector2i mousePos = getMousePosition();
    return window.mapPixelToCoords(mousePos);
}

/**
 * @brief Ustawia aktualny widok okna
 * @param view Nowy widok
 */
void Engine::setView(const sf::View& view) {
    window.setView(view);
}

/**
 * @brief Pobiera aktualny widok okna
 * @return Aktualny widok
 */
const sf::View& Engine::getView() const {
    return window.getView();
}

/**
 * @brief Resetuje widok do domyślnego
 */
void Engine::resetView() {
    window.setView(window.getDefaultView());
}

/**
 * @brief Powiększa/pomniejsza aktualny widok
 * @param factor Współczynnik skalowania (>1 pomniejsza, <1 powiększa)
 */
void Engine::zoom(float factor) {
    sf::View view = window.getView();
    view.zoom(factor);
    window.setView(view);
}

/**
 * @brief Przesuwa aktualny widok
 * @param offsetX Przesunięcie w osi X
 * @param offsetY Przesunięcie w osi Y
 */
void Engine::moveView(float offsetX, float offsetY) {
    sf::View view = window.getView();
    view.move(offsetX, offsetY);
    window.setView(view);
}

/**
 * @brief Obsługuje zdarzenia SFML
 *
 * Przetwarza zdarzenia okna, w tym zamknięcie, zmianę rozmiaru,
 * oraz zdarzenia klawiatury (jeśli włączone).
 */
void Engine::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning1 = false;
            return;
        }

        if (event.type == sf::Event::Resized) {
            // Dostosuj widok do nowego rozmiaru okna
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }

        if (keyboardEnabled && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isRunning1 = false;
            }
            // Dodatkowa obsługa klawiszy może być dodana tutaj
        }
    }
}

/**
 * @brief Aktualizuje stan silnika (do przesłonięcia w klasach pochodnych)
 *
 * Metoda wirtualna przeznaczona do przesłonięcia w klasach pochodnych
 * w celu zaimplementowania logiki gry.
 */
void Engine::update() {
    // Do przesłonięcia przez klasy pochodne
}

/**
 * @brief Renderuje klatkę (do przesłonięcia w klasach pochodnych)
 *
 * Metoda wirtualna przeznaczona do przesłonięcia w klasach pochodnych
 * w celu zaimplementowania renderowania.
 */
void Engine::render() {
    // Do przesłonięcia przez klasy pochodne
}

/**
 * @brief Uruchamia główną pętlę silnika
 *
 * Pętla główna wykonująca kolejno: obsługę zdarzeń, aktualizację,
 * rozpoczęcie klatki, renderowanie, zakończenie klatki.
 */
void Engine::mainLoop() {
    if (!window.isOpen()) {
        logError("Window not initialized before mainLoop!");
        return;
    }

    isRunning1 = true;
    frameClock.restart();
    elapsedTime = sf::Time::Zero;

    log("Main loop started.");

    while (isRunning1 && window.isOpen()) {
        handleEvents();
        update();

        beginFrame();
        render();
        endFrame();
    }

    log("Main loop exited.");
}

/**
 * @brief Zamyka silnik i zwalnia zasoby
 *
 * Zamyka okno oraz plik logów.
 */
void Engine::shutdown() {
    if (window.isOpen()) {
        window.close();
        log("Window closed.");
    }
    if (logFile.is_open()) {
        log("Engine shutdown complete.");
        logFile.close();
    }
}

/**
 * @brief Loguje wiadomość do konsoli i pliku
 * @param message Wiadomość do zalogowania
 *
 * Wiadomość jest wypisywana na konsolę z prefiksem [ENGINE]
 * oraz zapisywana do pliku z znacznikiem czasu.
 */
void Engine::log(const std::string& message) {
    std::cout << "[ENGINE] " << message << std::endl;
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);

        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        logFile << "[" << ss.str() << "] [ENGINE] " << message << std::endl;
    }
}

/**
 * @brief Loguje błąd do konsoli i pliku
 * @param message Wiadomość błędu do zalogowania
 *
 * Błąd jest wypisywany na stderr z prefiksem [ENGINE ERROR]
 * oraz zapisywany do pliku z znacznikiem czasu.
 */
void Engine::logError(const std::string& message) {
    std::cerr << "[ENGINE ERROR] " << message << std::endl;
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);

        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        logFile << "[" << ss.str() << "] [ENGINE ERROR] " << message << std::endl;
    }
}

/**
 * @brief Loguje ostrzeżenie do konsoli i pliku
 * @param message Wiadomość ostrzeżenia do zalogowania
 *
 * Ostrzeżenie jest wypisywane na konsolę z prefiksem [ENGINE WARNING]
 * oraz zapisywane do pliku z znacznikiem czasu.
 */
void Engine::logWarning(const std::string& message) {
    std::cout << "[ENGINE WARNING] " << message << std::endl;
    if (logFile.is_open()) {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);

        std::stringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        logFile << "[" << ss.str() << "] [ENGINE WARNING] " << message << std::endl;
    }
}