/**
* @file DrawableObject.hpp
 * @brief Deklaracja klasy DrawableObject
 * @ingroup DrawableObject
 *
 * Klasa DrawableObject definiuje interfejs dla obiektów, które mogą być rysowane.
 * Rozszerza klasę GameObject o możliwość renderowania przez PrimitiveRenderer.
 */

#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include "GameObject/GameObjects.hpp"
#include "Renderer/PrimitiveRenderer.hpp"

/**
 * @class DrawableObject
 * @brief Abstrakcyjna klasa bazowa dla obiektów rysowalnych
 *
 * Klasa rozszerza interfejs GameObject o możliwość renderowania na ekranie.
 * Każdy obiekt, który ma być wyświetlany, powinien implementować ten interfejs.
 * Wykorzystuje wirtualne dziedziczenie, aby umożliwić poprawne wielokrotne dziedziczenie.
 */
class DrawableObject : public virtual GameObject {
public:
    /**
     * @brief Rysuje obiekt na rendererze
     * @param renderer Referencja do renderera prymitywów
     *
     * Metoda czysto wirtualna, która musi być zaimplementowana przez klasy pochodne.
     * Odpowiada za renderowanie obiektu na ekranie przy użyciu dostarczonego renderera.
     */
    virtual void draw(PrimitiveRenderer& renderer) = 0;
};

#endif



