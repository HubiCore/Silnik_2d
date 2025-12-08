/**
 * @file BitmapObject.cpp
 * @brief Implementacja klasy BitmapObject
 * @ingroup BitmapObject
 * 
 * Implementacja metod klasy BitmapObject zdefiniowanych w BitmapObject.hpp.
 * Zawiera logikę ładowania obrazów oraz transformacji i renderowania sprite'a.
 */

#include "../BitmapObject/BitmapObject.hpp"

/**
 * @brief Konstruktor z ładowaniem obrazu
 * @param path Ścieżka do pliku obrazu
 * 
 * Tworzy obiekt bitmapowy i natychmiast ładuje obraz z podanej ścieżki.
 * Jeśli ładowanie się nie powiedzie, obiekt pozostaje pusty.
 */
BitmapObject::BitmapObject(const std::string& path) {
    loadFromFile(path);
}

/**
 * @brief Ładuje obraz z pliku
 * @param path Ścieżka do pliku obrazu
 * @return true jeśli ładowanie się powiodło, false w przeciwnym razie
 * 
 * Metoda próbuje załadować obraz przez sf::Image::loadFromFile.
 * Jeśli się uda, tworzy teksturę z obrazu i przypisuje ją do sprite'a.
 * W przeciwnym razie zwraca false.
 */
bool BitmapObject::loadFromFile(const std::string& path) {
    if (!image.loadFromFile(path))
        return false;

    texture.loadFromImage(image);
    sprite.setTexture(texture);
    return true;
}

/**
 * @brief Rysuje bitmapę na rendererze
 * @param renderer Referencja do renderera prymitywów
 * 
 * Metoda pobiera wskaźnik do okna docelowego z renderera i rysuje na nim sprite'a.
 * Wymaga, aby renderer miał ustawione okno docelowe (target).
 */
void BitmapObject::draw(PrimitiveRenderer& renderer) {
    renderer.getTarget()->draw(sprite);
}

/**
 * @brief Przesuwa bitmapę o podane wartości
 * @param dx Przesunięcie wzdłuż osi X
 * @param dy Przesunięcie wzdłuż osi Y
 * 
 * Metoda wykorzystuje sf::Sprite::move, który dodaje przesunięcie do aktualnej pozycji sprite'a.
 */
void BitmapObject::translate(float dx, float dy) {
    sprite.move(dx, dy);
}

/**
 * @brief Obraca bitmapę o podany kąt
 * @param angleDeg Kąt obrotu w stopniach
 * 
 * Metoda wykorzystuje sf::Sprite::rotate, który dodaje kąt obrotu do aktualnej rotacji sprite'a.
 * Obrót odbywa się względem punktu odniesienia sprite'a (domyślnie lewy górny róg).
 */
void BitmapObject::rotate(float angleDeg) {
    sprite.rotate(angleDeg);
}

/**
 * @brief Skaluje bitmapę o podany współczynnik
 * @param factor Współczynnik skalowania
 * 
 * Metoda wykorzystuje sf::Sprite::scale, który mnoży aktualną skalę sprite'a przez podany współczynnik.
 * Skalowanie jest jednolite w obu osiach (X i Y).
 */
void BitmapObject::scale(float factor) {
    sprite.scale(factor, factor);
}