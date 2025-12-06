#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>

Player::Player(float x, float y, float speed)
    : AnimatedObject(sprite), speed(speed), boundaries(0, 0, 800, 600) {
    translate(x, y);
    lastValidPosition = sf::Vector2f(x, y);
    createPlaceholderSprites();
    setDirection(Direction::DOWN);
}

bool Player::loadSprites(const std::string& folder)
{
    bool ok = true;

    ok &= directionTextures[Direction::UP].loadFromFile(folder + "/up.png");
    ok &= directionTextures[Direction::DOWN].loadFromFile(folder + "/down.png");
    ok &= directionTextures[Direction::LEFT].loadFromFile(folder + "/left.png");
    ok &= directionTextures[Direction::RIGHT].loadFromFile(folder + "/right.png");

    if (!ok)
        std::cout << "Failed to load sprites. Using placeholders.\n";

    return ok;
}

bool Player::loadAnimatedSprites(const std::string& folder)
{
    auto load = [&](Direction dir, const std::string& file) {
        sf::Texture tex;
        if (!tex.loadFromFile(folder + "/" + file))
            return false;

        directionTextures[dir] = tex;

        int w = tex.getSize().x / 4; // 4 klatki
        int h = tex.getSize().y;

        std::vector<sf::IntRect> frames;
        for (int i = 0; i < 4; i++)
            frames.push_back(sf::IntRect(i * w, 0, w, h));

        directionFrames[dir] = frames;

        return true;
    };

    bool ok = true;
    ok &= load(Direction::UP,    "up.png");
    ok &= load(Direction::DOWN,  "down.png");
    ok &= load(Direction::LEFT,  "left.png");
    ok &= load(Direction::RIGHT, "right.png");

    return ok;
}

void Player::createPlaceholderSprites()
{
    auto makeTex = [](sf::Color c, Direction d) {
        sf::Image img;
        img.create(32, 32, sf::Color::Transparent);

        for (int y = 8; y < 24; y++)
            for (int x = 8; x < 24; x++)
                img.setPixel(x, y, c);

        if (d == Direction::UP)
            for (int x = 12; x < 20; x++)
                for (int y = 4; y < 8; y++)
                    img.setPixel(x, y, c);

        if (d == Direction::DOWN)
            for (int x = 12; x < 20; x++)
                for (int y = 24; y < 28; y++)
                    img.setPixel(x, y, c);

        if (d == Direction::LEFT)
            for (int x = 4; x < 8; x++)
                for (int y = 12; y < 20; y++)
                    img.setPixel(x, y, c);

        if (d == Direction::RIGHT)
            for (int x = 24; x < 28; x++)
                for (int y = 12; y < 20; y++)
                    img.setPixel(x, y, c);

        sf::Texture tex;
        tex.loadFromImage(img);
        return tex;
    };

    directionTextures[Direction::UP]    = makeTex(sf::Color::Red,    Direction::UP);
    directionTextures[Direction::DOWN]  = makeTex(sf::Color::Green,  Direction::DOWN);
    directionTextures[Direction::LEFT]  = makeTex(sf::Color::Blue,   Direction::LEFT);
    directionTextures[Direction::RIGHT] = makeTex(sf::Color::Yellow, Direction::RIGHT);
}

void Player::setDirection(Direction newDirection)
{
    currentDirection = newDirection;

    setTexture(directionTextures[currentDirection]);

    frames = directionFrames[currentDirection];
    currentFrame = 0;
    frameTimer = 0.f;
}

void Player::animate(float dt)
{
    if (frames.empty())
        return;

    frameTimer += dt;

    if (frameTimer >= frameTime)
    {
        frameTimer = 0.f;
        currentFrame = (currentFrame + 1) % frames.size();

        sprite.setTextureRect(frames[currentFrame]);
    }
}

