/**
 * @file TransformableObject.hpp
 * @brief Deklaracja klasy TransformableObject
 * @ingroup TransformableObject
 * 
 * Klasa TransformableObject definiuje interfejs dla obiektów, które mogą być przekształcane geometrycznie.
 * Rozszerza klasę GameObject o podstawowe transformacje: przesunięcie, obrót i skalowanie.
 */

#ifndef TRANSFORMABLEOBJECT_HPP
#define TRANSFORMABLEOBJECT_HPP

#include "GameObject/GameObjects.hpp"

/**
 * @class TransformableObject
 * @brief Abstrakcyjna klasa bazowa dla obiektów transformowalnych
 * 
 * Klasa rozszerza interfejs GameObject o możliwość przekształceń geometrycznych.
 * Definiuje trzy podstawowe operacje transformacji, które są wspólne dla wielu obiektów graficznych.
 * Wykorzystuje wirtualne dziedziczenie, aby umożliwić poprawne wielokrotne dziedziczenie.
 */
class TransformableObject : public virtual GameObject {
public:
    /**
     * @brief Przesuwa obiekt o podane wartości
     * @param dx Przesunięcie wzdłuż osi X
     * @param dy Przesunięcie wzdłuż osi Y
     * 
     * Metoda czysto wirtualna, która musi być zaimplementowana przez klasy pochodne.
     * Odpowiada za przesunięcie obiektu w przestrzeni 2D.
     */
    virtual void translate(float dx, float dy) = 0;
    
    /**
     * @brief Obraca obiekt o podany kąt
     * @param angleDeg Kąt obrotu w stopniach
     * 
     * Metoda czysto wirtualna, która musi być zaimplementowana przez klasy pochodne.
     * Odpowiada za obrót obiektu względem jego punktu odniesienia.
     */
    virtual void rotate(float angleDeg) = 0;
    
    /**
     * @brief Skaluje obiekt o podany współczynnik
     * @param factor Współczynnik skalowania
     * 
     * Metoda czysto wirtualna, która musi być zaimplementowana przez klasy pochodne.
     * Odpowiada za skalowanie obiektu w obu osiach (jednolite skalowanie).
     */
    virtual void scale(float factor) = 0;
};

#endif