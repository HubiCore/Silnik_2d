/**
 * @file Point2D.hpp
 * @brief Deklaracja klasy Point2D - reprezentacja punktu 2D
 * @defgroup Shapes Grupa klas kształtów
 * @defgroup Point2D Klasa punktu 2D
 * @ingroup Shapes
 * 
 * Klasa reprezentująca punkt w przestrzeni 2D z możliwością transformacji i rysowania.
 * Dziedziczy po ShapeObject, implementując interfejsy DrawableObject, UpdatableObject i TransformableObject.
 */

#ifndef POINT2D_HPP
#define POINT2D_HPP

#include "../../Object/ShapeObject.hpp"
#include "../../Object/Renderer/PrimitiveRenderer.hpp"
#include <SFML/Graphics.hpp>

/**
 * @class Point2D
 * @brief Klasa reprezentująca punkt w przestrzeni dwuwymiarowej
 * @ingroup Point2D
 * 
 * Klasa przechowuje współrzędne punktu (x, y) oraz jego kolor. Udostępnia metody
 * do pobierania i ustawiania współrzędnych, transformacji (translacja, rotacja, skalowanie)
 * oraz rysowania punktu na rendererze.
 * 
 * @note Rotacja punktu odbywa się względem punktu (0, 0)
 * @see ShapeObject, DrawableObject, TransformableObject
 */
class Point2D : public ShapeObject {
public:
    /**
     * @brief Konstruktor klasy Point2D
     * @param x Współrzędna X punktu (domyślnie 0.0)
     * @param y Współrzędna Y punktu (domyślnie 0.0)
     */
    Point2D(float x = 0.f, float y = 0.f);

    /**
     * @brief Pobiera współrzędną X punktu
     * @return Wartość współrzędnej X
     */
    float getX() const;

    /**
     * @brief Pobiera współrzędną Y punktu
     * @return Wartość współrzędnej Y
     */
    float getY() const;

    /**
     * @brief Ustawia nowe współrzędne punktu
     * @param newX Nowa wartość współrzędnej X
     * @param newY Nowa wartość współrzędnej Y
     */
    void set(float newX, float newY);

    // Implementacja DrawableObject

    /**
     * @brief Rysuje punkt na rendererze
     * @param renderer Referencja do renderera prymitywów
     * @override
     */
    void draw(PrimitiveRenderer& renderer) override;

    /**
     * @brief Zwraca typ obiektu jako string
     * @return String "Point2D"
     * @override
     */
    std::string getType() const override { return "Point2D"; }

    /**
     * @brief Metoda draw bez parametrów (nieużywana, wymagana przez interfejs)
     * @note Metoda musi istnieć ze względu na dziedziczenie, ale używa się draw(PrimitiveRenderer&)
     * @override
     */
    void draw() override {}

    // Implementacja UpdatableObject

    /**
     * @brief Metoda update (pusta, punkt nie wymaga aktualizacji)
     * @override
     */
    void update() override {}

    // Implementacja TransformableObject

    /**
     * @brief Przesuwa punkt o podane wartości
     * @param dx Przesunięcie wzdłuż osi X
     * @param dy Przesunięcie wzdłuż osi Y
     * @override
     */
    void translate(float dx, float dy) override;

    /**
     * @brief Obraca punkt względem początku układu współrzędnych (0, 0)
     * @param angleDeg Kąt obrotu w stopniach
     * @override
     * @note Rotacja odbywa się względem punktu (0, 0), nie względem własnego środka
     */
    void rotate(float angleDeg) override;

    /**
     * @brief Skaluje punkt względem początku układu współrzędnych
     * @param factor Współczynnik skalowania
     * @override
     * @note Dla factor = 1.0 punkt pozostaje niezmieniony
     * @note Dla factor = 2.0 punkt oddala się dwukrotnie od początku układu
     * @note Dla factor = 0.5 punkt przybliża się dwukrotnie do początku układu
     */
    void scale(float factor) override;

    /**
     * @brief Ustawia kolor punktu
     * @param c Nowy kolor punktu
     */
    void setColor(const sf::Color& c) { color = c; }

    /**
     * @brief Pobiera kolor punktu
     * @return Referencja do koloru punktu
     */
    const sf::Color& getColor() const { return color; }

private:
    float x;                ///< Współrzędna X punktu
    float y;                ///< Współrzędna Y punktu
    sf::Color color = sf::Color::White; ///< Kolor punktu (domyślnie biały)
};

#endif // POINT2D_HPP