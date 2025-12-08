/**
 * @file SpriteObject.hpp
 * @brief Deklaracja klasy SpriteObject
 * @ingroup SpriteObject
 * 
 * Klasa SpriteObject reprezentuje obiekt sprite'a, który może być rysowany i transformowany.
 * Zawiera sprite SFML z teksturą oraz metody do manipulacji jego właściwościami.
 */

#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "../Renderer/PrimitiveRenderer.hpp"

/**
 * @class SpriteObject
 * @brief Klasa reprezentująca sprite jako obiekt graficzny
 * 
 * Klasa zarządza sprite'em SFML, udostępniając metody do ustawiania tekstury,
 * rysowania oraz przekształceń geometrycznych. Może być dziedziczona w celu
 * rozszerzenia funkcjonalności.
 */
class SpriteObject {
public:
    /**
     * @brief Domyślny konstruktor
     * 
     * Tworzy pusty obiekt sprite'a bez przypisanej tekstury.
     */
    SpriteObject() = default;
    
    /**
     * @brief Konstruktor z teksturą
     * @param tex Referencja do tekstury SFML
     * 
     * Tworzy obiekt sprite'a i przypisuje mu podaną teksturę.
     */
    SpriteObject(const sf::Texture& tex);
    
    /**
     * @brief Wirtualny destruktor
     * 
     * Zapewnia prawidłowe niszczenie obiektów pochodnych.
     */
    virtual ~SpriteObject() = default;

    /**
     * @brief Ustawia teksturę sprite'a
     * @param tex Referencja do tekstury SFML
     * 
     * Przypisuje nową teksturę do sprite'a. Tekstura musi istnieć
     * przez cały czas użycia sprite'a.
     */
    void setTexture(const sf::Texture& tex);
    
    /**
     * @brief Rysuje sprite'a na rendererze
     * @param renderer Referencja do renderera prymitywów
     * 
     * Metoda renderuje sprite'a na oknie docelowym renderera.
     * Wymaga, aby renderer miał ustawione okno docelowe (target).
     */
    void draw(PrimitiveRenderer& renderer);

    /**
     * @brief Przesuwa sprite'a o podane wartości
     * @param dx Przesunięcie wzdłuż osi X
     * @param dy Przesunięcie wzdłuż osi Y
     * 
     * Metoda wykorzystuje sf::Sprite::move do przesunięcia sprite'a.
     */
    void translate(float dx, float dy);
    
    /**
     * @brief Obraca sprite'a o podany kąt
     * @param angleDeg Kąt obrotu w stopniach
     * 
     * Metoda wykorzystuje sf::Sprite::rotate do obrócenia sprite'a.
     * Obrót odbywa się względem aktualnego punktu odniesienia sprite'a.
     */
    void rotate(float angleDeg);
    
    /**
     * @brief Skaluje sprite'a o podany współczynnik
     * @param factor Współczynnik skalowania
     * 
     * Metoda wykorzystuje sf::Sprite::scale do jednolitego skalowania
     * sprite'a w obu osiach (X i Y).
     */
    void scale(float factor);

    /**
     * @brief Pobiera referencję do sprite'a
     * @return Stała referencja do sf::Sprite
     */
    const sf::Sprite& getSprite() const { return sprite; }
    
    /**
     * @brief Zwraca typ obiektu jako string
     * @return Typ obiektu jako std::string
     * 
     * Metoda wirtualna pozwalająca na identyfikację typu obiektu.
     * Może być przesłonięta w klasach pochodnych.
     */
    virtual std::string getType() const { return "SpriteObject"; }
    
    /**
     * @brief Aktualizuje stan obiektu
     * 
     * Metoda wirtualna wywoływana w każdej klatce gry.
     * W podstawowej implementacji nie wykonuje żadnych działań.
     * Może być przesłonięta w klasach pochodnych.
     */
    virtual void update() {}

    /**
     * @brief Ustawia prostokąt tekstury sprite'a
     * @param rect Prostokąt definiujący obszar tekstury
     * 
     * Metoda pozwala na wyświetlenie tylko fragmentu tekstury.
     * Przydatne przy sprite sheetach i animacjach.
     */
    void setTextureRect(const sf::IntRect& rect) { sprite.setTextureRect(rect); }

protected:
    const sf::Texture* texture = nullptr;  ///< Wskaźnik do przypisanej tekstury
    sf::Sprite sprite;                     ///< Obiekt sprite'a SFML
};

#endif