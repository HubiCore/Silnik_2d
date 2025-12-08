#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class AnimatedObject {
public:

    AnimatedObject(sf::Sprite& sprite) : anim(&sprite) {}

    AnimatedObject(sf::Sprite* sprite = nullptr) : anim(sprite) {}

    virtual ~AnimatedObject() = default;

    bool loadAnimatedSprites(const std::string& folder);

    bool loadSpriteSheet(const std::string& filename,
                         int frameCount = 0,
                         int frameWidth = 0,
                         int frameHeight = 0);

    bool loadSpriteSheetAuto(const std::string& filename);

    void addFrame(const sf::IntRect& frame);

    virtual void animate(float dt);

    void play() { playing = true; }
    void pause() { playing = false; }
    void stop() { playing = false; reset(); }
    void reset() {
        currentFrame = 0;
        frameTimer = 0.f;
        finished = false;
        if (anim && !frames.empty()) {
            anim->setTextureRect(frames[currentFrame]);
        }
    }

    void setCurrentFrame(int frame);

    int getCurrentFrame() const { return currentFrame; }
    int getFrameCount() const { return static_cast<int>(frames.size()); }
    bool isPlaying() const { return playing; }
    bool isEmpty() const { return frames.empty(); }

    float getFrameTime() const { return frameTime; }
    void setFrameTime(float time) { frameTime = time; }

    bool isLooping() const { return looping; }
    void setLooping(bool loop) { looping = loop; }

    void setSprite(sf::Sprite& sprite) { anim = &sprite; }
    void setSprite(sf::Sprite* sprite) { anim = sprite; }

    bool isFinished() const { return finished; }

    void clear() {
        frames.clear();
        currentFrame = 0;
        frameTimer = 0.f;
        if (anim) {
            anim->setTextureRect(sf::IntRect(0, 0, 0, 0));
        }
    }

    const std::vector<sf::IntRect>& getFrames() const { return frames; }
    const sf::IntRect& getFrameAt(int index) const {
        static sf::IntRect emptyRect(0, 0, 0, 0);
        if (index >= 0 && index < static_cast<int>(frames.size())) {
            return frames[index];
        }
        return emptyRect;
    }

    sf::IntRect getCurrentFrameRect() const {
        return getFrameAt(currentFrame);
    }

    const sf::Texture* getTexture() const {
        if (anim && anim->getTexture()) {
            return anim->getTexture();
        }
        return nullptr;
    }

    void updateSprite() {
        if (anim && !frames.empty() && currentFrame >= 0 && currentFrame < static_cast<int>(frames.size())) {
            anim->setTextureRect(frames[currentFrame]);
        }
    }

protected:
    sf::Sprite* anim = nullptr;
    std::vector<sf::IntRect> frames;
    int currentFrame = 0;
    float frameTime = 0.15f;
    float frameTimer = 0.f;
    bool playing = true;
    bool looping = true;
    bool finished = false;

    virtual void updateSpriteFrame();
    virtual void advanceFrame();

private:
    bool isValidFrameIndex(int index) const {
        return index >= 0 && index < static_cast<int>(frames.size());
    }
};