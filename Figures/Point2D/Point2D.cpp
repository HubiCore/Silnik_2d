/**
 * @file Point2D.cpp
 * @brief Implementacja klasy Point2D
 * @ingroup Point2D
 * 
 * Implementacja metod klasy Point2D zdefiniowanych w Point2D.hpp.
 * Zawiera logikę transformacji geometrycznych i rysowania punktu.
 */

#include "Point2D.hpp"
#include <cmath>

/**
 * @brief Konstruktor klasy Point2D
 * @param x_ Współrzędna X punktu
 * @param y_ Współrzędna Y punktu
 * 
 * Inicjalizuje punkt o podanych współrzędnych. Domyślny kolor to biały.
 */
Point2D::Point2D(float x_, float y_)
    : x(x_), y(y_) {}

/**
 * @brief Pobiera współrzędną X punktu
 * @return Wartość współrzędnej X
 */
float Point2D::getX() const { return x; }

/**
 * @brief Pobiera współrzędną Y punktu
 * @return Wartość współrzędnej Y
 */
float Point2D::getY() const { return y; }

/**
 * @brief Ustawia nowe współrzędne punktu
 * @param newX Nowa wartość współrzędnej X
 * @param newY Nowa wartość współrzędnej Y
 */
void Point2D::set(float newX, float newY) {
    x = newX;
    y = newY;
}

/**
 * @brief Rysuje punkt na rendererze
 * @param renderer Referencja do renderera prymitywów
 * 
 * Metoda wywołuje renderer.drawPoint() z aktualnymi współrzędnymi i kolorem punktu.
 */
void Point2D::draw(PrimitiveRenderer& renderer) {
    renderer.drawPoint(x, y, color);
}

/**
 * @brief Przesuwa punkt o podane wartości
 * @param dx Przesunięcie wzdłuż osi X
 * @param dy Przesunięcie wzdłuż osi Y
 * 
 * Dodaje wartości dx i dy do odpowiednich współrzędnych punktu.
 */
void Point2D::translate(float dx, float dy) {
    x += dx;
    y += dy;
}

/**
 * @brief Obraca punkt względem początku układu współrzędnych
 * @param angleDeg Kąt obrotu w stopniach
 * 
 * Metoda wykonuje obrót punktu używając macierzy rotacji 2D:
 * [x'] = [cosθ -sinθ] [x]
 * [y']   [sinθ  cosθ] [y]
 * 
 * @note Kąt jest konwertowany ze stopni na radiany
 * @note Rotacja odbywa się względem punktu (0, 0), nie względem własnych współrzędnych
 */
void Point2D::rotate(float angleDeg) {
    // Obrót względem punktu (0, 0)
    const float rad = angleDeg * static_cast<float>(M_PI) / 180.f;
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    float nx = x * cosA - y * sinA;
    float ny = x * sinA + y * cosA;

    x = nx;
    y = ny;
}

/**
 * @brief Skaluje punkt względem początku układu współrzędnych
 * @param factor Współczynnik skalowania
 * 
 * Mnoży współrzędne punktu przez współczynnik skalowania.
 * Dla factor = 1.0 punkt pozostaje niezmieniony.
 */
void Point2D::scale(float factor) {
    x *= factor;
    y *= factor;
}