#include "Engine.hpp"
#include "../Object/Renderer/PrimitiveRenderer.hpp"
#include "../Figures/Point2D/Point2D.hpp"
#include "../Figures/LineSegment/LineSegment.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

Engine::Engine() : fullscreen(false), mouseEnabled(false), keyboardEnabled(true),
                   fps(60), isRunning1(false), clearColor(sf::Color::Black) {
    logFile.open("engine_log.txt", std::ios::out);
    log("Engine created.");
}

Engine::~Engine() {
    shutdown();
}

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

void Engine::setClearColor(const sf::Color& color) {
    clearColor = color;
    log("Set clear color.");
}

void Engine::setWindowTitle(const std::string& title) {
    window.setTitle(title);
}

void Engine::enableMouse(bool enable) {
    mouseEnabled = enable;
    sf::Mouse::setPosition({static_cast<int>(window.getSize().x / 2),
                           static_cast<int>(window.getSize().y / 2)}, window);
    window.setMouseCursorVisible(enable);
    log(std::string("Mouse ") + (enable ? "enabled" : "disabled"));
}

void Engine::enableKeyboard(bool enable) {
    keyboardEnabled = enable;
    log(std::string("Keyboard ") + (enable ? "enabled" : "disabled"));
}

sf::RenderWindow* Engine::getWindow() {
    return &window;
}

sf::Vector2u Engine::getWindowSize() const {
    return window.getSize();
}

void Engine::beginFrame() {
    window.clear(clearColor);
}

void Engine::endFrame() {
    window.display();
    deltaTime = frameClock.restart();
    elapsedTime += deltaTime;
}

float Engine::getDeltaTime() const {
    return deltaTime.asSeconds();
}

float Engine::getElapsedTime() const {
    return elapsedTime.asSeconds();
}

bool Engine::isKeyPressed(sf::Keyboard::Key key) const {
    return keyboardEnabled && sf::Keyboard::isKeyPressed(key);
}

bool Engine::isMouseButtonPressed(sf::Mouse::Button button) const {
    return mouseEnabled && sf::Mouse::isButtonPressed(button);
}

sf::Vector2i Engine::getMousePosition() const {
    if (!mouseEnabled) return sf::Vector2i(-1, -1);
    return sf::Mouse::getPosition(window);
}

sf::Vector2f Engine::getMouseWorldPosition() const {
    if (!mouseEnabled) return sf::Vector2f(-1.f, -1.f);
    sf::Vector2i mousePos = getMousePosition();
    return window.mapPixelToCoords(mousePos);
}

void Engine::setView(const sf::View& view) {
    window.setView(view);
}

const sf::View& Engine::getView() const {
    return window.getView();
}

void Engine::resetView() {
    window.setView(window.getDefaultView());
}

void Engine::zoom(float factor) {
    sf::View view = window.getView();
    view.zoom(factor);
    window.setView(view);
}

void Engine::moveView(float offsetX, float offsetY) {
    sf::View view = window.getView();
    view.move(offsetX, offsetY);
    window.setView(view);
}

void Engine::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            isRunning1 = false;
            return;
        }

        if (event.type == sf::Event::Resized) {

            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }

        if (keyboardEnabled && event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                isRunning1 = false;
            }

        }
    }
}

void Engine::update() {

}

void Engine::render() {

}

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