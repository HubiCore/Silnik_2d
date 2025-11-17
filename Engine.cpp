#include "Engine.hpp"
#include "PrimitiveRenderer.hpp"
#include "Point2D.hpp"
#include "LineSegment.hpp"

Engine::Engine() : fullscreen(false), mouseEnabled(false), keyboardEnabled(true), fps(60), isRunning(false),clearColor(sf::Color::Black) {
    logFile.open("engine_log.txt", std::ios::out);
    log("Engine created.");
};

Engine::~Engine() {
    shutdown();
}

bool Engine::init(const std::string& title, unsigned int screenWidth, unsigned int screenHeight, bool fullscreenMode, unsigned int targetFps) {
    fullscreen = fullscreenMode;
    fps = targetFps;

    sf::VideoMode mode(screenWidth, screenHeight);
    if (fullscreen && !mode.isValid()) {
        log("invalid fullscreen video mode");
        return false;
    }


    unsigned int style = fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
    window.create(mode, title, style);

    if (!window.isOpen()) {
        log("could not create window");
        return false;
    }

    window.setFramerateLimit(fps);
    log("Engine initialized successfully.");
    log("Resolution: " + std::to_string(screenWidth) + "x" + std::to_string(screenHeight) );
    log(std::string("Fullscreen: ") + (fullscreen ? "yes" : "no"));

    return true;
}

void Engine::setClearColor(const sf::Color& color) {
    clearColor = color;
    log("Set clear color.");

}

void Engine::enableMouse(bool enable) {
    mouseEnabled = enable;
    sf::Mouse::setPosition({400,300}, window);
    window.setMouseCursorVisible(enable);
    log(std::string("Mouse ") + (enable ? "enabled" : "disabled"));
}

void Engine::enableKeyboard(bool enable) {
    keyboardEnabled = enable;
    log(std::string("Keyboard ") + (enable ? "enabled" : "disabled"));
}


void Engine::mainLoop() {
    if (!window.isOpen()) {
        log("Error: Window not initialized before mainLoop!");
        return;
    }

    PrimitiveRenderer renderer(&window);
    Point2D point(200, 200);
    LineSegment line(Point2D(100, 100), Point2D(400, 300));

    isRunning = true;
    log("Main loop started.");

    while (isRunning && window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                isRunning = false;

            if (keyboardEnabled && event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    isRunning = false;
                log("Key pressed: " + std::to_string(event.key.code));
            }

            if (mouseEnabled && event.type == sf::Event::MouseButtonPressed)
                log("Mouse button pressed: " + std::to_string(event.mouseButton.button));
        }

        window.clear(clearColor);
        point.draw(renderer, sf::Color::Green);
        line.draw(renderer, false, sf::Color::Red);
        window.display();
    }

    log("Main loop exited.");
    shutdown();
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
    std::cout << "[Engine] " << message << std::endl;
    if (logFile.is_open()) {
        logFile << "[Engine]" << message << std::endl;
    }
}


