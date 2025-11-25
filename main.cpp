#include "Engine.hpp"
#include "PrimitiveRenderer.hpp"
#include "Point2D.hpp"
#include "LineSegment.hpp"
#include "Player.hpp"
#include <vector>
#include <cmath>
#include <iostream>
#include <map>

// Rozszerzone klasy z obsługą kolorów i PrimitiveRenderer
class DrawablePoint2D : public Point2D {
private:
    sf::Color color;

public:
    DrawablePoint2D(float x = 0, float y = 0, sf::Color color = sf::Color::White)
        : Point2D(x, y), color(color) {}

    void setColor(sf::Color newColor) { color = newColor; }
    sf::Color getColor() const { return color; }

    void draw(PrimitiveRenderer& renderer) const {
        renderer.drawPoint(getX(), getY(), color);
    }
};

class DrawableLineSegment : public LineSegment {
private:
    sf::Color color;

public:
    DrawableLineSegment(const Point2D& p1, const Point2D& p2, sf::Color color = sf::Color::White)
        : LineSegment(p1, p2), color(color) {}

    void setColor(sf::Color newColor) { color = newColor; }
    sf::Color getColor() const { return color; }

    void draw(PrimitiveRenderer& renderer) const {
        renderer.drawLine(getP1().getX(), getP1().getY(), getP2().getX(), getP2().getY(), color);
    }
};

void drawAllFigures(PrimitiveRenderer& renderer, Player& player) {
    DrawablePoint2D p1(100, 100, sf::Color::Yellow);
    DrawablePoint2D p2(200, 200, sf::Color::White);
    DrawableLineSegment line(p1, p2, sf::Color::Red);

    std::vector<sf::Vector2f> polylinePoints = {
        {300, 100}, {400, 150}, {450, 250}, {350, 300}, {100, 300}
    };

    // punktów i linii
    p1.draw(renderer);
    renderer.drawPoint(150, 150, sf::Color::White);
    line.draw(renderer);

    // elementy z oryginalnej funkcji
    renderer.drawLine(250, 100, 400, 200, sf::Color::Green);
    renderer.drawLineIncremental(400, 100, 550, 200, sf::Color::Cyan);

    renderer.drawPolyLine(polylinePoints, true, sf::Color::Cyan);

    std::vector<sf::Vector2f> openLine = {{600, 100}, {650, 130}, {700, 200}};
    renderer.drawPolyLine(openLine, false, sf::Color::White);

    renderer.drawCircle(600, 200, 40, sf::Color::Green, sf::Color::White);
    renderer.drawCircleSymmetric(700, 350, 60, sf::Color::Red);

    renderer.drawElipse(600, 500, 100, 60, sf::Color::Magenta);
    renderer.drawEllipseSymmetric(900, 400, 80, 40, sf::Color::Yellow);

    renderer.drawPolygon(3, 60, {200, 400}, 0, sf::Color::Red);
    renderer.drawPolygon(4, 80, {350, 400}, M_PI / 4, sf::Color::Green);
    renderer.drawPolygon(6, 50, {500, 400}, 0, sf::Color::Red);

    renderer.drawPolygon(5, 80, {1300, 300}, 0, sf::Color::Red);
    renderer.drawPolygon(5, 100, {1000, 300}, 0, sf::Color::Red);

    renderer.floodFill0(200, 400, sf::Color(0, 255, 255, 150), sf::Color::Green);

    // Rysowanie gracza
    player.draw(renderer);
}

// Funkcja do tworzenia placeholder sprite'ów programowo dla różnych kierunków
sf::Texture createDirectionTexture(sf::Color baseColor, Player::Direction direction) {
    sf::Image img;
    img.create(32, 32, sf::Color::Transparent);

    // Rysujemy podstawowy kształt (kwadrat)
    for (int y = 8; y < 24; y++) {
        for (int x = 8; x < 24; x++) {
            img.setPixel(x, y, baseColor);
        }
    }

    // Dodajemy "głowę" w zależności od kierunku
    switch (direction) {
        case Player::Direction::UP:
            for (int x = 12; x < 20; x++) {
                for (int y = 4; y < 8; y++) {
                    img.setPixel(x, y, baseColor);
                }
            }
            break;
        case Player::Direction::DOWN:
            for (int x = 12; x < 20; x++) {
                for (int y = 24; y < 28; y++) {
                    img.setPixel(x, y, baseColor);
                }
            }
            break;
        case Player::Direction::LEFT:
            for (int x = 4; x < 8; x++) {
                for (int y = 12; y < 20; y++) {
                    img.setPixel(x, y, baseColor);
                }
            }
            break;
        case Player::Direction::RIGHT:
            for (int x = 24; x < 28; x++) {
                for (int y = 12; y < 20; y++) {
                    img.setPixel(x, y, baseColor);
                }
            }
            break;
    }

    sf::Texture texture;
    texture.loadFromImage(img);
    return texture;
}

