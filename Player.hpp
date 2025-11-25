#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SpriteObject.hpp"
#include <string>
#include <map>

class Player : public SpriteObject {
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };

    Player() = default;
    explicit Player(const std::map<Direction, sf::Texture>& textures, float startX = 0.f, float startY = 0.f, float speed = 2.0f);

    std::string getType() const override { return "Player"; }

    void update() override;

    float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; }

    bool checkCollision(const sf::FloatRect& bounds) const;
    sf::FloatRect getGlobalBounds() const;

    void setDirection(Direction newDirection);

private:
    float speed = .0f;
    Direction currentDirection = Direction::DOWN;
    std::map<Direction, sf::Texture> directionTextures;
};

#endif