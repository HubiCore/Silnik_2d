/**
 * @file AnimatedObject.hpp
 * @brief Deklaracja klasy AnimatedObject
 * @ingroup AnimatedObject
 *
 * Klasa AnimatedObject zarządza animacjami sprite'ów, obsługując zarówno pojedyncze klatki
 * jak i arkusze sprite'ów. Umożliwia odtwarzanie, pauzowanie i kontrolę animacji.
 */

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>

/**
 * @class AnimatedObject
 * @brief Klasa do zarządzania animacjami sprite'ów
 *
 * Klasa pozwala na ładowanie animacji z pojedynczych plików lub arkuszy sprite'ów,
 * kontrolę odtwarzania (play, pause, stop) oraz automatyczne przełączanie klatek
 * w zadanym czasie. Wspiera zapętlanie i ręczne ustawianie klatek.
 */
class AnimatedObject {
public:
    /**
     * @brief Konstruktor z referencją do sprite'a
     * @param sprite Referencja do sprite'a, który będzie animowany
     */
    AnimatedObject(sf::Sprite& sprite) : anim(&sprite) {}

    /**
     * @brief Konstruktor ze wskaźnikiem na sprite'a
     * @param sprite Wskaźnik do sprite'a, który będzie animowany (domyślnie nullptr)
     */
    AnimatedObject(sf::Sprite* sprite = nullptr) : anim(sprite) {}

    /**
     * @brief Wirtualny destruktor
     */
    virtual ~AnimatedObject() = default;

    /**
     * @brief Ładuje animację z pojedynczych plików w folderze
     * @param folder Ścieżka do folderu z plikami klatek (nazwy: 0.png, 1.png, ...)
     * @return true jeśli załadowano przynajmniej jedną klatkę, false w przeciwnym razie
     */
    bool loadAnimatedSprites(const std::string& folder);

    /**
     * @brief Ładuje animację z arkusza sprite'ów (spritesheet)
     * @param filename Ścieżka do pliku arkusza sprite'ów
     * @param frameCount Liczba klatek w arkuszu (0 = automatyczne wykrywanie)
     * @param frameWidth Szerokość pojedynczej klatki (0 = automatyczne wykrywanie)
     * @param frameHeight Wysokość pojedynczej klatki (0 = automatyczne wykrywanie)
     * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
     */
    bool loadSpriteSheet(const std::string& filename,
                         int frameCount = 0,
                         int frameWidth = 0,
                         int frameHeight = 0);

    /**
     * @brief Ładuje arkusz sprite'ów z automatycznym wykrywaniem parametrów
     * @param filename Ścieżka do pliku arkusza sprite'ów
     * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
     */
    bool loadSpriteSheetAuto(const std::string& filename);

    /**
     * @brief Dodaje ręcznie zdefiniowaną klatkę
     * @param frame Prostokąt definiujący klatkę w teksturze
     */
    void addFrame(const sf::IntRect& frame);

    /**
     * @brief Aktualizuje animację w czasie
     * @param dt Czas, który upłynął od ostatniej aktualizacji (w sekundach)
     */
    virtual void animate(float dt);

    /**
     * @brief Rozpoczyna odtwarzanie animacji
     */
    void play() { playing = true; }

    /**
     * @brief Wstrzymuje odtwarzanie animacji
     */
    void pause() { playing = false; }

    /**
     * @brief Zatrzymuje i resetuje animację do pierwszej klatki
     */
    void stop() { playing = false; reset(); }

    /**
     * @brief Resetuje animację do pierwszej klatki
     */
    void reset() {
        currentFrame = 0;
        frameTimer = 0.f;
        finished = false;
        if (anim && !frames.empty()) {
            anim->setTextureRect(frames[currentFrame]);
        }
    }

    /**
     * @brief Ustawia aktualną klatkę animacji
     * @param frame Indeks klatki do ustawienia
     */
    void setCurrentFrame(int frame);

    /**
     * @brief Pobiera indeks aktualnej klatki
     * @return Indeks aktualnej klatki
     */
    int getCurrentFrame() const { return currentFrame; }

    /**
     * @brief Pobiera liczbę klatek w animacji
     * @return Liczba klatek
     */
    int getFrameCount() const { return static_cast<int>(frames.size()); }

    /**
     * @brief Sprawdza, czy animacja jest odtwarzana
     * @return true jeśli odtwarzana, false w przeciwnym razie
     */
    bool isPlaying() const { return playing; }

