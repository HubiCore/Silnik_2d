#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include "SpriteObject.hpp"
#include "AnimatedObject.hpp"

class Player : public SpriteObject, public AnimatedObject {
public:

    enum class Direction { UP, DOWN, LEFT, RIGHT };

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

    // Metody do kolizji z obiektami
    void setCollisionObjects(const std::vector<sf::FloatRect>& objects);
    void addCollisionObject(const sf::FloatRect& object);
    void clearCollisionObjects();
    bool checkCollisionWithObjects() const;
    bool checkCollisionWithObject(const sf::FloatRect& object) const;
    std::vector<sf::FloatRect> getCollisionObjects() const { return collisionObjects; }

    bool loadAnimatedSprites(const std::string& folder);
    void animate(float dt) override;



private:
    float speed;
    Direction currentDirection = Direction::DOWN;
    sf::FloatRect boundaries; // Granice obszaru gry
    sf::Vector2f lastValidPosition; // Ostatnia poprawna pozycja

    std::map<Direction, sf::Texture> directionTextures;







    bool checkCollisionWithBounds() const;
    void clampToBounds();
    sf::Vector2f calculateNewPosition(const sf::Vector2f& movement) const;
    bool isPositionValid(const sf::Vector2f& position) const;
    std::vector<sf::FloatRect> collisionObjects;

    std::map<Direction, std::vector<sf::IntRect>> directionFrames;
    std::vector<sf::IntRect> frames;
    int currentFrame = 0;
    float frameTimer = 0.f;
    float frameTime = 0.15f; // np 150ms na klatkę


};

#endif
