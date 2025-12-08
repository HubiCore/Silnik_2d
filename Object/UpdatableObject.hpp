/**
* @file UpdatableObject.hpp
 * @brief Deklaracja klasy UpdatableObject
 * @ingroup UpdatableObject
 *
 * Klasa UpdatableObject definiuje interfejs dla obiektów, których stan może być aktualizowany w czasie.
 * Rozszerza klasę GameObject o możliwość aktualizacji z uwzględnieniem czasu.
 */

#ifndef UPDATABLEOBJECT_HPP
#define UPDATABLEOBJECT_HPP

#include "GameObject/GameObjects.hpp"

/**
 * @class UpdatableObject
 * @brief Abstrakcyjna klasa bazowa dla obiektów aktualizowalnych w czasie
 *
 * Klasa rozszerza interfejs GameObject o możliwość aktualizacji stanu obiektu
 * w każdej klatce gry z uwzględnieniem czasu, który upłynął od poprzedniej aktualizacji.
 * Wykorzystuje wirtualne dziedziczenie, aby umożliwić poprawne wielokrotne dziedziczenie.
 */
class UpdatableObject : public virtual GameObject {
public:
    /**
     * @brief Aktualizuje stan obiektu
     * @param deltaTime Czas, który upłynął od ostatniej aktualizacji (w sekundach)
     *
     * Metoda czysto wirtualna, która musi być zaimplementowana przez klasy pochodne.
     * Odpowiada za aktualizację stanu obiektu, taką jak ruch, animacje, logika gry itp.
     */
    virtual void update(float deltaTime) = 0;
};

#endif