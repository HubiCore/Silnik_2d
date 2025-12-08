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

    // Auto-detect frame count if not specified
    if (frameCount <= 0) {
        // Check for common frame sizes
        if (frameWidth <= 0 || frameHeight <= 0) {
            // Try to detect based on texture dimensions
            if (texSize.x % 64 == 0 && texSize.y == 64) {
                // 64x64 frames (common for character sprites)
                frameCount = texSize.x / 64;
                frameWidth = 64;
                frameHeight = 64;
                std::cout << "Auto-detected: " << frameCount << " frames of 64x64" << std::endl;
            }
            else if (texSize.x % 32 == 0 && texSize.y == 64) {
                // 32x64 frames (common for tall character sprites)
                frameCount = texSize.x / 32;
                frameWidth = 32;
                frameHeight = 64;
                std::cout << "Auto-detected: " << frameCount << " frames of 32x64" << std::endl;
            }
            else if (texSize.x % 64 == 0) {
                // 64px wide frames, any height
                frameCount = texSize.x / 64;
                frameWidth = 64;
                frameHeight = texSize.y;
                std::cout << "Auto-detected: " << frameCount << " frames of "
                          << frameWidth << "x" << frameHeight << std::endl;
            }
            else if (texSize.x % 32 == 0) {
                // 32px wide frames, any height
                frameCount = texSize.x / 32;
                frameWidth = 32;
                frameHeight = texSize.y;
                std::cout << "Auto-detected: " << frameCount << " frames of "
                          << frameWidth << "x" << frameHeight << std::endl;
            }
            else {
                // Default: 4 frames
                frameCount = 4;
                frameWidth = texSize.x / frameCount;
                frameHeight = texSize.y;
                std::cout << "Using default: " << frameCount << " frames of "
                          << frameWidth << "x" << frameHeight << std::endl;
            }
        }
    }
    else {
        // Use specified frame count
        if (frameWidth <= 0) {
            frameWidth = texSize.x / frameCount;
        }
        if (frameHeight <= 0) {
            frameHeight = texSize.y;
        }
    }

    // Create frames
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
    updateSprite(); // Update sprite with current frame
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
        updateSprite(); // Update sprite after advancing frame
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
    updateSprite(); // Just use the public method
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