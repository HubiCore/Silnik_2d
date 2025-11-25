#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SpriteObject.hpp"
#include <string>

class Player : public SpriteObject {
public:
    Player() = default;
    explicit Player(const sf::Texture& texture);

    std::string getType() const override { return "Player"; }

    void update() override;
};

#endif
