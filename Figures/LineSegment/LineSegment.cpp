/**
 * @file LineSegment.cpp
 * @brief Implementacja klasy LineSegment
 * @ingroup LineSegment
 * 
 * Implementacja metod klasy LineSegment zdefiniowanych w LineSegment.hpp.
 * Zawiera logikę transformacji geometrycznych i rysowania odcinka.
 */

#include "LineSegment.hpp"
#include <cmath>

/**
 * @brief Konstruktor klasy LineSegment
 * @param a Pierwszy punkt końcowy odcinka
 * @param b Drugi punkt końcowy odcinka
 * 
 * Inicjalizuje odcinek o podanych punktach końcowych. Domyślny kolor to biały.
 */
LineSegment::LineSegment(const Point2D& a, const Point2D& b)
    : p1(a), p2(b) {}

/**
 * @brief Pobiera pierwszy punkt końcowy odcinka
 * @return Kopia obiektu Point2D reprezentującego punkt p1
 */
Point2D LineSegment::getP1() const { return p1; }

/**
 * @brief Pobiera drugi punkt końcowy odcinka
 * @return Kopia obiektu Point2D reprezentującego punkt p2
 */
Point2D LineSegment::getP2() const { return p2; }

/**
 * @brief Ustawia pierwszy punkt końcowy odcinka
 * @param p Nowy punkt p1
 */
void LineSegment::setP1(const Point2D& p) { p1 = p; }

/**
 * @brief Ustawia drugi punkt końcowy odcinka
 * @param p Nowy punkt p2
 */
void LineSegment::setP2(const Point2D& p) { p2 = p; }

/**
 * @brief Rysuje odcinek na rendererze
 * @param renderer Referencja do renderera prymitywów
 * 
 * Metoda wywołuje renderer.drawLine() z współrzędnymi punktów końcowych i kolorem odcinka.
 */
void LineSegment::draw(PrimitiveRenderer& renderer) {
    renderer.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
}

/**
 * @brief Przesuwa odcinek o podane wartości
 * @param dx Przesunięcie wzdłuż osi X
 * @param dy Przesunięcie wzdłuż osi Y
 * 
 * Przesuwa oba punkty końcowe odcinka o te same wartości dx i dy.
 */
void LineSegment::translate(float dx, float dy) {
    p1.translate(dx, dy);
    p2.translate(dx, dy);
}

/**
 * @brief Obraca odcinek wokół jego środka
 * @param angleDeg Kąt obrotu w stopniach
 * 
 * Metoda wykonuje następujące kroki:
 * 1. Oblicza środek odcinka (cx, cy)
 * 2. Dla każdego punktu końcowego:
 *    - Przesuwa punkt tak, aby środek znalazł się w (0, 0)
 *    - Obraca punkt o podany kąt
 *    - Przesuwa punkt z powrotem
 * 
 * @note Używa macierzy rotacji 2D: [cosθ -sinθ; sinθ cosθ]
 * @note Kąt jest konwertowany ze stopni na radiany
 */
void LineSegment::rotate(float angleDeg) {
    // Oblicz środek odcinka
    float cx = (p1.getX() + p2.getX()) * 0.5f;
    float cy = (p1.getY() + p2.getY()) * 0.5f;

    const float rad = angleDeg * static_cast<float>(M_PI) / 180.f;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    // Lambda funkcja do rotacji punktu względem środka
    auto rotateAroundCenter = [&](Point2D& p) {
        float x = p.getX() - cx;
        float y = p.getY() - cy;
        float nx = x * cosA - y * sinA;
        float ny = x * sinA + y * cosA;
        p.set(nx + cx, ny + cy);
    };

    rotateAroundCenter(p1);
    rotateAroundCenter(p2);
}

/**
 * @brief Skaluje odcinek względem jego środka
 * @param factor Współczynnik skalowania
 * 
 * Metoda wykonuje następujące kroki:
 * 1. Oblicza środek odcinka (cx, cy)
 * 2. Dla każdego punktu końcowego:
 *    - Oblicza wektor od środka do punktu
 *    - Mnoży ten wektor przez współczynnik skalowania
 *    - Ustawia nową pozycję punktu
 * 
 * @note Dla factor = 2.0 odcinek zostanie dwukrotnie wydłużony w obu kierunkach od środka
 * @note Dla factor = 0.5 odcinek zostanie skrócony do połowy
 * @note Dla factor = -1.0 odcinek zostanie odbity względem środka
 */
void LineSegment::scale(float factor) {
    // Oblicz środek odcinka
    float cx = (p1.getX() + p2.getX()) * 0.5f;
    float cy = (p1.getY() + p2.getY()) * 0.5f;

    // Lambda funkcja do skalowania punktu względem środka
    auto scaleAroundCenter = [&](Point2D& p) {
        float nx = cx + (p.getX() - cx) * factor;
        float ny = cy + (p.getY() - cy) * factor;
        p.set(nx, ny);
    };

    scaleAroundCenter(p1);
    scaleAroundCenter(p2);
}