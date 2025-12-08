#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

class AnimatedObject {
public:
    // Konstruktor z referencją do sprite'a
    AnimatedObject(sf::Sprite& sprite) : anim(&sprite) {}

    // Konstruktor z wskaźnikiem na sprite'a (opcjonalnie)
    AnimatedObject(sf::Sprite* sprite = nullptr) : anim(sprite) {}

    virtual ~AnimatedObject() = default;

    // ===== METODY ŁADOWANIA ANIMACJI =====

    // Ładowanie animacji z pojedynczych plików PNG (0.png, 1.png, ...)
    bool loadAnimatedSprites(const std::string& folder);

    // Ładowanie rolki (spritesheet) z określoną liczbą klatek
    bool loadSpriteSheet(const std::string& filename,
                         int frameCount = 0,
                         int frameWidth = 0,
                         int frameHeight = 0);

    // Ładowanie rolki z automatycznym wykrywaniem liczby klatek
    bool loadSpriteSheetAuto(const std::string& filename);

    // Ręczne dodawanie klatek
    void addFrame(const sf::IntRect& frame);

    // ===== METODY ANIMACJI =====

    // Główna metoda animacji
    virtual void animate(float dt);

    // Kontrola animacji
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

    // Skakanie do konkretnej klatki
    void setCurrentFrame(int frame);

    // ===== GETTERY I SETTERY =====

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

    // Czyszczenie animacji
    void clear() {
        frames.clear();
        currentFrame = 0;
        frameTimer = 0.f;
        if (anim) {
            anim->setTextureRect(sf::IntRect(0, 0, 0, 0));
        }
    }

    // Gettery do chronionych pól
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

    // Aktualizuje sprite'a do aktualnej klatki
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