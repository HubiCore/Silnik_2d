/**
 * @file Player.cpp
 * @brief Implementacja klasy Player
 * @ingroup Player
 *
 * Implementacja metod klasy Player zdefiniowanych w Player.hpp.
 * Zawiera logikę poruszania się, animacji, ładowania sprite'ów i obsługi kolizji.
 */

#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <filesystem>

/**
 * @brief Konstruktor klasy Player
 * @param x Pozycja X początkowa
 * @param y Pozycja Y początkowa
 * @param speed Prędkość poruszania się gracza
 *
 * Inicjalizuje gracza na podanej pozycji, tworzy zastępcze sprite'y,
 * ustawia domyślny kierunek (w dół) i stan (spoczynek).
 */
Player::Player(float x, float y, float speed)
    : AnimatedObject(sprite), speed(speed), boundaries(0, 0, 800, 600) {
    translate(x, y);
    lastValidPosition = sf::Vector2f(x, y);
    createPlaceholderSprites();
    setDirection(Direction::DOWN);
    setState(State::IDLE);
    sprite.setScale(1.0f, 1.0f);
}

/**
 * @brief Ładuje sprite'y gracza z folderu
 * @param folder Ścieżka do folderu z teksturami
 * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
 *
 * Metoda próbuje załadować sprite'y na różne sposoby:
 * 1. Jako animowane sprite'y
 * 2. Jako arkusze sprite'ów
 * 3. Jako pojedyncze pliki dla każdego kierunku
 * Jeśli wszystko się nie powiedzie, używa zastępczych sprite'ów.
 */
bool Player::loadSprites(const std::string& folder)
{
    bool ok = true;

    if (loadAnimatedSprites(folder) || loadSpriteSheets(folder)) {
        return true;
    }

    ok &= idleTextures[Direction::UP].loadFromFile(folder + "/up.png");
    ok &= idleTextures[Direction::DOWN].loadFromFile(folder + "/down.png");
    ok &= idleTextures[Direction::LEFT].loadFromFile(folder + "/left.png");
    ok &= idleTextures[Direction::RIGHT].loadFromFile(folder + "/right.png");

    if (!ok) {
        std::cout << "Failed to load sprites. Using placeholders.\n";
        return false;
    }

    updateTextureForState();
    return true;
}

/**
 * @brief Ładuje animowane sprite'y chodzenia z folderu
 * @param folder Ścieżka do folderu z teksturami
 * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
 *
 * Ładuje sprite'y spoczynku, a następnie animacje chodzenia
 * z plików o nazwach: up_walk.png, down_walk.png, itd.
 * Dzieli tekstury na 4 klatki animacji.
 */
bool Player::loadAnimatedSprites(const std::string& folder)
{
    // Najpierw ładuj sprite'y spoczynku
    if (loadIdleSprites(folder)) {
        std::cout << "Idle sprites loaded from: " << folder << std::endl;
    }

    // Lambda do ładowania animacji chodzenia dla kierunku
    auto load = [&](Direction dir, const std::string& file) {
        sf::Texture tex;
        if (!tex.loadFromFile(folder + "/" + file))
            return false;

        walkTextures[dir] = tex;

        int w = tex.getSize().x / 4;  // Zakładamy 4 klatki w poziomie
        int h = tex.getSize().y;

        std::vector<sf::IntRect> frames;
        for (int i = 0; i < 4; i++)
            frames.push_back(sf::IntRect(i * w, 0, w, h));

        walkFrames[dir] = frames;

        return true;
    };

    bool ok = true;
    ok &= load(Direction::UP,    "up_walk.png");
    ok &= load(Direction::DOWN,  "down_walk.png");
    ok &= load(Direction::LEFT,  "left_walk.png");
    ok &= load(Direction::RIGHT, "right_walk.png");

    if (ok) {
        std::cout << "Walk animations loaded from: " << folder << std::endl;
        updateTextureForState();
    }

    return ok;
}

