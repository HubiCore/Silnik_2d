#include "AnimatedObject.hpp"
#include <filesystem>
#include <iostream>
#include <cmath>

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

    reset();
    return !frames.empty();
}

bool AnimatedObject::loadSpriteSheet(const std::string& filename,
                                     int frameCount,
                                     int frameWidth,
                                     int frameHeight)
{
    frames.clear();

    static sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        std::cerr << "Failed to load spritesheet: " << filename << std::endl;
        return false;
    }

    if (anim) {
        anim->setTexture(texture);
    }

    sf::Vector2u texSize = texture.getSize();

    if (frameCount <= 0) {

        if (frameWidth <= 0 || frameHeight <= 0) {

            if (texSize.x % 64 == 0 && texSize.y == 64) {

                frameCount = texSize.x / 64;
                frameWidth = 64;
                frameHeight = 64;
                std::cout << "Auto-detected: " << frameCount << " frames of 64x64" << std::endl;
            }
            else if (texSize.x % 32 == 0 && texSize.y == 64) {

                frameCount = texSize.x / 32;
                frameWidth = 32;
                frameHeight = 64;
                std::cout << "Auto-detected: " << frameCount << " frames of 32x64" << std::endl;
            }
            else if (texSize.x % 64 == 0) {

                frameCount = texSize.x / 64;
                frameWidth = 64;
                frameHeight = texSize.y;
                std::cout << "Auto-detected: " << frameCount << " frames of "
                          << frameWidth << "x" << frameHeight << std::endl;
            }
            else if (texSize.x % 32 == 0) {

                frameCount = texSize.x / 32;
                frameWidth = 32;
                frameHeight = texSize.y;
                std::cout << "Auto-detected: " << frameCount << " frames of "
                          << frameWidth << "x" << frameHeight << std::endl;
            }
            else {

                frameCount = 4;
                frameWidth = texSize.x / frameCount;
                frameHeight = texSize.y;
                std::cout << "Using default: " << frameCount << " frames of "
                          << frameWidth << "x" << frameHeight << std::endl;
            }
        }
    }
    else {

        if (frameWidth <= 0) {
            frameWidth = texSize.x / frameCount;
        }
        if (frameHeight <= 0) {
            frameHeight = texSize.y;
        }
    }

    for (int i = 0; i < frameCount; i++) {
        frames.emplace_back(i * frameWidth, 0, frameWidth, frameHeight);
    }

    reset();

    std::cout << "Loaded spritesheet: " << filename
              << " (" << frameCount << " frames, "
              << frameWidth << "x" << frameHeight << " each)" << std::endl;

    return true;
}

bool AnimatedObject::loadSpriteSheetAuto(const std::string& filename)
{
    return loadSpriteSheet(filename, 0, 0, 0);
}

void AnimatedObject::addFrame(const sf::IntRect& frame)
{
    frames.push_back(frame);
    updateSprite();

}

void AnimatedObject::animate(float dt)
{
    if (frames.empty() || anim == nullptr || !playing)
        return;

    frameTimer += dt;
    if (frameTimer >= frameTime)
    {
        frameTimer = 0.f;
        advanceFrame();
        updateSprite();

    }
}

void AnimatedObject::setCurrentFrame(int frame)
{
    if (isValidFrameIndex(frame)) {
        currentFrame = frame;
        updateSprite();
    }
}

void AnimatedObject::updateSpriteFrame()
{
    updateSprite();

}

void AnimatedObject::advanceFrame()
{
    if (frames.empty()) return;

    currentFrame++;

    if (currentFrame >= static_cast<int>(frames.size())) {
        if (looping) {
            currentFrame = 0;
        } else {
            currentFrame = static_cast<int>(frames.size()) - 1;
            finished = true;
            playing = false;
        }
    }
}