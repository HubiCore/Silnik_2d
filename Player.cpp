#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

Player::Player(float x, float y, float speed)
    : speed(speed)
{
    translate(x, y);
    createPlaceholderSprites();
    setDirection(Direction::DOWN);
}

bool Player::loadSprites(const std::string& folder)
{
    bool ok = true;

    ok &= directionTextures[Direction::UP].loadFromFile(folder + "/up.png");
    ok &= directionTextures[Direction::DOWN].loadFromFile(folder + "/down.png");
    ok &= directionTextures[Direction::LEFT].loadFromFile(folder + "/left.png");
    ok &= directionTextures[Direction::RIGHT].loadFromFile(folder + "/right.png");
    /*
    ok &= directionTextures[Direction::UP].loadFromFile(folder + "/up.png");
    ok &= directionTextures[Direction::DOWN].loadFromFile(folder + "/down.png");
    ok &= directionTextures[Direction::LEFT].loadFromFile(folder + "/left.png");
    ok &= directionTextures[Direction::RIGHT].loadFromFile(folder + "/right.png");
    ok &= directionTextures[Direction::UP].loadFromFile(folder + "/up.png");
    ok &= directionTextures[Direction::DOWN].loadFromFile(folder + "/down.png");
    ok &= directionTextures[Direction::LEFT].loadFromFile(folder + "/left.png");
    ok &= directionTextures[Direction::RIGHT].loadFromFile(folder + "/right.png");
*/

    if (!ok)
        std::cout << "Failed to load sprites. Using placeholders.\n";

    return ok;
}

void Player::createPlaceholderSprites()
{
    auto makeTex = [](sf::Color c, Direction d) {
        sf::Image img;
        img.create(64, 64, sf::Color::Transparent);

        for (int y = 8; y < 24; y++)
            for (int x = 8; x < 24; x++)
                img.setPixel(x, y, c);

        if (d == Direction::UP)
            for (int x = 12; x < 20; x++)
                for (int y = 4; y < 8; y++)
                    img.setPixel(x, y, c);

        if (d == Direction::DOWN)
            for (int x = 12; x < 20; x++)
                for (int y = 24; y < 28; y++)
                    img.setPixel(x, y, c);

        if (d == Direction::LEFT)
            for (int x = 4; x < 8; x++)
                for (int y = 12; y < 20; y++)
                    img.setPixel(x, y, c);

        if (d == Direction::RIGHT)
            for (int x = 24; x < 28; x++)
                for (int y = 12; y < 20; y++)
                    img.setPixel(x, y, c);

        sf::Texture tex;
        tex.loadFromImage(img);
        return tex;
    };

    directionTextures[Direction::UP]    = makeTex(sf::Color::Red,    Direction::UP);
    directionTextures[Direction::DOWN]  = makeTex(sf::Color::Green,  Direction::DOWN);
    directionTextures[Direction::LEFT]  = makeTex(sf::Color::Blue,   Direction::LEFT);
    directionTextures[Direction::RIGHT] = makeTex(sf::Color::Yellow, Direction::RIGHT);
}

void Player::setDirection(Direction newDirection)
{
    currentDirection = newDirection;
    setTexture(directionTextures[currentDirection]);
}

void Player::update()
{
    bool moved = false;
    Direction newDir = currentDirection;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        translate(0, -speed); newDir = Direction::UP; moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { translate(0,  speed); newDir = Direction::DOWN; moved = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { translate(-speed, 0); newDir = Direction::LEFT; moved = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { translate( speed, 0); newDir = Direction::RIGHT; moved = true; }

    if (moved && newDir != currentDirection)
        setDirection(newDir);
}

sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}
