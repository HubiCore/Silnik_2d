#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <filesystem>

Player::Player(float x, float y, float speed)
    : AnimatedObject(sprite), speed(speed), boundaries(0, 0, 800, 600) {
    translate(x, y);
    lastValidPosition = sf::Vector2f(x, y);
    createPlaceholderSprites();
    setDirection(Direction::DOWN);
    sprite.setScale(0.5f, 0.5f);
}

bool Player::loadSprites(const std::string& folder)
{
    bool ok = true;

    ok &= directionTextures[Direction::UP].loadFromFile(folder + "/up.png");
    ok &= directionTextures[Direction::DOWN].loadFromFile(folder + "/down.png");
    ok &= directionTextures[Direction::LEFT].loadFromFile(folder + "/left.png");
    ok &= directionTextures[Direction::RIGHT].loadFromFile(folder + "/right.png");

    if (!ok) {
        std::cout << "Failed to load sprites. Using placeholders.\n";
        return false;
    }

    // After loading textures, set the current one
    setTexture(directionTextures[currentDirection]);
    return true;
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

    if (ok) {
        // Set current texture and frames
        setTexture(directionTextures[currentDirection]);
        setDirection(currentDirection); // This will update AnimatedObject
    }

    return ok;
}

bool Player::loadSpriteSheets(const std::string& folder)
{
    // Mapowanie nazw plików na kierunki
    std::map<Direction, std::vector<std::string>> sheetFiles = {
        {Direction::UP, {"up_strip.png", "up_sheet.png", "up_anim.png", "up.png"}},
        {Direction::DOWN, {"down_strip.png", "down_sheet.png", "down_anim.png", "down.png"}},
        {Direction::LEFT, {"left_strip.png", "left_sheet.png", "left_anim.png", "left.png"}},
        {Direction::RIGHT, {"right_strip.png", "right_sheet.png", "right_anim.png", "right.png"}}
    };

    bool ok = true;

    for (const auto& [dir, filenames] : sheetFiles) {
        bool loaded = false;

        for (const auto& filename : filenames) {
            std::string path = folder + "/" + filename;

            if (std::filesystem::exists(path)) {
                if (loadSpriteSheet(dir, path)) {
                    loaded = true;
                    break;
                }
            }
        }

        if (!loaded) {
            std::cout << "Sprite sheet not found for direction: " << static_cast<int>(dir) << std::endl;
            ok = false;
        }
    }

    // Set default texture and frames
    if (ok) {
        setTexture(directionTextures[currentDirection]);
        setDirection(currentDirection);
    }

    return ok;
}

bool Player::loadSpriteSheet(Direction dir, const std::string& filename, int frameCount)
{
    sf::Texture tex;
    if (!tex.loadFromFile(filename)) {
        std::cout << "Failed to load sprite sheet: " << filename << std::endl;
        return false;
    }

    directionTextures[dir] = tex;

    sf::Vector2u size = tex.getSize();
    int frameWidth;

    if (frameCount > 0) {
        frameWidth = size.x / frameCount;
    } else {
        // Auto-detect based on common frame sizes
        // Try 64x64 first, then 32x64, then 32x32
        if (size.x % 64 == 0 && size.y == 64) {
            frameCount = size.x / 64;  // 64x64 frames
            std::cout << "Detected 64x64 frames: " << frameCount << " frames" << std::endl;
        }
        else if (size.x % 32 == 0 && size.y == 64) {
            frameCount = size.x / 32;  // 32x64 frames
            std::cout << "Detected 32x64 frames: " << frameCount << " frames" << std::endl;
        }
        else if (size.x % 32 == 0 && size.y == 32) {
            frameCount = size.x / 32;  // 32x32 frames
            std::cout << "Detected 32x32 frames: " << frameCount << " frames" << std::endl;
        }
        else {
            // Default: assume 4 frames
            frameCount = 4;
            std::cout << "Could not detect frame size, using default: " << frameCount << " frames" << std::endl;
        }

        frameWidth = size.x / frameCount;
    }

    std::vector<sf::IntRect> frames;
    for (int i = 0; i < frameCount; i++) {
        frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, size.y));
    }

    directionFrames[dir] = frames;

    std::cout << "Loaded sprite sheet: " << filename
              << " for direction: " << static_cast<int>(dir)
              << " (" << frameCount << " frames, "
              << frameWidth << "x" << size.y << " each)" << std::endl;

    return true;
}

void Player::createPlaceholderSprites()
{
    auto makeTex = [](sf::Color c, Direction d) {
        const int frameCount = 4;
        const int frameWidth = 32;
        const int frameHeight = 64;

        sf::Image img;
        img.create(frameWidth * frameCount, frameHeight, sf::Color::Transparent);

        for (int frame = 0; frame < frameCount; frame++) {
            sf::Color frameColor = c;
            if (frame == 1) frameColor = sf::Color(c.r * 0.9, c.g * 0.9, c.b * 0.9);
            if (frame == 2) frameColor = sf::Color(c.r * 0.8, c.g * 0.8, c.b * 0.8);
            if (frame == 3) frameColor = sf::Color(c.r * 0.7, c.g * 0.7, c.b * 0.7);

            int frameOffset = frame * frameWidth;

            // Body
            for (int y = 8; y < 24; y++)
                for (int x = 8; x < 24; x++)
                    img.setPixel(frameOffset + x, y, frameColor);

            // Direction indicator
            if (d == Direction::UP)
                for (int x = 12; x < 20; x++)
                    for (int y = 4; y < 8; y++)
                        img.setPixel(frameOffset + x, y, frameColor);

            if (d == Direction::DOWN)
                for (int x = 12; x < 20; x++)
                    for (int y = 24; y < 28; y++)
                        img.setPixel(frameOffset + x, y, frameColor);

            if (d == Direction::LEFT)
                for (int x = 4; x < 8; x++)
                    for (int y = 12; y < 20; y++)
                        img.setPixel(frameOffset + x, y, frameColor);

            if (d == Direction::RIGHT)
                for (int x = 24; x < 28; x++)
                    for (int y = 12; y < 20; y++)
                        img.setPixel(frameOffset + x, y, frameColor);
        }

        sf::Texture tex;
        tex.loadFromImage(img);
        return tex;
    };

    directionTextures[Direction::UP]    = makeTex(sf::Color::Red,    Direction::UP);
    directionTextures[Direction::DOWN]  = makeTex(sf::Color::Green,  Direction::DOWN);
    directionTextures[Direction::LEFT]  = makeTex(sf::Color::Blue,   Direction::LEFT);
    directionTextures[Direction::RIGHT] = makeTex(sf::Color::Yellow, Direction::RIGHT);

    // Create frames for placeholders
    for (auto& [dir, tex] : directionTextures) {
        sf::Vector2u size = tex.getSize();
        int frameCount = 4;
        int frameWidth = size.x / frameCount;

        std::vector<sf::IntRect> frames;
        for (int i = 0; i < frameCount; i++) {
            frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, size.y));
        }
        directionFrames[dir] = frames;
    }
}

