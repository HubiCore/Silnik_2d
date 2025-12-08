/**
 * @file drawAllFigures.cpp
 * @brief Implementacja głównej funkcji rysującej wszystkie figury
 * @ingroup MainDrawing
 *
 * Implementacja funkcji drawAllFigures zdefiniowanej w drawAllFigures.hpp.
 * Zawiera kompletny kod do renderowania wszystkich kształtów w scenie gry.
 */

#include "drawAllFigures.hpp"
#include "../Shapes/Points/Points.hpp"
#include "../Shapes/Lines/Lines.hpp"
#include "../Shapes/Polylines/Polylines.hpp"
#include "../Shapes/Circles/Circles.hpp"
#include "../Shapes/Elipses/Elipses.hpp"
#include "../Shapes/Polygon/Polygons.hpp"
#include "../Shapes/Helpers/Helpers.hpp"

// Definicja stałej PI użytej w kodzie
#ifndef PI
#define PI 3.14159265358979323846f
#endif

/**
 * @brief Implementacja głównej funkcji rysującej
 * @ingroup MainDrawing
 *
 * Funkcja realizuje następującą sekwencję rysowania:
 *
 * 1. **Inicjalizacja**: Czyszczenie istniejących hitboxów gracza
 * 2. **Punkty**: Rysowanie trzech punktów z hitboxami (żółty i dwa białe)
 * 3. **Linie**: Rysowanie trzech linii z hitboxami (czerwona, cyjanowa, niebieska)
 * 4. **Polilinie**:
 *    - Zamknięty czterobok (niebiesko-zielony) z hitboxami
 *    - Zamknięty czworobok (szary) z hitboxami z wypełnieniem
 *    - Waza (żółta) bez hitboxów z wypełnieniem
 * 5. **Koła**:
 *    - Zielone koło z białym obrysem i hitboxem
 *    - Czerwony okrąg z hitboxem (rysowany algorytmem symetrycznym)
 * 6. **Elipsa**: Żółta elipsa z hitboxem
 * 7. **Wielokąty foremne**:
 *    - Cztery czerwone trójkąty równoboczne (wierzchołek u góry)
 *    - Dwa zielone kwadraty obrócone o 45°
 *    - Czerwony sześciokąt (wierzchołek w prawo)
 *    - Czerwony pięciokąt (wierzchołek u góry)
 * 8. **Gracz**: Rysowanie gracza na wierzchu wszystkich elementów
 *
 * @param renderer Referencja do renderera prymitywów
 * @param player Referencja do obiektu gracza
 *
 * @section coordinate_system System współrzędnych
 * - Początek układu (0, 0) w lewym górnym rogu
 * - Oś X rośnie w prawo
 * - Oś Y rośnie w dół
 * - Rozdzielczość zakładana: 800x600 pikseli
 *
 * @section collision_system System kolizji
 * - Hitboxy są dodawane tylko dla obiektów interaktywnych
 * - Elementy dekoracyjne (np. waza) nie mają hitboxów
 * - Gracz może kolidować z: punktami, liniami, poliliniami, kołami, elipsami, wielokątami
 *
 * @section rendering_order Kolejność renderowania
 * 1. Tło i elementy dekoracyjne
 * 2. Obiekty statyczne z kolizjami
 * 3. Wypełnienia kolorem (flood fill)
 * 4. Gracz (na wierzchu)
 *
 * @note Stała PI jest używana do określania kątów w radianach
 * @note Funkcja floodFill0 jest używana do wypełniania zamkniętych obszarów
 * @see player.clearCollisionObjects(), renderer.floodFill0()
 */
