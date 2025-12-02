#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

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
        img.create(64, 64, sf::Color::Transparent);

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

    // ustaw nową animację
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

    animate(0.016f); // albo dt z Engine


    sf::Vector2f oldPosition = getPosition();
    sf::Vector2f movement(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        translate(0, -speed); newDir = Direction::UP; moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { translate(0,  speed); newDir = Direction::DOWN; moved = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) { translate(-speed, 0); newDir = Direction::LEFT; moved = true; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { translate( speed, 0); newDir = Direction::RIGHT; moved = true; }

    sf::Vector2f newPosition = calculateNewPosition(movement);

    if (moved && isPositionValid(newPosition)) {
        // Ustaw nową pozycję
        setPosition(newPosition.x, newPosition.y);
        lastValidPosition = newPosition;

        if (newDir != currentDirection) {
            setDirection(newDir);
        }
    } else if (moved) {
        if (!checkCollisionWithBounds()) {
            // Gracz wyszedł poza granice - cofnij ruch
            setPosition(oldPosition.x, oldPosition.y);
            moved = false;
        } else {
            // Zapisz poprawną pozycję
            lastValidPosition = getPosition();

            if (newDir != currentDirection)
                setDirection(newDir);
            // Spróbuj osobno ruch w osi X i Y
            sf::Vector2f xMovement(movement.x, 0);
            sf::Vector2f yMovement(0, movement.y);

            sf::Vector2f xPosition = calculateNewPosition(xMovement);
            sf::Vector2f yPosition = calculateNewPosition(yMovement);

            bool xValid = isPositionValid(xPosition);
            bool yValid = isPositionValid(yPosition);

            if (xValid && !yValid) {
                // Możliwy tylko ruch w osi X
                setPosition(xPosition.x, xPosition.y);
                lastValidPosition = xPosition;
                if (movement.x < 0) newDir = Direction::LEFT;
                else if (movement.x > 0) newDir = Direction::RIGHT;
            } else if (!xValid && yValid) {
                // Możliwy tylko ruch w osi Y
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
        // Przywróć ostatnią poprawną pozycję
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

    // Sprawdź czy gracz jest całkowicie wewnątrz granic
    return boundaries.contains(playerBounds.left, playerBounds.top) &&
           boundaries.contains(playerBounds.left + playerBounds.width,
                              playerBounds.top + playerBounds.height);
}

void Player::clampToBounds() {
    sf::FloatRect playerBounds = getGlobalBounds();
    sf::Vector2f  newPosition = getPosition();

    // Jeśli gracz jest poza lewą krawędzią
    if (playerBounds.left < boundaries.left) {
        newPosition.x += (boundaries.left - playerBounds.left);
    }
    // Jeśli gracz jest poza prawą krawędzią
    else if (playerBounds.left + playerBounds.width > boundaries.left + boundaries.width) {
        newPosition.x -= (playerBounds.left + playerBounds.width - (boundaries.left + boundaries.width));
    }

    // Jeśli gracz jest poza górną krawędzią
    if (playerBounds.top < boundaries.top) {
        newPosition.y += (boundaries.top - playerBounds.top);
    }
    // Jeśli gracz jest poza dolną krawędzią
    else if (playerBounds.top + playerBounds.height > boundaries.top + boundaries.height) {
        newPosition.y -= (playerBounds.top + playerBounds.height - (boundaries.top + boundaries.height));
    }


    }

    void Player::addCollisionObject(const sf::FloatRect& object) {
        collisionObjects.push_back(object);
    }

    void Player::clearCollisionObjects() {
        collisionObjects.clear();
    }

    bool Player::checkCollisionWithObjects() const {
        sf::FloatRect playerBounds = getGlobalBounds();

        for (const auto& obj : collisionObjects) {
            if (playerBounds.intersects(obj)) {
                return true;
            }
        }

        return false;
    }

    bool Player::checkCollisionWithObject(const sf::FloatRect& object) const {
        return getGlobalBounds().intersects(object);
    }

    sf::Vector2f Player::calculateNewPosition(const sf::Vector2f& movement) const {
        sf::Vector2f currentPos = getPosition();
        return sf::Vector2f(currentPos.x + movement.x, currentPos.y + movement.y);
    }

    bool Player::isPositionValid(const sf::Vector2f& position) const {
        // Utwórz tymczasowy prostokąt dla gracza w nowej pozycji
        sf::FloatRect tempBounds = getGlobalBounds();
        tempBounds.left = position.x;
        tempBounds.top = position.y;

        // Sprawdź kolizję z granicami
        bool boundsOk = boundaries.contains(tempBounds.left, tempBounds.top) &&
                        boundaries.contains(tempBounds.left + tempBounds.width,
                                            tempBounds.top + tempBounds.height);

        if (!boundsOk) {
            return false;
        }

        // Sprawdź kolizję z obiektami
        for (const auto& obj : collisionObjects) {
            if (tempBounds.intersects(obj)) {
                return false;
            }

        }
    }

