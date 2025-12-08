/**
 * @file Player.hpp
 * @brief Deklaracja klasy Player - gracza w grze
 * @ingroup Player
 *
 * Klasa Player reprezentuje gracza w grze, łącząc funkcjonalności SpriteObject
 * i AnimatedObject. Obsługuje animacje chodzenia, kierunki, kolizje i poruszanie się.
 */

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <variant>
#include "../Object/sprite/SpriteObject.hpp"
#include "../Object/AnimatedObject/AnimatedObject.hpp"

/**
 * @class Player
 * @brief Klasa reprezentująca gracza w grze
 *
 * Klasa dziedziczy po SpriteObject i AnimatedObject, zapewniając animowane
 * poruszanie się w czterech kierunkach z obsługą stanów (spoczynek/chód).
 * Implementuje system kolizji z różnymi kształtami oraz ograniczenia ruchu.
 */
class Player : public SpriteObject, public AnimatedObject {
public:
    /**
     * @enum Direction
     * @brief Kierunki poruszania się gracza
     */
    enum class Direction { UP, DOWN, LEFT, RIGHT };

    /**
     * @enum State
     * @brief Stany animacji gracza
     */
    enum class State { IDLE, WALKING };

    /**
     * @struct RectangleShape
     * @brief Struktura reprezentująca prostokątny kształt kolizji
     */
    struct RectangleShape {
        sf::FloatRect rect;  ///< Prostokąt definiujący kształt
    };

    /**
     * @struct CircleShape
     * @brief Struktura reprezentująca okrągły kształt kolizji
     */
    struct CircleShape {
        sf::Vector2f center;  ///< Środek okręgu
        float radius;         ///< Promień okręgu
    };

    /**
     * @struct PolygonShape
     * @brief Struktura reprezentująca wielokątny kształt kolizji
     */
    struct PolygonShape {
        std::vector<sf::Vector2f> points;  ///< Wierzchołki wielokąta
    };

    /**
     * @typedef CollisionShape
     * @brief Wariant mogący przechowywać różne typy kształtów kolizji
     */
    using CollisionShape = std::variant<RectangleShape, CircleShape, PolygonShape>;

    /**
     * @brief Konstruktor klasy Player
     * @param x Pozycja X początkowa
     * @param y Pozycja Y początkowa
     * @param speed Prędkość poruszania się gracza
     */
    Player(float x, float y, float speed);

    /**
     * @brief Aktualizuje stan gracza (nadpisuje metodę z GameObject)
     */
    void update() override;

    /**
     * @brief Ustawia kierunek patrzenia gracza
     * @param newDirection Nowy kierunek
     */
    void setDirection(Direction newDirection);

    /**
     * @brief Ustawia stan animacji gracza
     * @param newState Nowy stan (IDLE lub WALKING)
     */
    void setState(State newState);

    /**
     * @brief Ładuje sprite'y gracza z folderu
     * @param folder Ścieżka do folderu z teksturami
     * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
     */
    bool loadSprites(const std::string& folder);

    /**
     * @brief Ładuje animowane sprite'y chodzenia z folderu
     * @param folder Ścieżka do folderu z teksturami
     * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
     */
    bool loadAnimatedSprites(const std::string& folder);

    /**
     * @brief Ładuje arkusze sprite'ów z folderu
     * @param folder Ścieżka do folderu z teksturami
     * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
     */
    bool loadSpriteSheets(const std::string& folder);

    /**
     * @brief Ładuje arkusz sprite'ów dla określonego kierunku
     * @param dir Kierunek, dla którego ładowany jest arkusz
     * @param filename Nazwa pliku z arkuszem
     * @param frameCount Liczba klatek (0 = auto-detekcja)
     * @param isIdle Czy arkusz dotyczy stanu spoczynku
     * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
     */
    bool loadSpriteSheet(Direction dir, const std::string& filename, int frameCount = 0, bool isIdle = false);

    /**
     * @brief Ładuje sprite'y spoczynku z folderu
     * @param folder Ścieżka do folderu z teksturami
     * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
     */
    bool loadIdleSprites(const std::string& folder);

    /**
     * @brief Tworzy zastępcze sprite'y (placeholdery)
     *
     * Tworzy kolorowe prostokąty jako zastępcze tekstury, gdy nie uda się załadować plików.
     */
    void createPlaceholderSprites();

