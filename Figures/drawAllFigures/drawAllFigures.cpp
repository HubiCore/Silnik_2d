#include "drawAllFigures.hpp"
#include "../Shapes/Points/Points.hpp"
#include "../Shapes/Lines/Lines.hpp"
#include "../Shapes/Polylines/Polylines.hpp"
#include "../Shapes/Circles/Circles.hpp"
#include "../Shapes/Elipses/Elipses.hpp"
#include "../Shapes/Polygon/Polygons.hpp"
#include "../Shapes/Helpers/Helpers.hpp"

void drawAllFigures(PrimitiveRenderer& renderer, Player& player) {
    // Clear previous hitboxes
    player.clearCollisionObjects();

    // Rysowanie obiektów

    //Punkty
    drawPointWithHitbox(renderer, player, 20, 20, sf::Color::Yellow);
    drawPointWithHitbox(renderer, player, 30, 30, sf::Color::White);
    drawPointWithHitbox(renderer, player, 40, 40, sf::Color::White);

    //Linie
    drawLineWithHitbox(renderer, player, 150, 100, 200, 230, sf::Color::Red);
    drawLineWithHitbox(renderer, player, 400, 100, 550, 200, sf::Color::Cyan);
    drawLineWithHitbox(renderer, player, 0, 599, 800, 599, sf::Color::Blue);


    //Wielokąt
    std::vector<sf::Vector2f> polylinePoints = {
        {300,200}, {400,250}, {350,300}, {100,300}
    };
    drawPolylineWithHitboxes(renderer, player, polylinePoints, true, sf::Color::Cyan, 2.0f);

    //Okręgi
    drawCircleWithHitbox(renderer, player, 600, 200, 40, sf::Color::Green, sf::Color::White);
    drawCircleSymmetricWithHitbox(renderer, player, 600, 200, 60, sf::Color::Red);

    //Elipsa
    drawEllipseWithHitbox(renderer, player, 720, 555, 80, 40, sf::Color::Yellow);

    // Trójkąt równoboczny (wierzchołek na górze)
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(200, 588), -PI/2, sf::Color::Red);
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(240, 588), -PI/2, sf::Color::Red);
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(280, 588), -PI/2, sf::Color::Red);
    drawPolygonWithHitbox(renderer, player, 3, 40, sf::Vector2f(320, 588), -PI/2, sf::Color::Red);

    // ------------------------------------------------------------------------
    // AREA FILLING - visual effect only, no hitboxes
    // ------------------------------------------------------------------------
    //renderer.floodFill0(200, 570, sf::Color(0,255,255,150), sf::Color::Green);

    // Kwadrat obrócony o 45 stopni
    drawPolygonWithHitbox(renderer, player, 4, 40, sf::Vector2f(10, 10), PI/4, sf::Color::Green);
    drawPolygonWithHitbox(renderer, player, 4, 40, sf::Vector2f(30, 30), PI/4, sf::Color::Green);

    // Sześciokąt (wierzchołek w prawo)
    drawPolygonWithHitbox(renderer, player, 6, 60, sf::Vector2f(600, 400), 0, sf::Color::Red);

    // Pięciokąt (wierzchołek na górze)
    drawPolygonWithHitbox(renderer, player, 5, 70, sf::Vector2f(600, 300), -PI/2, sf::Color::Red);



    // ------------------------------------------------------------------------
    // DRAW PLAYER (on top of everything)
    // ------------------------------------------------------------------------
    player.draw(renderer);
}