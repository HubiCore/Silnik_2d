#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include <variant>
#include "../Object/sprite/SpriteObject.hpp"
#include "../Object/AnimatedObject/AnimatedObject.hpp"

class Player : public SpriteObject, public AnimatedObject {
public:
    enum class Direction { UP, DOWN, LEFT, RIGHT };
    enum class State { IDLE, WALKING };

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

    using CollisionShape = std::variant<RectangleShape, CircleShape, PolygonShape>;

    Player(float x, float y, float speed);
    void update() override;
    void setDirection(Direction newDirection);
    void setState(State newState);

    bool loadSprites(const std::string& folder);
    bool loadAnimatedSprites(const std::string& folder);
    bool loadSpriteSheets(const std::string& folder);
    bool loadSpriteSheet(Direction dir, const std::string& filename, int frameCount = 0, bool isIdle = false);
    bool loadIdleSprites(const std::string& folder);

    void createPlaceholderSprites();
    sf::FloatRect getGlobalBounds() const;
    void setBoundaries(const sf::FloatRect& newBoundaries);
    bool isOutOfBounds() const;
    void keepInBounds();
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);

    void addCollisionRectangle(const sf::FloatRect& rect);
    void addCollisionCircle(const sf::Vector2f& center, float radius);
    void addCollisionPolygon(const std::vector<sf::Vector2f>& points);
    void clearCollisionShapes();
    bool checkCollisionWithShapes() const;

    void addCollisionObject(const sf::FloatRect& object);
    void clearCollisionObjects();
    bool checkCollisionWithObjects() const;

    void animate(float dt) override;

    int getCurrentFrame() const { return AnimatedObject::getCurrentFrame(); }
    int getFrameCount() const { return AnimatedObject::getFrameCount(); }
    float getFrameTime() const { return AnimatedObject::getFrameTime(); }
    void setFrameTime(float time) { AnimatedObject::setFrameTime(time); }
    void resetAnimation() { AnimatedObject::reset(); }

    sf::Sprite& getSprite() { return *anim; }
    const sf::Sprite& getSprite() const { return *anim; }

    State getState() const { return currentState; }
    Direction getDirection() const { return currentDirection; }

    void setIdleTimeout(float timeout) { idleTimeout = timeout; }
    float getIdleTimeout() const { return idleTimeout; }

private:
    float speed;
    Direction currentDirection = Direction::DOWN;
    State currentState = State::IDLE;
    sf::FloatRect boundaries;
    sf::Vector2f lastValidPosition;
    float idleTimer = 0.f;
    float idleTimeout = 1.0f;

    std::map<Direction, sf::Texture> walkTextures;
    std::map<Direction, std::vector<sf::IntRect>> walkFrames;

    std::map<Direction, sf::Texture> idleTextures;

    std::vector<sf::FloatRect> collisionObjects;
    std::vector<CollisionShape> collisionShapes;

    bool checkCollisionWithBounds() const;
    void clampToBounds();
    sf::Vector2f calculateNewPosition(const sf::Vector2f& movement) const;
    bool isPositionValid(const sf::Vector2f& position) const;

    static bool rectangleIntersectsRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
    static bool circleIntersectsRect(const sf::Vector2f& center, float radius, const sf::FloatRect& rect);
    static bool polygonIntersectsRect(const std::vector<sf::Vector2f>& polygon, const sf::FloatRect& rect);
    static bool shapeIntersectsRect(const CollisionShape& shape, const sf::FloatRect& rect);

    static bool pointInPolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygon);

    void updateTextureForState();
    void loadIdleTexture(Direction dir, const std::string& filename);
    void loadWalkTexture(Direction dir, const std::string& filename, int frameCount);
};
#endif