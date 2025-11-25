#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>

Player::Player(const sf::Texture& texture, float startX, float startY, float speed)
    : SpriteObject(texture), speed(speed)
{
    translate(startX, startY);
}

void Player::update() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        translate(0, -speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        translate(0, speed);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        translate(-speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        translate(speed, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        rotate(-45);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
        rotate(45);
    }
}

bool Player::checkCollision(const sf::FloatRect& bounds) const {
    return getGlobalBounds().intersects(bounds);
}

sf::FloatRect Player::getGlobalBounds() const {
    // Teraz możemy wywołać getSprite() const
    return getSprite().getGlobalBounds();
}