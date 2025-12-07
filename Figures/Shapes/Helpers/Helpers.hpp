#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "../../Point2D/Point2D.hpp"
#include "../../LineSegment/LineSegment.hpp"
#include "../../../Object/Renderer/PrimitiveRenderer.hpp"

/**
 * @file Helpers.hpp
 * @brief Plik nagłówkowy zawierający klasy i funkcje pomocnicze do rysowania i obliczeń geometrycznych
 * @ingroup Graphics
 * @ingroup Geometry
 */

/**
 * @defgroup GeometryObliczenia Obliczenia geometryczne
 * @brief Funkcje i klasy związane z obliczeniami geometrycznymi
 */

/**
 * @brief Stała matematyczna π (pi)
 *
 * Wartość przybliżona liczby π używana do obliczeń geometrycznych.
 * @note Wartość: 3.14159265358979323846f
 */
constexpr float PI = 3.14159265358979323846f;

// ============================================================================
// HELPER CLASSES FOR DRAWING - deklaracje pełne
// ============================================================================

/**
 * @class DrawablePoint2D
 * @brief Klasa reprezentująca punkt 2D z możliwością rysowania
 *
 * Rozszerza klasę Point2D o możliwość określenia koloru i rysowania
 * punktu za pomocą renderera prymitywów.
 *
 * @extends Point2D
 * @ingroup Graphics
 */
class DrawablePoint2D : public Point2D {
private:
    sf::Color color; ///< Kolor punktu
public:
    /**
     * @brief Konstruktor klasy DrawablePoint2D
     * @param x Współrzędna X punktu (domyślnie 0)
     * @param y Współrzędna Y punktu (domyślnie 0)
     * @param color Kolor punktu (domyślnie biały)
     */
    DrawablePoint2D(float x = 0, float y = 0, sf::Color color = sf::Color::White);

    /**
     * @brief Ustawia nowy kolor punktu
     * @param newColor Nowy kolor punktu w formacie SFML Color
     */
    void setColor(sf::Color newColor);

    /**
     * @brief Pobiera aktualny kolor punktu
     * @return Aktualny kolor punktu
     */
    sf::Color getColor() const;

    /**
     * @brief Rysuje punkt za pomocą renderera
     * @param renderer Referencja do obiektu renderera prymitywów
     */
    void draw(PrimitiveRenderer& renderer) const;
};

/**
 * @class DrawableLineSegment
 * @brief Klasa reprezentująca odcinek linii z możliwością rysowania
 *
 * Rozszerza klasę LineSegment o możliwość określenia koloru i rysowania
 * odcinka za pomocą renderera prymitywów.
 *
 * @extends LineSegment
 * @ingroup Graphics
 */
class DrawableLineSegment : public LineSegment {
private:
    sf::Color color; ///< Kolor odcinka linii
public:
    /**
     * @brief Konstruktor klasy DrawableLineSegment
     * @param p1 Punkt początkowy odcinka
     * @param p2 Punkt końcowy odcinka
     * @param color Kolor odcinka (domyślnie biały)
     */
    DrawableLineSegment(const Point2D& p1, const Point2D& p2, sf::Color color = sf::Color::White);

    /**
     * @brief Ustawia nowy kolor odcinka
     * @param newColor Nowy kolor odcinka w formacie SFML Color
     */
    void setColor(sf::Color newColor);

    /**
     * @brief Pobiera aktualny kolor odcinka
     * @return Aktualny kolor odcinka
     */
    sf::Color getColor() const;

    /**
     * @brief Rysuje odcinek za pomocą renderera
     * @param renderer Referencja do obiektu renderera prymitywów
     */
    void draw(PrimitiveRenderer& renderer) const;
};

// ============================================================================
// HELPER FUNCTIONS
// ============================================================================

/**
 * @brief Oblicza punkty wierzchołków wielokąta foremnego
 *
 * Funkcja generuje współrzędne wierzchołków wielokąta foremnego o podanej
 * liczbie boków i promieniu, zaczynając od określonego kąta.
 *
 * @param sides Liczba boków wielokąta (minimum 3)
 * @param radius Promień opisany na wielokącie (odległość od środka do wierzchołka)
 * @param center Punkt centralny wielokąta
 * @param startAngle Kąt początkowy w radianach (domyślnie 0)
 * @return Wektor punktów wierzchołków wielokąta
 *
 * @throw Niejawnie: Zwraca pusty wektor dla sides < 3
 * @note Dla sides = 4 tworzy kwadrat, dla sides = 6 tworzy sześciokąt foremny
 *
 * @code
 * // Tworzenie pięciokąta foremnego o promieniu 50
 * auto points = calculatePolygonPoints(5, 50.0f, sf::Vector2f(100, 100));
 * @endcode
 */
std::vector<sf::Vector2f> calculatePolygonPoints(int sides, float radius, sf::Vector2f center, float startAngle = 0);

/**
 * @brief Tworzy hitbox (obszar kolizji) dla linii o określonej grubości
 *
 * Funkcja generuje wierzchołki prostokąta reprezentującego obszar kolizji
 * dla linii o zadanej grubości. Użyteczne do wykrywania kolizji z cienkimi
 * obiektami.
 *
 * @param x1 Współrzędna X punktu początkowego linii
 * @param y1 Współrzędna Y punktu początkowego linii
 * @param x2 Współrzędna X punktu końcowego linii
 * @param y2 Współrzędna Y punktu końcowego linii
 * @param thickness Grubość linii (domyślnie 2.0f)
 * @return Wektor 4 punktów tworzących prostokątny hitbox
 *
 * @note W przypadku bardzo krótkich linii (< 0.001f) tworzy kwadratowy hitbox
 * @warning Długość linii obliczana jest za pomocą pierwiastka kwadratowego
 *
 * @see calculatePolygonPoints()
 */
std::vector<sf::Vector2f> createLineHitbox(float x1, float y1, float x2, float y2, float thickness = 2.0f);

#endif // HELPERS_HPP