void Player::setDirection(Direction newDirection)
{
    currentDirection = newDirection;

    setTexture(directionTextures[currentDirection]);

    // Użyj metod z AnimatedObject do zarządzania klatkami
    AnimatedObject::clear();
    if (directionFrames.find(currentDirection) != directionFrames.end()) {
        for (const auto& frame : directionFrames[currentDirection]) {
            AnimatedObject::addFrame(frame);
        }
    }

    AnimatedObject::reset();
}

void Player::animate(float dt)
{
    AnimatedObject::animate(dt);
}

void Player::update()
{
    bool moved = false;
    Direction newDir = currentDirection;

    // Update animation using AnimatedObject's method
    AnimatedObject::animate(0.016f);

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

    // Normalize diagonal movement (z drugiego kodu)
    if (movement.x != 0 && movement.y != 0) {
        movement.x *= 0.7071f; // sqrt(2)/2
        movement.y *= 0.7071f;
    }

    sf::Vector2f newPosition = calculateNewPosition(movement);

    // Uproszczona logika ruchu z drugiego kodu
    if (moved) {
        if (isPositionValid(newPosition)) {
            setPosition(newPosition.x, newPosition.y);
            lastValidPosition = newPosition;
        } else {
            // Try moving only horizontally
            sf::Vector2f horizontalPos = calculateNewPosition(sf::Vector2f(movement.x, 0));
            if (isPositionValid(horizontalPos)) {
                setPosition(horizontalPos.x, horizontalPos.y);
                lastValidPosition = horizontalPos;
            } else {
                // Try moving only vertically
                sf::Vector2f verticalPos = calculateNewPosition(sf::Vector2f(0, movement.y));
                if (isPositionValid(verticalPos)) {
                    setPosition(verticalPos.x, verticalPos.y);
                    lastValidPosition = verticalPos;
                } else {
                    // Stay in place
                    setPosition(oldPosition.x, oldPosition.y);
                }
            }
        }

        // Change direction if needed
        if (newDir != currentDirection) {
            setDirection(newDir);
        }
    }
}

// Pozostałe metody pozostają bez zmian jak w pierwszym kodzie
// (getGlobalBounds, setBoundaries, isOutOfBounds, keepInBounds,
// getPosition, setPosition, checkCollisionWithBounds, clampToBounds,
// metody hitboxów, funkcje pomocnicze do kolizji, itd.)

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

// Funkcje pomocnicze do kolizji (bez zmian)
bool Player::rectangleIntersectsRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    return rect1.intersects(rect2);
}

bool Player::circleIntersectsRect(const sf::Vector2f& center, float radius, const sf::FloatRect& rect) {
    float closestX = std::max(rect.left, std::min(center.x, rect.left + rect.width));
    float closestY = std::max(rect.top, std::min(center.y, rect.top + rect.height));

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

    for (const auto& point : polygon) {
        if (rect.contains(point)) {
            return true;
        }
    }

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

    for (size_t i = 0; i < polygon.size(); i++) {
        size_t j = (i + 1) % polygon.size();

        sf::Vector2f p1 = polygon[i];
        sf::Vector2f p2 = polygon[j];

        if ((p1.y <= rect.top && p2.y >= rect.top) || (p2.y <= rect.top && p1.y >= rect.top)) {
            float x = p1.x + (rect.top - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            if (x >= rect.left && x <= rect.left + rect.width) {
                return true;
            }
        }

        if ((p1.y <= rect.top + rect.height && p2.y >= rect.top + rect.height) ||
            (p2.y <= rect.top + rect.height && p1.y >= rect.top + rect.height)) {
            float x = p1.x + (rect.top + rect.height - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            if (x >= rect.left && x <= rect.left + rect.width) {
                return true;
            }
        }

        if ((p1.x <= rect.left && p2.x >= rect.left) || (p2.x <= rect.left && p1.x >= rect.left)) {
            float y = p1.y + (rect.left - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            if (y >= rect.top && y <= rect.top + rect.height) {
                return true;
            }
        }

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

    bool boundsOk = boundaries.contains(tempBounds.left, tempBounds.top) &&
                    boundaries.contains(tempBounds.left + tempBounds.width,
                                       tempBounds.top + tempBounds.height);
    if (!boundsOk)
        return false;

    for (const auto& shape : collisionShapes) {
        if (shapeIntersectsRect(shape, tempBounds)) {
            return false;
        }
    }

    return true;
}