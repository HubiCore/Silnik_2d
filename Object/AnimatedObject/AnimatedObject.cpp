#include "AnimatedObject.hpp"
#include <filesystem>
#include <string>

bool AnimatedObject::loadAnimatedSprites(const std::string& folder)
{
    frames.clear();

    int index = 0;
    while (true)
    {
        std::string filename = folder + "/" + std::to_string(index) + ".png";

        sf::Texture temp;
        if (!temp.loadFromFile(filename))
            break;

        sf::Vector2u size = temp.getSize();
        frames.emplace_back(0, 0, size.x, size.y);
        index++;
    }

    currentFrame = 0;
    frameTimer = 0.f;

    return !frames.empty();
}

void AnimatedObject::animate(float dt)
{
    if (frames.empty() || anim == nullptr)
        return;

    frameTimer += dt;
    if (frameTimer >= frameTime)
    {
        frameTimer = 0.f;
        currentFrame = (currentFrame + 1) % frames.size();
        anim->setTextureRect(frames[currentFrame]);
    }
}