/**
 * @brief Ładuje arkusze sprite'ów z folderu
 * @param folder Ścieżka do folderu z teksturami
 * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
 *
 * Próbuje załadować arkusze sprite'ów z różnych możliwych nazw plików
 * dla każdego kierunku. Używa auto-detekcji liczby klatek.
 */
bool Player::loadSpriteSheets(const std::string& folder)
{
    // Najpierw ładuj sprite'y spoczynku
    if (loadIdleSprites(folder)) {
        std::cout << "Idle sprites loaded from: " << folder << std::endl;
    }

    // Mapowanie kierunków na możliwe nazwy plików
    std::map<Direction, std::vector<std::string>> sheetFiles = {
        {Direction::UP, {"up_walk_strip.png", "up_walk_sheet.png", "up_walk_anim.png", "up_walk.png"}},
        {Direction::DOWN, {"down_walk_strip.png", "down_walk_sheet.png", "down_walk_anim.png", "down_walk.png"}},
        {Direction::LEFT, {"left_walk_strip.png", "left_walk_sheet.png", "left_walk_anim.png", "left_walk.png"}},
        {Direction::RIGHT, {"right_walk_strip.png", "right_walk_sheet.png", "right_walk_anim.png", "right_walk.png"}}
    };

    bool ok = true;

    for (const auto& [dir, filenames] : sheetFiles) {
        bool loaded = false;

        for (const auto& filename : filenames) {
            std::string path = folder + "/" + filename;

            if (std::filesystem::exists(path)) {
                if (loadSpriteSheet(dir, path, 0, false)) {
                    loaded = true;
                    break;
                }
            }
        }

        if (!loaded) {
            std::cout << "Walk sprite sheet not found for direction: " << static_cast<int>(dir) << std::endl;
            ok = false;
        }
    }

    if (ok) {
        std::cout << "All walk animations loaded from: " << folder << std::endl;
        updateTextureForState();
    }

    return ok;
}

/**
 * @brief Ładuje sprite'y spoczynku z folderu
 * @param folder Ścieżka do folderu z teksturami
 * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
 *
 * Próbuje załadować sprite'y spoczynku z różnych możliwych nazw plików.
 */
bool Player::loadIdleSprites(const std::string& folder)
{
    bool ok = true;

    std::map<Direction, std::vector<std::string>> idleFiles = {
        {Direction::UP, {"up_idle.png", "up.png"}},
        {Direction::DOWN, {"down_idle.png", "down.png"}},
        {Direction::LEFT, {"left_idle.png", "left.png"}},
        {Direction::RIGHT, {"right_idle.png", "right.png"}}
    };

    for (const auto& [dir, filenames] : idleFiles) {
        bool loaded = false;

        for (const auto& filename : filenames) {
            std::string path = folder + "/" + filename;

            if (std::filesystem::exists(path)) {
                sf::Texture tex;
                if (tex.loadFromFile(path)) {
                    idleTextures[dir] = tex;
                    loaded = true;
                    std::cout << "Loaded idle sprite for " << static_cast<int>(dir)
                              << " from: " << path << std::endl;
                    break;
                }
            }
        }

        if (!loaded) {
            std::cout << "Idle sprite not found for direction: " << static_cast<int>(dir) << std::endl;
            ok = false;
        }
    }

    return ok;
}

/**
 * @brief Ładuje arkusz sprite'ów dla określonego kierunku
 * @param dir Kierunek, dla którego ładowany jest arkusz
 * @param filename Nazwa pliku z arkuszem
 * @param frameCount Liczba klatek (0 = auto-detekcja)
 * @param isIdle Czy arkusz dotyczy stanu spoczynku
 * @return true jeśli załadowano pomyślnie, false w przeciwnym razie
 *
 * Metoda automatycznie wykrywa liczbę klatek na podstawie rozmiaru tekstury
 * dla typowych rozmiarów (32x64, 64x64, itp.).
 */