    /**
     * @brief Sprawdza, czy animacja jest pusta
     * @return true jeśli brak klatek, false w przeciwnym razie
     */
    bool isEmpty() const { return frames.empty(); }

    /**
     * @brief Pobiera czas wyświetlania pojedynczej klatki
     * @return Czas klatki w sekundach
     */
    float getFrameTime() const { return frameTime; }

    /**
     * @brief Ustawia czas wyświetlania pojedynczej klatki
     * @param time Czas klatki w sekundach
     */
    void setFrameTime(float time) { frameTime = time; }

    /**
     * @brief Sprawdza, czy animacja jest zapętlona
     * @return true jeśli zapętlona, false w przeciwnym razie
     */
    bool isLooping() const { return looping; }

    /**
     * @brief Ustawia zapętlanie animacji
     * @param loop true aby zapętlić, false aby odtworzyć raz
     */
    void setLooping(bool loop) { looping = loop; }

    /**
     * @brief Ustawia sprite'a przez referencję
     * @param sprite Referencja do sprite'a
     */
    void setSprite(sf::Sprite& sprite) { anim = &sprite; }

    /**
     * @brief Ustawia sprite'a przez wskaźnik
     * @param sprite Wskaźnik do sprite'a
     */
    void setSprite(sf::Sprite* sprite) { anim = sprite; }

    /**
     * @brief Sprawdza, czy animacja zakończyła się (tylko przy braku zapętlenia)
     * @return true jeśli zakończona, false w przeciwnym razie
     */
    bool isFinished() const { return finished; }

    /**
     * @brief Czyści wszystkie klatki animacji
     */
    void clear() {
        frames.clear();
        currentFrame = 0;
        frameTimer = 0.f;
        if (anim) {
            anim->setTextureRect(sf::IntRect(0, 0, 0, 0));
        }
    }

    /**
     * @brief Pobiera wektor wszystkich klatek
     * @return Stała referencja do wektora klatek
     */
    const std::vector<sf::IntRect>& getFrames() const { return frames; }

    /**
     * @brief Pobiera klatkę o podanym indeksie
     * @param index Indeks klatki
     * @return Prostokąt klatki lub pusty prostokąt dla nieprawidłowego indeksu
     */
    const sf::IntRect& getFrameAt(int index) const {
        static sf::IntRect emptyRect(0, 0, 0, 0);
        if (index >= 0 && index < static_cast<int>(frames.size())) {
            return frames[index];
        }
        return emptyRect;
    }

    /**
     * @brief Pobiera prostokąt aktualnej klatki
     * @return Prostokąt aktualnej klatki
     */
    sf::IntRect getCurrentFrameRect() const {
        return getFrameAt(currentFrame);
    }

    /**
     * @brief Pobiera teksturę przypisaną do sprite'a
     * @return Wskaźnik do tekstury lub nullptr jeśli brak
     */
    const sf::Texture* getTexture() const {
        if (anim && anim->getTexture()) {
            return anim->getTexture();
        }
        return nullptr;
    }

    /**
     * @brief Aktualizuje sprite'a do aktualnej klatki
     */
    void updateSprite() {
        if (anim && !frames.empty() && currentFrame >= 0 && currentFrame < static_cast<int>(frames.size())) {
            anim->setTextureRect(frames[currentFrame]);
        }
    }

protected:
    sf::Sprite* anim = nullptr;                 ///< Wskaźnik do sprite'a, który jest animowany
    std::vector<sf::IntRect> frames;            ///< Wektor klatek animacji
    int currentFrame = 0;                       ///< Indeks aktualnej klatki
    float frameTime = 0.15f;                    ///< Czas wyświetlania jednej klatki (w sekundach)
    float frameTimer = 0.f;                     ///< Licznik czasu do następnej klatki
    bool playing = true;                        ///< Czy animacja jest odtwarzana
    bool looping = true;                        ///< Czy animacja jest zapętlona
    bool finished = false;                      ///< Czy animacja zakończyła się (tylko bez zapętlenia)

    /**
     * @brief Aktualizuje sprite'a do aktualnej klatki (metoda wirtualna)
     */
    virtual void updateSpriteFrame();

    /**
     * @brief Przechodzi do następnej klatki (metoda wirtualna)
     */
    virtual void advanceFrame();

private:
    /**
     * @brief Sprawdza poprawność indeksu klatki
     * @param index Indeks do sprawdzenia
     * @return true jeśli indeks jest poprawny, false w przeciwnym razie
     */
    bool isValidFrameIndex(int index) const {
        return index >= 0 && index < static_cast<int>(frames.size());
    }
};