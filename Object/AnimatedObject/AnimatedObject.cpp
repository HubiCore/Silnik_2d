/**
 * @file AnimatedObject.cpp
 * @brief Implementacja klasy AnimatedObject
 * @ingroup AnimatedObject
 *
 * Implementacja metod klasy AnimatedObject zdefiniowanych w AnimatedObject.hpp.
 * Zawiera logikę ładowania animacji z plików i arkuszy sprite'ów oraz zarządzania klatkami.
 */

#include "AnimatedObject.hpp"
#include <filesystem>
#include <iostream>
#include <cmath>

/**
 * @brief Ładuje animację z pojedynczych plików w folderze
 * @param folder Ścieżka do folderu z plikami klatek (nazwy: 0.png, 1.png, ...)
 * @return true jeśli załadowano przynajmniej jedną klatkę, false w przeciwnym razie
 *
 * Metoda oczekuje plików o nazwach "0.png", "1.png", itd. w podanym folderze.
 * Ładuje je kolejno aż do napotkania braku pliku. Każdy plik staje się osobną klatką.
 */
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

/**
 * @brief Ładuje animację z arkusza sprite'ów (spritesheet)
 * @param filename Ścieżka do pliku arkusza sprite'ów
 * @param frameCount Liczba klatek w arkuszu (0 = automatyczne wykrywanie)
 * @param frameWidth Szerokość pojedynczej klatki (0 = automatyczne wykrywanie)
 * @param frameHeight Wysokość pojedynczej klatki (0 = automatyczne wykrywanie)
 * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
 *
 * Metoda obsługuje automatyczne wykrywanie parametrów dla typowych rozmiarów klatek
 * (64x64, 32x64, itp.). Jeśli parametry są podane, używa ich bez auto-detekcji.
 */
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

/**
 * @brief Ładuje arkusz sprite'ów z automatycznym wykrywaniem parametrów
 * @param filename Ścieżka do pliku arkusza sprite'ów
 * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
 *
 * Wrapper wywołujący loadSpriteSheet z domyślnymi parametrami (0,0,0)
 * co wymusza automatyczne wykrywanie liczby klatek i ich rozmiarów.
 */
bool AnimatedObject::loadSpriteSheetAuto(const std::string& filename)
{
    return loadSpriteSheet(filename, 0, 0, 0);
}

/**
 * @brief Dodaje ręcznie zdefiniowaną klatkę
 * @param frame Prostokąt definiujący klatkę w teksturze
 *
 * Metoda pozwala na ręczne dodawanie klatek, np. gdy arkusz sprite'ów
 * ma nieregularny układ lub gdy chcemy użyć tylko wybranych klatek.
 */
void AnimatedObject::addFrame(const sf::IntRect& frame)
{
    frames.push_back(frame);
    updateSprite();

}

/**
 * @brief Aktualizuje animację w czasie
 * @param dt Czas, który upłynął od ostatniej aktualizacji (w sekundach)
 *
 * Metoda powinna być wywoływana w każdej klatce gry. Aktualizuje licznik czasu
 * i przechodzi do następnej klatki gdy frameTimer przekroczy frameTime.
 */
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

/**
 * @brief Ustawia aktualną klatkę animacji
 * @param frame Indeks klatki do ustawienia
 *
 * Metoda sprawdza poprawność indeksu i aktualizuje sprite'a do wybranej klatki.
 */
void AnimatedObject::setCurrentFrame(int frame)
{
    if (isValidFrameIndex(frame)) {
        currentFrame = frame;
        updateSprite();
    }
}

/**
 * @brief Aktualizuje sprite'a do aktualnej klatki (metoda wirtualna)
 *
 * Metoda wirtualna pozwalająca na rozszerzenie funkcjonalności aktualizacji
 * sprite'a w klasach pochodnych. Domyślnie wywołuje updateSprite().
 */
void AnimatedObject::updateSpriteFrame()
{
    updateSprite();

}

/**
 * @brief Przechodzi do następnej klatki (metoda wirtualna)
 *
 * Metoda wirtualna zarządzająca przejściem do następnej klatki.
 * Uwzględnia zapętlanie i ustawia flagę finished gdy animacja się kończy.
 */
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