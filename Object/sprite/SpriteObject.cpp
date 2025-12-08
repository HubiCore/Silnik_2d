/**
 * @file SpriteObject.cpp
 * @brief Implementacja klasy SpriteObject
 * @ingroup SpriteObject
 * 
 * Implementacja metod klasy SpriteObject zdefiniowanych w SpriteObject.hpp.
 * Zawiera logikę przypisywania tekstury oraz transformacji i renderowania sprite'a.
 */

#include "SpriteObject.hpp"

/**
 * @brief Konstruktor z teksturą
 * @param tex Referencja do tekstury SFML
 * 
 * Inicjalizuje obiekt sprite'a i natychmiast przypisuje mu podaną teksturę.
 * Wykorzystuje metodę setTexture do ustawienia tekstury.
 */
SpriteObject::SpriteObject(const sf::Texture& tex) {
    setTexture(tex);
}

/**
 * @brief Ustawia teksturę sprite'a
 * @param tex Referencja do tekstury SFML
 * 
 * Przypisuje teksturę do sprite'a. Przechowuje wskaźnik do tekstury,
 * aby zapewnić jej istnienie przez cały czas życia sprite'a.
 * Sprite automatycznie dostosowuje swój rozmiar do rozmiaru tekstury.
 */
void SpriteObject::setTexture(const sf::Texture& tex) {
    texture = &tex;
    sprite.setTexture(*texture);
}

/**
 * @brief Rysuje sprite'a na rendererze
 * @param renderer Referencja do renderera prymitywów
 * 
 * Metoda pobiera wskaźnik do okna docelowego z renderera i rysuje na nim sprite'a.
 * Wymaga, aby renderer miał ustawione okno docelowe (target).
 */
void SpriteObject::draw(PrimitiveRenderer& renderer) {
    renderer.getTarget()->draw(sprite);
}

/**
 * @brief Przesuwa sprite'a o podane wartości
 * @param dx Przesunięcie wzdłuż osi X
 * @param dy Przesunięcie wzdłuż osi Y
 * 
 * Metoda wykorzystuje sf::Sprite::move, który dodaje przesunięcie
 * do aktualnej pozycji sprite'a.
 */
void SpriteObject::translate(float dx, float dy) {
    sprite.move(dx, dy);
}

/**
 * @brief Obraca sprite'a o podany kąt
 * @param angleDeg Kąt obrotu w stopniach
 * 
 * Metoda wykorzystuje sf::Sprite::rotate, który dodaje kąt obrotu
 * do aktualnej rotacji sprite'a. Obrót odbywa się względem punktu
 * odniesienia sprite'a (domyślnie lewy górny róg).
 */
void SpriteObject::rotate(float angleDeg) {
    sprite.rotate(angleDeg);
}

/**
 * @brief Skaluje sprite'a o podany współczynnik
 * @param factor Współczynnik skalowania
 * 
 * Metoda wykorzystuje sf::Sprite::scale, który mnoży aktualną skalę
 * sprite'a przez podany współczynnik. Skalowanie jest jednolite w obu osiach.
 */
void SpriteObject::scale(float factor) {
    sprite.scale(factor, factor);
}