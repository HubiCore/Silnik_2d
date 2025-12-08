#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <fstream>
#include <memory>
#include <chrono>

class Engine {
public:
    Engine();
    ~Engine();

    // Initialization
    bool init(const std::string& title,
              unsigned int screenWidth = 800,
              unsigned int screenHeight = 600,
              bool fullscreenMode = false,
              unsigned int targetFps = 60);

    // Window management
    void setClearColor(const sf::Color& color);
    void setWindowTitle(const std::string& title);
    void enableMouse(bool enable);
    void enableKeyboard(bool enable);

    // Accessors
    sf::RenderWindow* getWindow();
    sf::Vector2u getWindowSize() const;
    bool isFullscreen() const { return fullscreen; }
    unsigned int getFPS() const { return fps; }
    bool isRunning() const { return isRunning1; }

    // Rendering utilities
    void beginFrame();
    void endFrame();

    // Time management
    float getDeltaTime() const;
    float getElapsedTime() const;

    // Input utilities
    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isMouseButtonPressed(sf::Mouse::Button button) const;
    sf::Vector2i getMousePosition() const;
    sf::Vector2f getMouseWorldPosition() const;

    // Main loop
    void mainLoop();
    void shutdown();

    // Logging
    void log(const std::string& message);
    void logError(const std::string& message);
    void logWarning(const std::string& message);

    // Camera/view management
    void setView(const sf::View& view);
    const sf::View& getView() const;
    void resetView();
    void zoom(float factor);
    void moveView(float offsetX, float offsetY);

private:
    sf::RenderWindow window;
    bool fullscreen;
    bool mouseEnabled;
    bool keyboardEnabled;
    unsigned int fps;
    bool isRunning1;
    sf::Color clearColor;

    // Time management
    sf::Clock frameClock;
    sf::Time deltaTime;
    sf::Time elapsedTime;

    // Logging
    std::ofstream logFile;

    // Private methods
    void handleEvents();
    void update();
    void render();

    // Prevent copying
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
};

#endif // ENGINE_HPP