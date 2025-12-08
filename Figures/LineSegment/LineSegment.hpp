/**
 * @file LineSegment.hpp
 * @brief Deklaracja klasy LineSegment - reprezentacja odcinka w 2D
 * @defgroup Shapes Grupa klas kształtów
 * @defgroup LineSegment Klasa odcinka
 * @ingroup Shapes
 * 
 * Klasa reprezentująca odcinek zdefiniowany przez dwa punkty końcowe w przestrzeni 2D.
 * Dziedziczy po ShapeObject, implementując interfejsy do rysowania, aktualizacji i transformacji.
 */

#ifndef LINESEGMENT_HPP
#define LINESEGMENT_HPP

#include "../../Object/ShapeObject.hpp"
#include "../Point2D/Point2D.hpp"
#include "../../Object/Renderer/PrimitiveRenderer.hpp"
#include <SFML/Graphics.hpp>

/**
 * @class LineSegment
 * @brief Klasa reprezentująca odcinek w przestrzeni dwuwymiarowej
 * @ingroup LineSegment
 * 
 * Klasa przechowuje dwa punkty końcowe odcinka (p1 i p2) oraz jego kolor.
 * Udostępnia metody do pobierania i ustawiania punktów końcowych, transformacji
 * (translacja, rotacja wokół środka, skalowanie względem środka) oraz rysowania odcinka.
 * 
 * @note Rotacja i skalowanie odbywają się względem środka odcinka
 * @see ShapeObject, Point2D, DrawableObject, TransformableObject
 */
class LineSegment : public ShapeObject {
public:
    /**
     * @brief Konstruktor klasy LineSegment
     * @param a Pierwszy punkt końcowy odcinka (domyślnie Point2D())
     * @param b Drugi punkt końcowy odcinka (domyślnie Point2D())
     */
    LineSegment(const Point2D& a = Point2D(), const Point2D& b = Point2D());

    /**
     * @brief Pobiera pierwszy punkt końcowy odcinka
     * @return Kopia obiektu Point2D reprezentującego punkt p1
     */
    Point2D getP1() const;

    /**
     * @brief Pobiera drugi punkt końcowy odcinka
     * @return Kopia obiektu Point2D reprezentującego punkt p2
     */
    Point2D getP2() const;

    /**
     * @brief Ustawia pierwszy punkt końcowy odcinka
     * @param p Nowy punkt p1
     */
    void setP1(const Point2D& p);

    /**
     * @brief Ustawia drugi punkt końcowy odcinka
     * @param p Nowy punkt p2
     */
    void setP2(const Point2D& p);

    // Implementacja DrawableObject

    /**
     * @brief Rysuje odcinek na rendererze
     * @param renderer Referencja do renderera prymitywów
     * @override
     */
    void draw(PrimitiveRenderer& renderer) override;

    /**
     * @brief Zwraca typ obiektu jako string
     * @return String "LineSegment"
     * @override
     */
    std::string getType() const override { return "LineSegment"; }

    /**
     * @brief Metoda draw bez parametrów (nieużywana, wymagana przez interfejs)
     * @override
     * @note Metoda musi istnieć ze względu na dziedziczenie, ale używa się draw(PrimitiveRenderer&)
     */
    void draw() override {}

    // Implementacja UpdatableObject

    /**
     * @brief Metoda update (pusta, odcinek nie wymaga aktualizacji)
     * @override
     */
    void update() override {}

    // Implementacja TransformableObject

    /**
     * @brief Przesuwa odcinek o podane wartości
     * @param dx Przesunięcie wzdłuż osi X
     * @param dy Przesunięcie wzdłuż osi Y
     * @override
     */
    void translate(float dx, float dy) override;

    /**
     * @brief Obraca odcinek wokół jego środka
     * @param angleDeg Kąt obrotu w stopniach
     * @override
     * @note Rotacja odbywa się względem środka odcinka, nie względem początku układu współrzędnych
     */
    void rotate(float angleDeg) override;

    /**
     * @brief Skaluje odcinek względem jego środka
     * @param factor Współczynnik skalowania
     * @override
     * @note Dla factor = 1.0 odcinek pozostaje niezmieniony
     * @note Dla factor > 1.0 odcinek jest powiększany
     * @note Dla 0 < factor < 1.0 odcinek jest pomniejszany
     * @note Dla factor < 0 odcinek jest odbity i przeskalowany
     */
    void scale(float factor) override;

    /**
     * @brief Ustawia kolor odcinka
     * @param c Nowy kolor odcinka
     */
    void setColor(const sf::Color& c) { color = c; }

    /**
     * @brief Pobiera kolor odcinka
     * @return Referencja do koloru odcinka
     */
    const sf::Color& getColor() const { return color; }

private:
    Point2D p1;                ///< Pierwszy punkt końcowy odcinka
    Point2D p2;                ///< Drugi punkt końcowy odcinka
    sf::Color color = sf::Color::White; ///< Kolor odcinka (domyślnie biały)
};

#endif // LINESEGMENT_HPP