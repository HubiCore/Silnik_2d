/**
 * @file PrimitiveRenderer.hpp
 * @brief Deklaracja klasy PrimitiveRenderer
 * @ingroup Renderer
 *
 * Klasa PrimitiveRenderer udostępnia metody do rysowania prymitywów graficznych
 * na celu renderowania SFML (RenderTarget). Obsługuje punkty, linie, okręgi,
 * elipsy, wielokąty oraz algorytmy wypełniania.
 */

#ifndef PRIMITIVERENDERER_HPP
#define PRIMITIVERENDERER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

/**
 * @class PrimitiveRenderer
 * @brief Klasa renderera prymitywów graficznych
 *
 * Udostępnia zestaw metod do rysowania podstawowych kształtów geometrycznych
 * z wykorzystaniem algorytmów rastrowych oraz wypełniania obszarów.
 * Wszystkie operacje są wykonywane na przypisanym obiekcie sf::RenderTarget.
 */
class PrimitiveRenderer {
private:
    sf::RenderTarget* target;  ///< Wskaźnik do celu renderowania (okno lub tekstura)

public:
    /**
     * @brief Konstruktor klasy PrimitiveRenderer
     * @param target Wskaźnik do celu renderowania (domyślnie nullptr)
     */
    PrimitiveRenderer(sf::RenderTarget* target = nullptr);

    /**
     * @brief Ustawia cel renderowania
     * @param target Wskaźnik do celu renderowania
     */
    void setTarget(sf::RenderTarget* target);

    /**
     * @brief Pobiera cel renderowania
     * @return Wskaźnik do aktualnego celu renderowania
     */
    sf::RenderTarget* getTarget() { return target; }

    /**
     * @brief Rysuje pojedynczy punkt
     * @param x Współrzędna X punktu
     * @param y Współrzędna Y punktu
     * @param color Kolor punktu
     */
    void drawPoint(float x, float y, sf::Color color);

    /**
     * @brief Rysuje linię (algorytm natywny SFML)
     * @param x1 Współrzędna X początku linii
     * @param y1 Współrzędna Y początku linii
     * @param x2 Współrzędna X końca linii
     * @param y2 Współrzędna Y końca linii
     * @param color Kolor linii
     */
    void drawLine(float x1, float y1, float x2, float y2, sf::Color color);

    /**
     * @brief Rysuje linię algorytmem przyrostowym
     * @param x1 Współrzędna X początku linii
     * @param y1 Współrzędna Y początku linii
     * @param x2 Współrzędna X końca linii
     * @param y2 Współrzędna Y końca linii
     * @param color Kolor linii
     *
     * Algorytm przyrostowy (Digital Differential Analyzer) rysuje linię
     * krok po kroku, obliczając przyrosty współrzędnych.
     */
    void drawLineIncremental(float x1, float y1, float x2, float y2, sf::Color color);

    /**
     * @brief Rysuje łamaną lub wielokąt
     * @param points Wektor punktów definiujących łamaną
     * @param closed Czy łamana ma być zamknięta (wielokąt)
     * @param color Kolor linii
     */
    void drawPolyLine(const std::vector<sf::Vector2f> &points, bool closed, sf::Color color);

    /**
     * @brief Rysuje okrąg (metoda z wykorzystaniem SFML CircleShape)
     * @param x Współrzędna X środka okręgu
     * @param y Współrzędna Y środka okręgu
     * @param radius Promień okręgu
     * @param color Kolor wypełnienia okręgu
     * @param color2 Kolor obramowania okręgu (domyślnie przezroczysty)
     */
    void drawCircle(float x, float y, float radius, sf::Color color, sf::Color color2 = sf::Color::Transparent);

    /**
     * @brief Rysuje okrąg algorytmem symetrycznym (Bresenham)
     * @param x0 Współrzędna X środka okręgu
     * @param y0 Współrzędna Y środka okręgu
     * @param R Promień okręgu
     * @param color Kolor okręgu
     *
     * Algorytm Bresenham'a do rysowania okręgów wykorzystujący symetrię punktów.
     */
    void drawCircleSymmetric(float x0, float y0, float R, sf::Color color);

    /**
     * @brief Rysuje elipsę algorytmem symetrycznym
     * @param x0 Współrzędna X środka elipsy
     * @param y0 Współrzędna Y środka elipsy
     * @param Rx Promień wzdłuż osi X
     * @param Ry Promień wzdłuż osi Y
     * @param color Kolor elipsy
     *
     * Algorytm Midpoint do rysowania elips wykorzystujący symetrię punktów.
     */
    void drawEllipseSymmetric(float x0, float y0, float Rx, float Ry, sf::Color color);

    /**
     * @brief Rysuje wielokąt foremny
     * @param sides Liczba boków wielokąta (minimum 3)
     * @param sideLength Długość boku wielokąta
     * @param center Środek wielokąta
     * @param startAngle Kąt początkowy w radianach
     * @param color Kolor wielokąta
     */
    void drawPolygon(int sides, float sideLength, sf::Vector2f center, float startAngle, sf::Color color);

    /**
     * @brief Wypełnia obszar algorytmem flood fill
     * @param sx Współrzędna X punktu startowego
     * @param sy Współrzędna Y punktu startowego
     * @param fillColor Kolor wypełnienia
     * @param backgroundColor Kolor tła do wypełnienia
     *
     * Algorytm wypełniania obszaru o jednolitym kolorze tła.
     * Wykorzystuje podejście iteracyjne z kolejką.
     */
    void floodFill0(int sx, int sy, sf::Color fillColor, sf::Color backgroundColor);

    /**
     * @brief Wypełnia obszar algorytmem boundary fill
     * @param sx Współrzędna X punktu startowego
     * @param sy Współrzędna Y punktu startowego
     * @param fillColor Kolor wypełnienia
     * @param boundaryColor Kolor granicy obszaru
     *
     * Algorytm wypełniania obszaru ograniczonego granicą o określonym kolorze.
     * Wykorzystuje podejście iteracyjne z kolejką.
     */
    void boundaryFillIterative0(int sx, int sy, sf::Color fillColor, sf::Color boundaryColor);
};

#endif