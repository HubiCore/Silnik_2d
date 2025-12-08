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

    bool init(const std::string& title,
              unsigned int screenWidth = 800,
              unsigned int screenHeight = 600,
              bool fullscreenMode = false,
              unsigned int targetFps = 60);

    void setClearColor(const sf::Color& color);
    void setWindowTitle(const std::string& title);
    void enableMouse(bool enable);
    void enableKeyboard(bool enable);

    sf::RenderWindow* getWindow();
    sf::Vector2u getWindowSize() const;
    bool isFullscreen() const { return fullscreen; }
    unsigned int getFPS() const { return fps; }
    bool isRunning() const { return isRunning1; }

    void beginFrame();
    void endFrame();

    float getDeltaTime() const;
    float getElapsedTime() const;

    bool isKeyPressed(sf::Keyboard::Key key) const;
    bool isMouseButtonPressed(sf::Mouse::Button button) const;
    sf::Vector2i getMousePosition() const;
    sf::Vector2f getMouseWorldPosition() const;

    void mainLoop();
    void shutdown();

    void log(const std::string& message);
    void logError(const std::string& message);
    void logWarning(const std::string& message);

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

    sf::Clock frameClock;
    sf::Time deltaTime;
    sf::Time elapsedTime;

    std::ofstream logFile;

    void handleEvents();
    void update();
    void render();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
};

#endif

