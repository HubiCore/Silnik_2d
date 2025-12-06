#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class AnimatedObject {
public:
    AnimatedObject(sf::Sprite& sprite) : anim(&sprite) {}
    bool loadAnimatedSprites(const std::string& folder);
    virtual void animate(float dt);
    virtual ~AnimatedObject() = default;

protected:
    sf::Sprite* anim;
    std::vector<sf::IntRect> frames;
    int currentFrame = 0;
    float frameTime = 0.15f;
    float frameTimer = 0.f;
};
