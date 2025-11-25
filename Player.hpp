#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SpriteObject.hpp"
#include <string>

class Player : public SpriteObject {
public:
    Player() = default;
    explicit Player(const sf::Texture& texture, float startX = 0.f, float startY = 0.f, float speed = 2.0f);

    std::string getType() const override { return "Player"; }

    void update() override;

    float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; }

    bool checkCollision(const sf::FloatRect& bounds) const;
    sf::FloatRect getGlobalBounds() const;

private:
    float speed = 2.0f;
};

#endif