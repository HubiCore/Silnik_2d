#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

class Engine {
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Clock clock;
    sf::Color clearColor;
    unsigned int screenWidth, screenHeight;
    unsigned int fps;
    bool isRunning;
    bool fullscreen;
    bool mouseEnabled;
    bool keyboardEnabled;

    std::ofstream logFile;

public:
    Engine();
    bool init(const std::string& title, unsigned int screenWidth, unsigned int screenHeight, bool fullscreen = false, unsigned int fps = 60);
    void setClearColor(const sf::Color& color);
    void enableMouse(bool enable);
    void enableKeyboard(bool enable);
    void mainLoop();
    void shutdown();
    void log(const std::string& message);
    sf::RenderWindow* getWindow() { return &window; }
    ~Engine();

};