int main()
{
    Engine engine;

    if (!engine.init("Simple engine", 800, 600, true, 144))
        return -1;

    engine.setClearColor(sf::Color(50, 50, 50));
    engine.enableMouse(true);
    engine.enableKeyboard(true);

    sf::RenderWindow* window = engine.getWindow();
    if (!window) {
        engine.log("ERROR: getWindow() == nullptr!");
        return -1;
    }

    PrimitiveRenderer renderer(window);

    sf::RenderTexture buffer;
    if (!buffer.create(800, 600)) {
        engine.log("ERROR: Unable to create RenderTexture!");
        return -1;
    }

    // ŁADOWANIE SPRITE'ÓW DLA RÓŻNYCH KIERUNKÓW
    std::map<Player::Direction, sf::Texture> playerTextures;

    // Próba załadowania sprite'ów z plików
    bool loadedCustomSprites = true;

    // Możesz zmienić ścieżki na swoje pliki
    if (!playerTextures[Player::Direction::UP].loadFromFile("C:/Users/huber/Downloads/player_up.png") ||
        !playerTextures[Player::Direction::DOWN].loadFromFile("C:/Users/huber/Downloads/player_down.png") ||
        !playerTextures[Player::Direction::LEFT].loadFromFile("C:/Users/huber/Downloads/player_left.png") ||
        !playerTextures[Player::Direction::RIGHT].loadFromFile("C:/Users/huber/Downloads/player_right.png")) {

        engine.log("WARNING: Could not load direction sprites! Creating placeholders.");
        loadedCustomSprites = false;

        // Tworzenie placeholder sprite'ów programowo z różnymi kolorami
        playerTextures[Player::Direction::UP] = createDirectionTexture(sf::Color::Red, Player::Direction::UP);
        playerTextures[Player::Direction::DOWN] = createDirectionTexture(sf::Color::Green, Player::Direction::DOWN);
        playerTextures[Player::Direction::LEFT] = createDirectionTexture(sf::Color::Blue, Player::Direction::LEFT);
        playerTextures[Player::Direction::RIGHT] = createDirectionTexture(sf::Color::Yellow, Player::Direction::RIGHT);

        engine.log("Created placeholder sprites with colors: UP=Red, DOWN=Green, LEFT=Blue, RIGHT=Yellow");
    } else {
        engine.log("Successfully loaded all direction sprites!");
    }

    // Tworzenie obiektu gracza z teksturami kierunków
    Player player(playerTextures, 400.f, 300.f, 3.0f);

    engine.log("Custom main loop started.");

    // Zegar do pomiaru czasu między klatkami
    sf::Clock clock;
    bool firstFrame = true;

    while (window->isOpen())
    {
        // Oblicz czas od ostatniej klatki
        float deltaTime = clock.restart().asSeconds();

        // UPDATE GRACZA (teraz z automatyczną zmianą sprite'a w zależności od kierunku)
        player.update();

        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                int mx = event.mouseButton.x;
                int my = event.mouseButton.y;

                engine.log("Mouse click at: " + std::to_string(mx) + ", " + std::to_string(my));

                buffer.clear(sf::Color(50, 50, 50));
                PrimitiveRenderer bufferRenderer(&buffer);
                drawAllFigures(bufferRenderer, player);

                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    engine.log("Running FLOOD FILL...");
                    bufferRenderer.floodFill0(mx, my, sf::Color::Blue, sf::Color(50, 50, 50));
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    engine.log("Running BOUNDARY FILL...");
                    bufferRenderer.boundaryFillIterative0(mx, my, sf::Color::Yellow, sf::Color::Red);
                }

                buffer.display();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                engine.log("Key pressed: " + std::to_string(event.key.code));
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
            }
        }

        buffer.clear(sf::Color(50, 50, 50));
        PrimitiveRenderer bufferRenderer(&buffer);
        drawAllFigures(bufferRenderer, player);
        buffer.display();

        if (firstFrame) {
            firstFrame = false;
        }

        // Rysuj aktualną scenę
        window->clear();
        sf::Sprite sprite(buffer.getTexture());
        window->draw(sprite);
        window->display();
    }

    engine.log("Custom main loop ended.");
    return 0;
}