bool Player::loadSpriteSheet(Direction dir, const std::string& filename, int frameCount, bool isIdle)
{
    sf::Texture tex;
    if (!tex.loadFromFile(filename)) {
        std::cout << "Failed to load sprite sheet: " << filename << std::endl;
        return false;
    }

    if (isIdle) {
        idleTextures[dir] = tex;
        std::cout << "Loaded idle sprite sheet: " << filename
                  << " for direction: " << static_cast<int>(dir) << std::endl;
        return true;
    } else {
        walkTextures[dir] = tex;

        sf::Vector2u size = tex.getSize();
        int frameWidth;

        if (frameCount > 0) {
            frameWidth = size.x / frameCount;
        } else {
            // Auto-detekcja liczby klatek
            if (size.x % 64 == 0 && size.y == 64) {
                frameCount = size.x / 64;
            }
            else if (size.x % 32 == 0 && size.y == 64) {
                frameCount = size.x / 32;
            }
            else if (size.x % 32 == 0 && size.y == 32) {
                frameCount = size.x / 32;
            }
            else {
                // Domyślnie 4 klatki
                frameCount = 4;
            }

            frameWidth = size.x / frameCount;
        }

        std::vector<sf::IntRect> frames;
        for (int i = 0; i < frameCount; i++) {
            frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, size.y));
        }

        walkFrames[dir] = frames;

        std::cout << "Loaded walk sprite sheet: " << filename
                  << " for direction: " << static_cast<int>(dir)
                  << " (" << frameCount << " frames)" << std::endl;

        return true;
    }
}

/**
 * @brief Tworzy zastępcze sprite'y (placeholdery)
 *
 * Tworzy kolorowe prostokąty jako zastępcze tekstury dla każdego kierunku
 * i stanu. Używane gdy nie uda się załadować prawdziwych tekstur.
 */
