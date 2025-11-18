#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "ShapeObject.hpp"
#include "UpdatableObject.hpp"
#include "Point2D.hpp"
#include "PrimitiveRenderer.hpp"
#include <SFML/Graphics.hpp>
#include <cmath>

class Player : public ShapeObject, public UpdatableObject {
public:
    Player(float startX = 0.f, float startY = 0.f, sf::Color color = sf::Color::Green, float speed = 5.0f)
        : position(startX, startY), speed(speed), color(color), rotationAngle(0) {}

    // Gettery
    float getX() const { return position.getX(); }
    float getY() const { return position.getY(); }
    float getRotation() const { return rotationAngle; }
    float getSpeed() const { return speed; }

    // Settery
    void setPosition(float x, float y) {
        position.set(x, y);
    }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setColor(const sf::Color& newColor) { color = newColor; }

    // GameObject
    std::string getType() const override { return "Player"; }
    void update() override {} // NIEUŻYWANE - używamy update(float deltaTime)
    void draw() override {}   // NIEUŻYWANE - używamy draw(PrimitiveRenderer&)

    // UpdatableObject
    void update(float deltaTime) override;

    // DrawableObject
    void draw(PrimitiveRenderer& renderer) override;

    // TransformableObject
    void translate(float dx, float dy) override;
    void rotate(float angleDeg) override;
    void scale(float factor) override;

    // Kolizje
    bool checkCollision(float x, float y, float radius) const;

private:
    Point2D position;
    float speed;
    sf::Color color;
    float rotationAngle;
};

// Implementacje metod
inline void Player::update(float deltaTime) {
    // DEBUG: Wypisz pozycję gracza
    // std::cout << "Player position: (" << position.getX() << ", " << position.getY() << ")" << std::endl;

    // Sterowanie graczem z uwzględnieniem czasu
    float frameSpeed = speed * deltaTime * 60.0f;

    // Sprawdzanie stanu klawiszy
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        position.translate(0, -frameSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        position.translate(0, frameSpeed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        position.translate(-frameSpeed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        position.translate(frameSpeed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        rotate(-2.0f * deltaTime * 60.0f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        rotate(2.0f * deltaTime * 60.0f);
    }
}

inline void Player::draw(PrimitiveRenderer& renderer) {
    float x = position.getX();
    float y = position.getY();
    float size = 15.0f;

    float rad = rotationAngle * M_PI / 180.0f;

    // Oblicz wierzchołki trójkąta reprezentującego gracza
    sf::Vector2f front(x + cos(rad) * size, y + sin(rad) * size);
    sf::Vector2f backLeft(x + cos(rad + 2.2f) * size * 0.7f, y + sin(rad + 2.2f) * size * 0.7f);
    sf::Vector2f backRight(x + cos(rad - 2.2f) * size * 0.7f, y + sin(rad - 2.2f) * size * 0.7f);

    // Rysowanie trójkąta (statku gracza)
    std::vector<sf::Vector2f> triangle = {front, backLeft, backRight, front};
    renderer.drawPolyLine(triangle, false, color);

    // Rysowanie punktu w środku (dla debugowania)
    renderer.drawPoint(x, y, sf::Color::White);
}

inline void Player::translate(float dx, float dy) {
    position.translate(dx, dy);
}

inline void Player::rotate(float angleDeg) {
    rotationAngle += angleDeg;
    // Normalizacja kąta do zakresu 0-360
    while (rotationAngle >= 360.0f) rotationAngle -= 360.0f;
    while (rotationAngle < 0.0f) rotationAngle += 360.0f;
}

inline void Player::scale(float factor) {
    speed *= factor;
}

inline bool Player::checkCollision(float x, float y, float radius) const {
    float dx = position.getX() - x;
    float dy = position.getY() - y;
    float distance = sqrt(dx * dx + dy * dy);
    return distance < (radius + 15.0f);
}

#endif // PLAYER_HPP