void drawAllFigures(PrimitiveRenderer& renderer, Player& player) {
    // Czyszczenie poprzednich hitboxów
    player.clearCollisionObjects();

    // ------------------------------------------------------------
    // RYSOWANIE PUNKTÓW
    // ------------------------------------------------------------
    drawPointWithHitbox(renderer, player, 20, 20, sf::Color::Yellow);
    drawPointWithHitbox(renderer, player, 30, 30, sf::Color::White);
    drawPointWithHitbox(renderer, player, 40, 40, sf::Color::White);

    // ------------------------------------------------------------
    // RYSOWANIE LINII
    // ------------------------------------------------------------
    drawLineWithHitbox(renderer, player, 150, 100, 200, 230, sf::Color::Red);
    drawLineWithHitbox(renderer, player, 400, 100, 550, 200, sf::Color::Cyan);
    drawLineWithHitbox(renderer, player, 0, 599, 800, 599, sf::Color::Blue);

    // ------------------------------------------------------------
    // RYSOWANIE POLILINII
    // ------------------------------------------------------------

    // Wielokąt z hitboxami (niebiesko-zielony czterobok)
    std::vector<sf::Vector2f> polylinePoints = {
        {300, 200}, {400, 250}, {350, 300}, {100, 300}
    };
    drawPolylineWithHitboxes(renderer, player, polylinePoints, true, sf::Color::Cyan, 2.0f);

    // Wielokąt z hitboxami (szary czworobok z wypełnieniem)
    std::vector<sf::Vector2f> polylinePoints2 = {
        {400, 598}, {500, 598}, {425, 550}, {475, 550}
    };
    drawPolylineWithHitboxes(renderer, player, polylinePoints2, true, sf::Color(200, 200, 200), 2.0f);

    // Wypełnianie dwóch części kolorem
    renderer.floodFill0(402, 597, sf::Color(150, 150, 150), sf::Color(50, 50, 50));
    renderer.floodFill0(446, 556, sf::Color(150, 150, 150), sf::Color(50, 50, 50));

    // Wielokąt jako waza bez hitboxów (żółta dekoracja)
    std::vector<sf::Vector2f> polylinePoints3 = {
        // Podstawa
        {445, 549}, {455, 549},
        // Prawa strona
        {457, 544}, {460, 540}, {458, 538}, {458, 535},
        {460, 533}, {452, 530},
        // Lewa strona
        {448, 530}, {440, 533}, {442, 535}, {441, 538},
        {440, 540}, {443, 544}
    };
    drawPolylineWithoutHitboxes(renderer, player, polylinePoints3, true, sf::Color::Yellow, 2.0f);

    // Wypełnianie wazy kolorem
    renderer.floodFill0(447, 548, sf::Color::Yellow, sf::Color(50, 50, 50));

    // ------------------------------------------------------------
    // RYSOWANIE KÓŁ
    // ------------------------------------------------------------
    drawCircleWithHitbox(renderer, player, 600, 200, 40, sf::Color::Green, sf::Color::White);
    drawCircleSymmetricWithHitbox(renderer, player, 600, 200, 60, sf::Color::Red);

    // ------------------------------------------------------------
    // RYSOWANIE ELIPSY
    // ------------------------------------------------------------
    drawEllipseWithHitbox(renderer, player, 720, 555, 80, 40, sf::Color::Yellow);

    // ------------------------------------------------------------
    // RYSOWANIE WIELOKĄTÓW FOREMNYCH
    // ------------------------------------------------------------

    // Trójkąty równoboczne (wierzchołek na górze)
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(200, 588), -PI/2, sf::Color::Red);
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(240, 588), -PI/2, sf::Color::Red);
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(280, 588), -PI/2, sf::Color::Red);
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(320, 588), -PI/2, sf::Color::Red);

    // ------------------------------------------------------------
    // WYPEŁNIANIE OBSZARÓW (tylko efekt wizualny, bez hitboxów)
    // ------------------------------------------------------------
    // renderer.floodFill0(200, 570, sf::Color(0, 255, 255, 150), sf::Color::Green);

    // Kwadraty obrócone o 45 stopni
    drawPolygonWithHitbox(renderer, player, 4, 40, sf::Vector2f(10, 10), PI/4, sf::Color::Green);
    drawPolygonWithHitbox(renderer, player, 4, 40, sf::Vector2f(30, 30), PI/4, sf::Color::Green);

    // Sześciokąt (wierzchołek w prawo)
    drawPolygonWithHitbox(renderer, player, 6, 60, sf::Vector2f(600, 400), 0, sf::Color::Red);

    // Pięciokąt (wierzchołek na górze)
    drawPolygonWithHitbox(renderer, player, 5, 70, sf::Vector2f(600, 300), -PI/2, sf::Color::Red);

    // ------------------------------------------------------------
    // RYSOWANIE GRACZA (na wierzchu wszystkiego)
    // ------------------------------------------------------------
    player.draw(renderer);
}