    /**
     * @brief Pobiera globalne granice sprite'a gracza
     * @return Prostokąt reprezentujący granice sprite'a
     */
    sf::FloatRect getGlobalBounds() const;

    /**
     * @brief Ustawia granice obszaru, w którym może poruszać się gracz
     * @param newBoundaries Nowy prostokąt graniczny
     */
    void setBoundaries(const sf::FloatRect& newBoundaries);

    /**
     * @brief Sprawdza, czy gracz jest poza dozwolonym obszarem
     * @return true jeśli poza granicami, false w przeciwnym razie
     */
    bool isOutOfBounds() const;

    /**
     * @brief Przywraca gracza do ostatniej poprawnej pozycji jeśli jest poza granicami
     */
    void keepInBounds();

    /**
     * @brief Pobiera aktualną pozycję gracza
     * @return Pozycja gracza jako sf::Vector2f
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Ustawia pozycję gracza
     * @param x Nowa pozycja X
     * @param y Nowa pozycja Y
     */
    void setPosition(float x, float y);

    /**
     * @brief Dodaje prostokątny obszar kolizji
     * @param rect Prostokąt definiujący obszar kolizji
     */
    void addCollisionRectangle(const sf::FloatRect& rect);

    /**
     * @brief Dodaje okrągły obszar kolizji
     * @param center Środek okręgu
     * @param radius Promień okręgu
     */
    void addCollisionCircle(const sf::Vector2f& center, float radius);

    /**
     * @brief Dodaje wielokątny obszar kolizji
     * @param points Wierzchołki wielokąta
     */
    void addCollisionPolygon(const std::vector<sf::Vector2f>& points);

    /**
     * @brief Czyści wszystkie kształty kolizji
     */
    void clearCollisionShapes();

    /**
     * @brief Sprawdza kolizję z zdefiniowanymi kształtami
     * @return true jeśli występuje kolizja, false w przeciwnym razie
     */
    bool checkCollisionWithShapes() const;

    /**
     * @brief Dodaje obiekt kolizji (prostokąt)
     * @param object Prostokąt definiujący obiekt kolizji
     */
    void addCollisionObject(const sf::FloatRect& object);

    /**
     * @brief Czyści wszystkie obiekty kolizji
     */
    void clearCollisionObjects();

    /**
     * @brief Sprawdza kolizję z obiektami kolizji
     * @return true jeśli występuje kolizja, false w przeciwnym razie
     */
    bool checkCollisionWithObjects() const;

    /**
     * @brief Aktualizuje animację gracza
     * @param dt Czas od ostatniej klatki w sekundach
     */
    void animate(float dt) override;

    /**
     * @brief Pobiera numer aktualnej klatki animacji
     * @return Numer aktualnej klatki
     */
    int getCurrentFrame() const { return AnimatedObject::getCurrentFrame(); }

    /**
     * @brief Pobiera liczbę klatek w animacji
     * @return Liczba klatek
     */
    int getFrameCount() const { return AnimatedObject::getFrameCount(); }

    /**
     * @brief Pobiera czas wyświetlania jednej klatki
     * @return Czas klatki w sekundach
     */
    float getFrameTime() const { return AnimatedObject::getFrameTime(); }

    /**
     * @brief Ustawia czas wyświetlania jednej klatki
     * @param time Nowy czas klatki w sekundach
     */
    void setFrameTime(float time) { AnimatedObject::setFrameTime(time); }

    /**
     * @brief Resetuje animację do pierwszej klatki
     */
    void resetAnimation() { AnimatedObject::reset(); }

    /**
     * @brief Pobiera referencję do sprite'a gracza
     * @return Referencja do sf::Sprite
     */
    sf::Sprite& getSprite() { return *anim; }

    /**
     * @brief Pobiera stałą referencję do sprite'a gracza
     * @return Stała referencja do sf::Sprite
     */
    const sf::Sprite& getSprite() const { return *anim; }

    /**
     * @brief Pobiera aktualny stan gracza
     * @return Aktualny stan (IDLE lub WALKING)
     */
    State getState() const { return currentState; }

    /**
     * @brief Pobiera aktualny kierunek gracza
     * @return Aktualny kierunek
     */
    Direction getDirection() const { return currentDirection; }

    /**
     * @brief Ustawia czas po którym gracz przechodzi w stan spoczynku
     * @param timeout Czas w sekundach
     */
    void setIdleTimeout(float timeout) { idleTimeout = timeout; }