void Player::update()
{
    bool moved = false;
    Direction newDir = currentDirection;

    animate(0.016f);

    sf::Vector2f oldPosition = getPosition();
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed;
        newDir = Direction::UP; moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed;
        newDir = Direction::DOWN; moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed;
        newDir = Direction::LEFT; moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed;
        newDir = Direction::RIGHT; moved = true;
    }

    sf::Vector2f newPosition = calculateNewPosition(movement);

    if (moved && isPositionValid(newPosition)) {
        setPosition(newPosition.x, newPosition.y);
        lastValidPosition = newPosition;

        if (newDir != currentDirection) {
            setDirection(newDir);
        }
    } else if (moved) {
        if (!checkCollisionWithBounds()) {
            setPosition(oldPosition.x, oldPosition.y);
            moved = false;
        } else {
            lastValidPosition = getPosition();

            if (newDir != currentDirection)
                setDirection(newDir);

            sf::Vector2f xMovement(movement.x, 0);
            sf::Vector2f yMovement(0, movement.y);

            sf::Vector2f xPosition = calculateNewPosition(xMovement);
            sf::Vector2f yPosition = calculateNewPosition(yMovement);

            bool xValid = isPositionValid(xPosition);
            bool yValid = isPositionValid(yPosition);

            if (xValid && !yValid) {
                setPosition(xPosition.x, xPosition.y);
                lastValidPosition = xPosition;
                if (movement.x < 0) newDir = Direction::LEFT;
                else if (movement.x > 0) newDir = Direction::RIGHT;
            } else if (!xValid && yValid) {
                setPosition(yPosition.x, yPosition.y);
                lastValidPosition = yPosition;
                if (movement.y < 0) newDir = Direction::UP;
                else if (movement.y > 0) newDir = Direction::DOWN;
            }

            if ((xValid || yValid) && newDir != currentDirection) {
                setDirection(newDir);
            }
        }
    }
}

sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Player::setBoundaries(const sf::FloatRect& newBoundaries) {
    boundaries = newBoundaries;
}

bool Player::isOutOfBounds() const {
    return !checkCollisionWithBounds();
}

void Player::keepInBounds() {
    if (isOutOfBounds()) {
        setPosition(lastValidPosition.x, lastValidPosition.y);
    }
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

bool Player::checkCollisionWithBounds() const {
    sf::FloatRect playerBounds = getGlobalBounds();
    return boundaries.contains(playerBounds.left, playerBounds.top) &&
           boundaries.contains(playerBounds.left + playerBounds.width,
                              playerBounds.top + playerBounds.height);
}

void Player::clampToBounds() {
    sf::FloatRect playerBounds = getGlobalBounds();
    sf::Vector2f newPosition = getPosition();

    if (playerBounds.left < boundaries.left) {
        newPosition.x += (boundaries.left - playerBounds.left);
    }
    else if (playerBounds.left + playerBounds.width > boundaries.left + boundaries.width) {
        newPosition.x -= (playerBounds.left + playerBounds.width - (boundaries.left + boundaries.width));
    }

    if (playerBounds.top < boundaries.top) {
        newPosition.y += (boundaries.top - playerBounds.top);
    }
    else if (playerBounds.top + playerBounds.height > boundaries.top + boundaries.height) {
        newPosition.y -= (playerBounds.top + playerBounds.height - (boundaries.top + boundaries.height));
    }

    setPosition(newPosition.x, newPosition.y);
}

// Nowe funkcje dla dokładnych hitboxów
void Player::addCollisionRectangle(const sf::FloatRect& rect) {
    RectangleShape shape;
    shape.rect = rect;
    collisionShapes.push_back(shape);
}

void Player::addCollisionCircle(const sf::Vector2f& center, float radius) {
    CircleShape shape;
    shape.center = center;
    shape.radius = radius;
    collisionShapes.push_back(shape);
}

void Player::addCollisionPolygon(const std::vector<sf::Vector2f>& points) {
    PolygonShape shape;
    shape.points = points;
    collisionShapes.push_back(shape);
}

void Player::clearCollisionShapes() {
    collisionShapes.clear();
}

bool Player::checkCollisionWithShapes() const {
    sf::FloatRect playerBounds = getGlobalBounds();
    for (const auto& shape : collisionShapes) {
        if (shapeIntersectsRect(shape, playerBounds)) {
            return true;
        }
    }
    return false;
}

// Stare funkcje dla kompatybilności
void Player::addCollisionObject(const sf::FloatRect& object) {
    // Dodaj jako prostokąt do nowego systemu
    addCollisionRectangle(object);
    // I do starego systemu dla kompatybilności
    collisionObjects.push_back(object);
}

void Player::clearCollisionObjects() {
    collisionShapes.clear();
    collisionObjects.clear();
}

bool Player::checkCollisionWithObjects() const {
    return checkCollisionWithShapes();
}

sf::Vector2f Player::calculateNewPosition(const sf::Vector2f& movement) const {
    sf::Vector2f currentPos = getPosition();
    return sf::Vector2f(currentPos.x + movement.x, currentPos.y + movement.y);
}

// Funkcje pomocnicze do kolizji
bool Player::rectangleIntersectsRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    return rect1.intersects(rect2);
}

bool Player::circleIntersectsRect(const sf::Vector2f& center, float radius, const sf::FloatRect& rect) {
    // Znajdź najbliższy punkt w prostokącie do środka koła
    float closestX = std::max(rect.left, std::min(center.x, rect.left + rect.width));
    float closestY = std::max(rect.top, std::min(center.y, rect.top + rect.height));

    // Oblicz odległość między tym punktem a środkiem koła
    float distanceX = center.x - closestX;
    float distanceY = center.y - closestY;

    return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
}

