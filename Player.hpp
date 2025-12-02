#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "SpriteObject.hpp"
#include "AnimatedObject.hpp"

class Player : public SpriteObject, public AnimatedObject {
public:

    enum class Direction { UP, DOWN, LEFT, RIGHT };

    Player(float x, float y, float speed);

    void update() override;
    void setDirection(Direction newDirection);

    bool loadSprites(const std::string& folder);
    void createPlaceholderSprites();

    sf::FloatRect getGlobalBounds() const;

private:
    float speed;
    Direction currentDirection = Direction::DOWN;


    std::map<Direction, sf::Texture> directionTextures;
};

#endif