    /**
     * @brief Pobiera czas przejścia w stan spoczynku
     * @return Czas w sekundach
     */
    float getIdleTimeout() const { return idleTimeout; }

private:
    float speed;                    ///< Prędkość poruszania się gracza
    Direction currentDirection = Direction::DOWN;  ///< Aktualny kierunek
    State currentState = State::IDLE;             ///< Aktualny stan
    sf::FloatRect boundaries;       ///< Granice obszaru ruchu
    sf::Vector2f lastValidPosition; ///< Ostatnia poprawna pozycja
    float idleTimer = 0.f;          ///< Licznik czasu bez ruchu
    float idleTimeout = 1.0f;       ///< Czas po którym przejść w stan spoczynku

    std::map<Direction, sf::Texture> walkTextures;  ///< Tekstury chodzenia dla kierunków
    std::map<Direction, std::vector<sf::IntRect>> walkFrames;  ///< Klatki animacji chodzenia

    std::map<Direction, sf::Texture> idleTextures;  ///< Tekstury spoczynku dla kierunków

    std::vector<sf::FloatRect> collisionObjects;    ///< Obiekty kolizji (prostokąty)
    std::vector<CollisionShape> collisionShapes;    ///< Kształty kolizji

    /**
     * @brief Sprawdza kolizję z granicami obszaru
     * @return true jeśli gracz jest w granicach, false w przeciwnym razie
     */
    bool checkCollisionWithBounds() const;

    /**
     * @brief Przycina pozycję gracza do granic obszaru
     */
    void clampToBounds();

    /**
     * @brief Oblicza nową pozycję na podstawie ruchu
     * @param movement Wektor ruchu
     * @return Nowa pozycja
     */
    sf::Vector2f calculateNewPosition(const sf::Vector2f& movement) const;

    /**
     * @brief Sprawdza, czy pozycja jest poprawna (bez kolizji)
     * @param position Pozycja do sprawdzenia
     * @return true jeśli pozycja jest poprawna, false w przeciwnym razie
     */
    bool isPositionValid(const sf::Vector2f& position) const;

    /**
     * @brief Sprawdza kolizję między dwoma prostokątami
     * @param rect1 Pierwszy prostokąt
     * @param rect2 Drugi prostokąt
     * @return true jeśli prostokąty się przecinają, false w przeciwnym razie
     */
    static bool rectangleIntersectsRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

    /**
     * @brief Sprawdza kolizję między okręgiem a prostokątem
     * @param center Środek okręgu
     * @param radius Promień okręgu
     * @param rect Prostokąt
     * @return true jeśli okrąg i prostokąt się przecinają, false w przeciwnym razie
     */
    static bool circleIntersectsRect(const sf::Vector2f& center, float radius, const sf::FloatRect& rect);

    /**
     * @brief Sprawdza kolizję między wielokątem a prostokątem
     * @param polygon Wierzchołki wielokąta
     * @param rect Prostokąt
     * @return true jeśli wielokąt i prostokąt się przecinają, false w przeciwnym razie
     */
    static bool polygonIntersectsRect(const std::vector<sf::Vector2f>& polygon, const sf::FloatRect& rect);

    /**
     * @brief Sprawdza kolizję między kształtem a prostokątem
     * @param shape Kształt kolizji
     * @param rect Prostokąt
     * @return true jeśli kształt i prostokąt się przecinają, false w przeciwnym razie
     */
    static bool shapeIntersectsRect(const CollisionShape& shape, const sf::FloatRect& rect);

    /**
     * @brief Sprawdza, czy punkt znajduje się wewnątrz wielokąta
     * @param point Punkt do sprawdzenia
     * @param polygon Wierzchołki wielokąta
     * @return true jeśli punkt jest wewnątrz wielokąta, false w przeciwnym razie
     */
    static bool pointInPolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygon);

    /**
     * @brief Aktualizuje teksturę zgodnie z aktualnym stanem i kierunkiem
     */
    void updateTextureForState();

    /**
     * @brief Ładuje teksturę spoczynku dla kierunku
     * @param dir Kierunek
     * @param filename Nazwa pliku
     */
    void loadIdleTexture(Direction dir, const std::string& filename);

    /**
     * @brief Ładuje teksturę chodzenia dla kierunku
     * @param dir Kierunek
     * @param filename Nazwa pliku
     * @param frameCount Liczba klatek
     */
    void loadWalkTexture(Direction dir, const std::string& filename, int frameCount);
};
#endif