void Player::createPlaceholderSprites()
{
    // Lambda tworząca teksturę placeholder
    auto makeTex = [](sf::Color c, Direction d, bool isWalk) {
        const int frameCount = isWalk ? 4 : 1;
        const int frameWidth = isWalk ? 32 : 32;
        const int frameHeight = 64;

        sf::Image img;
        img.create(frameWidth * frameCount, frameHeight, sf::Color::Transparent);

        for (int frame = 0; frame < frameCount; frame++) {
            sf::Color frameColor = c;
            if (isWalk) {
                if (frame == 1) frameColor = sf::Color(c.r * 0.9, c.g * 0.9, c.b * 0.9);
                if (frame == 2) frameColor = sf::Color(c.r * 0.8, c.g * 0.8, c.b * 0.8);
                if (frame == 3) frameColor = sf::Color(c.r * 0.7, c.g * 0.7, c.b * 0.7);
            }

            int frameOffset = frame * frameWidth;

            // Rysuj prostokątny korpus postaci
            for (int y = 8; y < 24; y++)
                for (int x = 8; x < 24; x++)
                    img.setPixel(frameOffset + x, y, frameColor);

            // Dodaj elementy kierunkowe (głowa/nogi)
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

    // Tworzenie placeholderów dla każdego kierunku
    walkTextures[Direction::UP]    = makeTex(sf::Color::Red,    Direction::UP, true);
    walkTextures[Direction::DOWN]  = makeTex(sf::Color::Green,  Direction::DOWN, true);
    walkTextures[Direction::LEFT]  = makeTex(sf::Color::Blue,   Direction::LEFT, true);
    walkTextures[Direction::RIGHT] = makeTex(sf::Color::Yellow, Direction::RIGHT, true);

    idleTextures[Direction::UP]    = makeTex(sf::Color::Red,    Direction::UP, false);
    idleTextures[Direction::DOWN]  = makeTex(sf::Color::Green,  Direction::DOWN, false);
    idleTextures[Direction::LEFT]  = makeTex(sf::Color::Blue,   Direction::LEFT, false);
    idleTextures[Direction::RIGHT] = makeTex(sf::Color::Yellow, Direction::RIGHT, false);

    // Tworzenie klatek animacji dla placeholderów chodzenia
    for (auto& [dir, tex] : walkTextures) {
        sf::Vector2u size = tex.getSize();
        int frameCount = 4;
        int frameWidth = size.x / frameCount;

        std::vector<sf::IntRect> frames;
        for (int i = 0; i < frameCount; i++) {
            frames.push_back(sf::IntRect(i * frameWidth, 0, frameWidth, size.y));
        }
        walkFrames[dir] = frames;
    }
}

/**
 * @brief Ustawia kierunek patrzenia gracza
 * @param newDirection Nowy kierunek
 *
 * Aktualizuje teksturę zgodnie z nowym kierunkiem.
 */
void Player::setDirection(Direction newDirection)
{
    currentDirection = newDirection;
    updateTextureForState();
}

/**
 * @brief Ustawia stan animacji gracza
 * @param newState Nowy stan (IDLE lub WALKING)
 *
 * Jeśli stan się zmienia, aktualizuje teksturę.
 */
void Player::setState(State newState)
{
    if (currentState != newState) {
        currentState = newState;
        updateTextureForState();
    }
}

/**
 * @brief Aktualizuje teksturę zgodnie z aktualnym stanem i kierunkiem
 *
 * Wybiera odpowiednią teksturę (spoczynku lub chodzenia) dla aktualnego
 * kierunku i ustawia ją na sprite'ie. Dla animacji chodzenia ustawia klatki.
 */
void Player::updateTextureForState()
{
    if (currentState == State::IDLE) {
        // Użyj tekstury spoczynku
        auto it = idleTextures.find(currentDirection);
        if (it != idleTextures.end()) {
            setTexture(it->second);

            AnimatedObject::clear();
            AnimatedObject::addFrame(sf::IntRect(0, 0,
                static_cast<int>(it->second.getSize().x),
                static_cast<int>(it->second.getSize().y)));
            AnimatedObject::reset();
        }
    } else {
        // Użyj tekstury chodzenia z animacją
        auto it = walkTextures.find(currentDirection);
        if (it != walkTextures.end()) {
            setTexture(it->second);

            AnimatedObject::clear();
            auto frameIt = walkFrames.find(currentDirection);
            if (frameIt != walkFrames.end()) {
                for (const auto& frame : frameIt->second) {
                    AnimatedObject::addFrame(frame);
                }
            }
            AnimatedObject::reset();
        }
    }
}

/**
 * @brief Aktualizuje animację gracza
 * @param dt Czas od ostatniej klatki w sekundach
 *
 * Aktualizuje animację tylko jeśli gracz jest w stanie chodzenia.
 */
void Player::animate(float dt)
{
    if (currentState == State::WALKING) {
        AnimatedObject::animate(dt);
    }
}

/**
 * @brief Aktualizuje stan gracza
 *
 * Obsługuje wejście z klawiatury (WSAD), oblicza ruch, sprawdza kolizje
 * i aktualizuje stan animacji. Uwzględnia przejście w stan spoczynku
 * po braku ruchu przez określony czas.
 */
void Player::update()
{
    bool moved = false;
    Direction newDir = currentDirection;
    State newState = State::IDLE;

    sf::Vector2f movement(0.f, 0.f);

    // Obsługa klawiszy WSAD
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= speed;
        newDir = Direction::UP;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += speed;
        newDir = Direction::DOWN;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= speed;
        newDir = Direction::LEFT;
        moved = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += speed;
        newDir = Direction::RIGHT;
        moved = true;
    }

    if (moved) {
        newState = State::WALKING;
        idleTimer = 0.f;  // Resetuj licznik bezruchu
    } else {
        // Zwiększaj licznik bezruchu
        idleTimer += 0.016f;  // ~60 FPS

        if (idleTimer >= idleTimeout) {
            newState = State::IDLE;
        }
    }

    // Normalizacja ruchu po przekątnej
    if (movement.x != 0 && movement.y != 0) {
        movement.x *= 0.7071f;  // √2/2
        movement.y *= 0.7071f;
    }

    // Aktualizuj animację jeśli chodzimy
    if (newState == State::WALKING) {
        AnimatedObject::animate(0.016f);  // Zakładamy 60 FPS
    }

    // Obsługa ruchu i kolizji
    if (moved) {
        sf::Vector2f oldPosition = getPosition();
        sf::Vector2f newPosition = calculateNewPosition(movement);

        // Sprawdź czy nowa pozycja jest poprawna
        if (isPositionValid(newPosition)) {
            setPosition(newPosition.x, newPosition.y);
            lastValidPosition = newPosition;
        } else {
            // Spróbuj przesunąć się tylko w osi X
            sf::Vector2f horizontalPos = calculateNewPosition(sf::Vector2f(movement.x, 0));
            if (isPositionValid(horizontalPos)) {
                setPosition(horizontalPos.x, horizontalPos.y);
                lastValidPosition = horizontalPos;
            } else {
                // Spróbuj przesunąć się tylko w osi Y
                sf::Vector2f verticalPos = calculateNewPosition(sf::Vector2f(0, movement.y));
                if (isPositionValid(verticalPos)) {
                    setPosition(verticalPos.x, verticalPos.y);
                    lastValidPosition = verticalPos;
                } else {
                    // Pozostań na starej pozycji
                    setPosition(oldPosition.x, oldPosition.y);
                }
            }
        }
    }

    // Aktualizuj kierunek jeśli się zmienił
    if (newDir != currentDirection) {
        setDirection(newDir);
    }

    // Aktualizuj stan jeśli się zmienił
    if (newState != currentState) {
        setState(newState);
    }
}

/**
 * @brief Pobiera globalne granice sprite'a gracza
 * @return Prostokąt reprezentujący granice sprite'a
 */
sf::FloatRect Player::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

/**
 * @brief Ustawia granice obszaru, w którym może poruszać się gracz
 * @param newBoundaries Nowy prostokąt graniczny
 */
void Player::setBoundaries(const sf::FloatRect& newBoundaries) {
    boundaries = newBoundaries;
}

/**
 * @brief Sprawdza, czy gracz jest poza dozwolonym obszarem
 * @return true jeśli poza granicami, false w przeciwnym razie
 */
bool Player::isOutOfBounds() const {
    return !checkCollisionWithBounds();
}

/**
 * @brief Przywraca gracza do ostatniej poprawnej pozycji jeśli jest poza granicami
 */
void Player::keepInBounds() {
    if (isOutOfBounds()) {
        setPosition(lastValidPosition.x, lastValidPosition.y);
    }
}

/**
 * @brief Pobiera aktualną pozycję gracza
 * @return Pozycja gracza jako sf::Vector2f
 */
sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

/**
 * @brief Ustawia pozycję gracza
 * @param x Nowa pozycja X
 * @param y Nowa pozycja Y
 */
void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

/**
 * @brief Sprawdza kolizję z granicami obszaru
 * @return true jeśli gracz jest w granicach, false w przeciwnym razie
 */
bool Player::checkCollisionWithBounds() const {
    sf::FloatRect playerBounds = getGlobalBounds();
    return boundaries.contains(playerBounds.left, playerBounds.top) &&
           boundaries.contains(playerBounds.left + playerBounds.width,
                              playerBounds.top + playerBounds.height);
}

/**
 * @brief Przycina pozycję gracza do granic obszaru
 */
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

/**
 * @brief Dodaje prostokątny obszar kolizji
 * @param rect Prostokąt definiujący obszar kolizji
 */
void Player::addCollisionRectangle(const sf::FloatRect& rect) {
    RectangleShape shape;
    shape.rect = rect;
    collisionShapes.push_back(shape);
}

/**
 * @brief Dodaje okrągły obszar kolizji
 * @param center Środek okręgu
 * @param radius Promień okręgu
 */
void Player::addCollisionCircle(const sf::Vector2f& center, float radius) {
    CircleShape shape;
    shape.center = center;
    shape.radius = radius;
    collisionShapes.push_back(shape);
}

/**
 * @brief Dodaje wielokątny obszar kolizji
 * @param points Wierzchołki wielokąta
 */
void Player::addCollisionPolygon(const std::vector<sf::Vector2f>& points) {
    PolygonShape shape;
    shape.points = points;
    collisionShapes.push_back(shape);
}

/**
 * @brief Czyści wszystkie kształty kolizji
 */
void Player::clearCollisionShapes() {
    collisionShapes.clear();
}

/**
 * @brief Sprawdza kolizję z zdefiniowanymi kształtami
 * @return true jeśli występuje kolizja, false w przeciwnym razie
 */
bool Player::checkCollisionWithShapes() const {
    sf::FloatRect playerBounds = getGlobalBounds();
    for (const auto& shape : collisionShapes) {
        if (shapeIntersectsRect(shape, playerBounds)) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Dodaje obiekt kolizji (prostokąt)
 * @param object Prostokąt definiujący obiekt kolizji
 */
void Player::addCollisionObject(const sf::FloatRect& object) {
    addCollisionRectangle(object);
    collisionObjects.push_back(object);
}

/**
 * @brief Czyści wszystkie obiekty kolizji
 */
void Player::clearCollisionObjects() {
    collisionShapes.clear();
    collisionObjects.clear();
}

/**
 * @brief Sprawdza kolizję z obiektami kolizji
 * @return true jeśli występuje kolizja, false w przeciwnym razie
 */
bool Player::checkCollisionWithObjects() const {
    return checkCollisionWithShapes();
}

/**
 * @brief Oblicza nową pozycję na podstawie ruchu
 * @param movement Wektor ruchu
 * @return Nowa pozycja
 */
sf::Vector2f Player::calculateNewPosition(const sf::Vector2f& movement) const {
    sf::Vector2f currentPos = getPosition();
    return sf::Vector2f(currentPos.x + movement.x, currentPos.y + movement.y);
}

/**
 * @brief Sprawdza kolizję między dwoma prostokątami
 * @param rect1 Pierwszy prostokąt
 * @param rect2 Drugi prostokąt
 * @return true jeśli prostokąty się przecinają, false w przeciwnym razie
 */
bool Player::rectangleIntersectsRect(const sf::FloatRect& rect1, const sf::FloatRect& rect2) {
    return rect1.intersects(rect2);
}

/**
 * @brief Sprawdza kolizję między okręgiem a prostokątem
 * @param center Środek okręgu
 * @param radius Promień okręgu
 * @param rect Prostokąt
 * @return true jeśli okrąg i prostokąt się przecinają, false w przeciwnym razie
 */
bool Player::circleIntersectsRect(const sf::Vector2f& center, float radius, const sf::FloatRect& rect) {
    float closestX = std::max(rect.left, std::min(center.x, rect.left + rect.width));
    float closestY = std::max(rect.top, std::min(center.y, rect.top + rect.height));

    float distanceX = center.x - closestX;
    float distanceY = center.y - closestY;

    return (distanceX * distanceX + distanceY * distanceY) <= (radius * radius);
}

/**
 * @brief Sprawdza, czy punkt znajduje się wewnątrz wielokąta
 * @param point Punkt do sprawdzenia
 * @param polygon Wierzchołki wielokąta
 * @return true jeśli punkt jest wewnątrz wielokąta, false w przeciwnym razie
 *
 * Używa algorytmu ray casting (parzystość przecięć).
 */
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

/**
 * @brief Sprawdza kolizję między wielokątem a prostokątem
 * @param polygon Wierzchołki wielokąta
 * @param rect Prostokąt
 * @return true jeśli wielokąt i prostokąt się przecinają, false w przeciwnym razie
 *
 * Sprawdza kilka przypadków:
 * 1. Czy wierzchołki wielokąta są wewnątrz prostokąta
 * 2. Czy wierzchołki prostokąta są wewnątrz wielokąta
 * 3. Czy krawędzie wielokąta przecinają prostokąt
 */
bool Player::polygonIntersectsRect(const std::vector<sf::Vector2f>& polygon, const sf::FloatRect& rect) {
    if (polygon.empty()) return false;

    // Sprawdź czy któryś wierzchołek wielokąta jest wewnątrz prostokąta
    for (const auto& point : polygon) {
        if (rect.contains(point)) {
            return true;
        }
    }

    // Wierzchołki prostokąta
    sf::Vector2f rectPoints[4] = {
        {rect.left, rect.top},
        {rect.left + rect.width, rect.top},
        {rect.left + rect.width, rect.top + rect.height},
        {rect.left, rect.top + rect.height}
    };

    // Sprawdź czy któryś wierzchołek prostokąta jest wewnątrz wielokąta
    for (int i = 0; i < 4; i++) {
        if (pointInPolygon(rectPoints[i], polygon)) {
            return true;
        }
    }

    // Sprawdź przecięcia krawędzi
    for (size_t i = 0; i < polygon.size(); i++) {
        size_t j = (i + 1) % polygon.size();

        sf::Vector2f p1 = polygon[i];
        sf::Vector2f p2 = polygon[j];

        // Sprawdź przecięcie z górną krawędzią prostokąta
        if ((p1.y <= rect.top && p2.y >= rect.top) || (p2.y <= rect.top && p1.y >= rect.top)) {
            float x = p1.x + (rect.top - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            if (x >= rect.left && x <= rect.left + rect.width) {
                return true;
            }
        }

        // Sprawdź przecięcie z dolną krawędzią prostokąta
        if ((p1.y <= rect.top + rect.height && p2.y >= rect.top + rect.height) ||
            (p2.y <= rect.top + rect.height && p1.y >= rect.top + rect.height)) {
            float x = p1.x + (rect.top + rect.height - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            if (x >= rect.left && x <= rect.left + rect.width) {
                return true;
            }
        }

        // Sprawdź przecięcie z lewą krawędzią prostokąta
        if ((p1.x <= rect.left && p2.x >= rect.left) || (p2.x <= rect.left && p1.x >= rect.left)) {
            float y = p1.y + (rect.left - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            if (y >= rect.top && y <= rect.top + rect.height) {
                return true;
            }
        }

        // Sprawdź przecięcie z prawą krawędzią prostokąta
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

/**
 * @brief Sprawdza kolizję między kształtem a prostokątem
 * @param shape Kształt kolizji
 * @param rect Prostokąt
 * @return true jeśli kształt i prostokąt się przecinają, false w przeciwnym razie
 *
 * Używa std::variant do obsługi różnych typów kształtów.
 */
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

/**
 * @brief Sprawdza, czy pozycja jest poprawna (bez kolizji)
 * @param position Pozycja do sprawdzenia
 * @return true jeśli pozycja jest poprawna, false w przeciwnym razie
 *
 * Sprawdza czy pozycja jest w granicach oraz czy nie koliduje z żadnym kształtem.
 */
bool Player::isPositionValid(const sf::Vector2f& position) const {
    sf::FloatRect tempBounds = getGlobalBounds();
    tempBounds.left = position.x;
    tempBounds.top = position.y;

    // Sprawdź granice obszaru
    bool boundsOk = boundaries.contains(tempBounds.left, tempBounds.top) &&
                    boundaries.contains(tempBounds.left + tempBounds.width,
                                       tempBounds.top + tempBounds.height);
    if (!boundsOk)
        return false;

    // Sprawdź kolizje z kształtami
    for (const auto& shape : collisionShapes) {
        if (shapeIntersectsRect(shape, tempBounds)) {
            return false;
        }
    }

    return true;
}