/**
* @file GameObjects.hpp
 * @brief Deklaracja klasy bazowej GameObject
 * @ingroup GameObject
 *
 * Definiuje interfejs bazowy dla wszystkich obiektów w systemie.
 * Klasa GameObject stanowi podstawę hierarchii obiektów gry.
 */

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

/**
 * @class GameObject
 * @brief Abstrakcyjna klasa bazowa dla wszystkich obiektów w systemie
 *
 * Klasa definiuje interfejs, który musi implementować każdy obiekt w systemie.
 * Zapewnia mechanizm identyfikacji typu oraz cyklu życia obiektu (aktualizacja i rysowanie).
 * Wszystkie metody są czysto wirtualne, co czyni klasę abstrakcyjną.
 */
class GameObject {
public:
    /**
     * @brief Wirtualny destruktor
     *
     * Zapewnia prawidłowe niszczenie obiektów pochodnych.
     * Destruktor jest domyślny i wirtualny.
     */
    virtual ~GameObject() = default;

    /**
     * @brief Zwraca typ obiektu jako string
     * @return Typ obiektu jako std::string
     *
     * Metoda pozwala na identyfikację typu obiektu w czasie wykonania.
     * Każda klasa pochodna powinna zwracać unikalny identyfikator.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Aktualizuje stan obiektu
     *
     * Metoda wywoływana w każdej klatce gry w celu aktualizacji stanu obiektu.
     * Implementuje logikę związaną z czasem, interakcjami, fizyką itp.
     */
    virtual void update() = 0;

    /**
     * @brief Rysuje obiekt na ekranie
     *
     * Metoda wywoływana w każdej klatce gry w celu wizualizacji obiektu.
     * Implementuje logikę renderowania obiektu na ekranie.
     */
    virtual void draw() = 0;
};

#endif