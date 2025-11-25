#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(const std::map<Direction, sf::Texture>& textures, float startX, float startY, float speed)
    : SpriteObject(textures.at(Direction::DOWN)), speed(speed), directionTextures(textures)
{
    translate(startX, startY);
}

void Player::update() {
    bool moved = false;
    Direction newDirection = currentDirection;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        translate(0, -speed);
        newDirection = Direction::UP;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        translate(0, speed);
        newDirection = Direction::DOWN;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        translate(-speed, 0);
        newDirection = Direction::LEFT;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        translate(speed, 0);
        newDirection = Direction::RIGHT;
        moved = true;
    }

    // Zmiana tekstury tylko jeśli kierunek się zmienił
    if (moved && newDirection != currentDirection) {
        setDirection(newDirection);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        rotate(-15);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        rotate(15);
    }
}

void Player::setDirection(Direction newDirection) {
    currentDirection = newDirection;
    setTexture(directionTextures[currentDirection]);
}

bool Player::checkCollision(const sf::FloatRect& bounds) const {
    return getGlobalBounds().intersects(bounds);
}

sf::FloatRect Player::getGlobalBounds() const {
    return getSprite().getGlobalBounds();
}