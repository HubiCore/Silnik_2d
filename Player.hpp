#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <variant>
#include "SpriteObject.hpp"
#include "AnimatedObject.hpp"

class Player : public SpriteObject, public AnimatedObject {
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };

    // Definicje typów hitboxów
    struct RectangleShape {
        sf::FloatRect rect;
    };

    struct CircleShape {
        sf::Vector2f center;
        float radius;
    };

    struct PolygonShape {
        std::vector<sf::Vector2f> points;
    };

    // Użyjemy std::variant do przechowywania różnych typów
    using CollisionShape = std::variant<RectangleShape, CircleShape, PolygonShape>;

    Player(float x, float y, float speed);
    void update() override;
    void setDirection(Direction newDirection);
    bool loadSprites(const std::string& folder);
    void createPlaceholderSprites();
    sf::FloatRect getGlobalBounds() const;
    void setBoundaries(const sf::FloatRect& newBoundaries);
    bool isOutOfBounds() const;
    void keepInBounds();
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);

    // Metody do dodawania różnych typów hitboxów
    void addCollisionRectangle(const sf::FloatRect& rect);
    void addCollisionCircle(const sf::Vector2f& center, float radius);
    void addCollisionPolygon(const std::vector<sf::Vector2f>& points);
    void clearCollisionShapes();
    bool checkCollisionWithShapes() const;

    // Dla kompatybilności
    void addCollisionObject(const sf::FloatRect& object);
    void clearCollisionObjects();
    bool checkCollisionWithObjects() const;

    bool loadAnimatedSprites(const std::string& folder);
    void animate(float dt) override;

private:
    float speed;
    Direction currentDirection = Direction::DOWN;
    sf::FloatRect boundaries;
    sf::Vector2f lastValidPosition;

    std::map<Direction, sf::Texture> directionTextures;
    std::vector<CollisionShape> collisionShapes; // Nowa tablica kształtów

    // Dla kompatybilności ze starym kodem
    std::vector<sf::FloatRect> collisionObjects;

    std::map<Direction, std::vector<sf::IntRect>> directionFrames;
    std::vector<sf::IntRect> frames;
    int currentFrame = 0;
    float frameTimer = 0.f;
    float frameTime = 0.15f;

    bool checkCollisionWithBounds() const;
    void clampToBounds();
    sf::Vector2f calculateNewPosition(const sf::Vector2f& movement) const;
    bool isPositionValid(const sf::Vector2f& position) const;

    // Funkcje pomocnicze do wykrywania kolizji
    static bool rectangleIntersectsRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
    static bool circleIntersectsRect(const sf::Vector2f& center, float radius, const sf::FloatRect& rect);
    static bool polygonIntersectsRect(const std::vector<sf::Vector2f>& polygon, const sf::FloatRect& rect);
    static bool shapeIntersectsRect(const CollisionShape& shape, const sf::FloatRect& rect);

    // Pomocnicza funkcja do sprawdzania punktu wewnątrz wielokąta
    static bool pointInPolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygon);
};

#endif