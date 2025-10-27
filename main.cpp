#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"

class Engine {
private:
    sf::RenderWindow window;
    sf::VideoMode videoMode;
    std::string windowTitle;
    bool isFullscreen;
    bool isRunning;

public:
    // Konstruktor
    Engine()
        : isFullscreen(false), windowTitle("Ngine"), videoMode(sf::VideoMode(800, 800)), isRunning(false)
    {
    }

    // Destruktor
    ~Engine() {
        if (window.isOpen()) {
            window.close();
        }
    }

	// Inicjalizacja silnika
    bool init() {
        if (isFullscreen) {
            window.create(videoMode, windowTitle, sf::Style::Fullscreen);
        }
        else {
            window.create(videoMode, windowTitle, sf::Style::Default);
        }

        isRunning = true;
        run();
        return true;
    }

    void run() {
        sf::Event event;
        while (isRunning && window.isOpen())
        {
            // Obs³uga zdarzeñ
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    isRunning = false;

                // Obs³uga klawiatury - ESC do zamkniêcia
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        isRunning = false;
                    }
                    // Opcjonalnie: F11 do prze³¹czania trybu pe³noekranowego
                    else if (event.key.code == sf::Keyboard::F11) {
                        toggleFullscreen();
                    }
                }
            }

            // Logika gry
            update();

            // Renderowanie
            render();
        }

        if (window.isOpen()) {
            window.close();
        }
    }

    void update() {
        // Tutaj logika aktualizacji gry
    }

    void render() {
        window.clear(sf::Color::Black); // Czyszczenie ekranu na czarno

        // Tutaj rysowanie obiektów gry

        window.display(); // Wyœwietlenie tego co narysowaliœmy
    }

    void toggleFullscreen() {
        isFullscreen = !isFullscreen;

        if (window.isOpen()) {
            window.close();
        }

        if (isFullscreen) {
            window.create(videoMode, windowTitle, sf::Style::Fullscreen);
        }
        else {
            window.create(videoMode, windowTitle, sf::Style::Default);
        }
    }

    void setFullscreen(bool fullscreen) {
        isFullscreen = fullscreen;
    }
    void setVideoMode(int width, int height) {
        videoMode = sf::VideoMode(width, height);
    }
};

int main()
{
    Engine engine;
    engine.setVideoMode(800, 300);
    engine.setFullscreen(false);
    engine.init();
    return 0;
}