bool Player::pointInPolygon(const sf::Vector2f& point, const std::vector<sf::Vector2f>& polygon) {
    if (polygon.size() < 3) return false;

    bool inside = false;
    for (size_t i = 0, j = polygon.size() - 1; i < polygon.size(); j = i++) {
        if (((polygon[i].y > point.y) != (polygon[j].y > point.y)) &&
            (point.x < (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) /
             (polygon[j].y - polygon[i].y) + polygon[i].x)) {
            inside = !inside;
        }
    }
    return inside;
}

bool Player::polygonIntersectsRect(const std::vector<sf::Vector2f>& polygon, const sf::FloatRect& rect) {
    if (polygon.empty()) return false;

    // 1. Sprawdź czy którykolwiek wierzchołek wielokąta jest wewnątrz prostokąta
    for (const auto& point : polygon) {
        if (rect.contains(point)) {
            return true;
        }
    }

    // 2. Sprawdź czy którykolwiek wierzchołek prostokąta jest wewnątrz wielokąta
    sf::Vector2f rectPoints[4] = {
        {rect.left, rect.top},
        {rect.left + rect.width, rect.top},
        {rect.left + rect.width, rect.top + rect.height},
        {rect.left, rect.top + rect.height}
    };

    for (int i = 0; i < 4; i++) {
        if (pointInPolygon(rectPoints[i], polygon)) {
            return true;
        }
    }

    // 3. Sprawdź przecięcia krawędzi
    for (size_t i = 0; i < polygon.size(); i++) {
        size_t j = (i + 1) % polygon.size();

        sf::Vector2f p1 = polygon[i];
        sf::Vector2f p2 = polygon[j];

        // Sprawdź przecięcie z każdą krawędzią prostokąta
        // Górna krawędź
        if ((p1.y <= rect.top && p2.y >= rect.top) || (p2.y <= rect.top && p1.y >= rect.top)) {
            float x = p1.x + (rect.top - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            if (x >= rect.left && x <= rect.left + rect.width) {
                return true;
            }
        }

        // Dolna krawędź
        if ((p1.y <= rect.top + rect.height && p2.y >= rect.top + rect.height) ||
            (p2.y <= rect.top + rect.height && p1.y >= rect.top + rect.height)) {
            float x = p1.x + (rect.top + rect.height - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            if (x >= rect.left && x <= rect.left + rect.width) {
                return true;
            }
        }

        // Lewa krawędź
        if ((p1.x <= rect.left && p2.x >= rect.left) || (p2.x <= rect.left && p1.x >= rect.left)) {
            float y = p1.y + (rect.left - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            if (y >= rect.top && y <= rect.top + rect.height) {
                return true;
            }
        }

        // Prawa krawędź
        if ((p1.x <= rect.left + rect.width && p2.x >= rect.left + rect.width) ||
            (p2.x <= rect.left + rect.width && p1.x >= rect.left + rect.width)) {
            float y = p1.y + (rect.left + rect.width - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            if (y >= rect.top && y <= rect.top + rect.height) {
                return true;
            }
        }
    }

    return false;
}

bool Player::shapeIntersectsRect(const CollisionShape& shape, const sf::FloatRect& rect) {
    if (const RectangleShape* rectangle = std::get_if<RectangleShape>(&shape)) {
        return rectangleIntersectsRect(rectangle->rect, rect);
    }
    else if (const CircleShape* circle = std::get_if<CircleShape>(&shape)) {
        return circleIntersectsRect(circle->center, circle->radius, rect);
    }
    else if (const PolygonShape* polygon = std::get_if<PolygonShape>(&shape)) {
        return polygonIntersectsRect(polygon->points, rect);
    }
    return false;
}

bool Player::isPositionValid(const sf::Vector2f& position) const {
    sf::FloatRect tempBounds = getGlobalBounds();
    tempBounds.left = position.x;
    tempBounds.top = position.y;

    // 1. Sprawdź granice okna
    bool boundsOk = boundaries.contains(tempBounds.left, tempBounds.top) &&
                    boundaries.contains(tempBounds.left + tempBounds.width,
                                       tempBounds.top + tempBounds.height);
    if (!boundsOk)
        return false;

    // 2. Sprawdź kolizję z kształtami (nowy system)
    for (const auto& shape : collisionShapes) {
        if (shapeIntersectsRect(shape, tempBounds)) {
            return false;
        }
    }

    return true;
}