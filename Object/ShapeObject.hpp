/**
* @file ShapeObject.hpp
 * @brief Deklaracja klasy bazowej ShapeObject
 * @ingroup ShapeObject
 *
 * Klasa ShapeObject stanowi interfejs bazowy dla wszystkich kształtów geometrycznych.
 * Łączy funkcjonalności rysowania i transformacji poprzez wirtualne dziedziczenie.
 */

#ifndef SHAPEOBJECT_HPP
#define SHAPEOBJECT_HPP

#include "DrawableObject.hpp"
#include "TransformableObject.hpp"

/**
 * @class ShapeObject
 * @brief Abstrakcyjna klasa bazowa dla obiektów kształtów
 *
 * Klasa łączy interfejsy DrawableObject i TransformableObject poprzez wirtualne dziedziczenie,
 * co umożliwia poprawne działanie mechanizmu diamentowego dziedziczenia w hierarchii obiektów.
 * Wszystkie klasy reprezentujące kształty geometryczne powinny dziedziczyć po tej klasie.
 *
 * @note Klasa używa wirtualnego dziedziczenia, aby uniknąć problemów z wielokrotnym
 *       dziedziczeniem tej samej klasy bazowej w złożonych hierarchiach.
 */
class ShapeObject :
        public virtual DrawableObject,
        public virtual TransformableObject {
public:
    /**
     * @brief Wirtualny destruktor
     *
     * Zapewnia prawidłowe niszczenie obiektów pochodnych.
     * Destruktor jest domyślny i wirtualny.
     */
    virtual ~ShapeObject() = default;

    // Klasa jest czysto interfejsowa - nie dodaje nowych metod,
    // ale łączy istniejące interfejsy przez wielokrotne dziedziczenie.
};

#endif