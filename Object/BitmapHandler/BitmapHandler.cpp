/**
 * @file BitmapHandler.cpp
 * @brief Implementacja klasy do obsługi obrazów bitmapowych
 * @ingroup BitmapHandler
 * 
 * Implementacja metod klasy BitmapHandler zdefiniowanych w BitmapHandler.hpp.
 * Zawiera logikę operacji na obrazach SFML.
 */

#include "../BitmapHandler/BitmapHandler.hpp"

/**
 * @brief Ładuje obraz z pliku
 * @param filename Ścieżka do pliku obrazu
 * @param outImage Referencja do obiektu sf::Image, do którego zostanie załadowany obraz
 * @return true jeśli ładowanie się powiodło, false w przeciwnym razie
 * 
 * Wykorzystuje metodę loadFromFile z biblioteki SFML.
 */
bool BitmapHandler::loadImage(const std::string& filename, sf::Image& outImage) {
    return outImage.loadFromFile(filename);
}

/**
 * @brief Zapisuje obraz do pliku
 * @param filename Ścieżka do pliku wynikowego
 * @param image Obraz do zapisania
 * @return true jeśli zapis się powiódł, false w przeciwnym razie
 */
bool BitmapHandler::saveImage(const std::string& filename, const sf::Image& image) {
    return image.saveToFile(filename);
}

/**
 * @brief Tworzy pusty obraz o podanych wymiarach
 * @param width Szerokość obrazu w pikselach
 * @param height Wysokość obrazu w pikselach
 * @param color Kolor wypełnienia (domyślnie przezroczysty)
 * @return sf::Image Utworzony obraz
 * 
 * Obraz jest tworzony przy użyciu metody create() z SFML.
 * Wszystkie piksele są inicjalizowane podanym kolorem.
 */
sf::Image BitmapHandler::createEmpty(unsigned width, unsigned height, sf::Color color) {
    sf::Image img;
    img.create(width, height, color);
    return img;
}

/**
 * @brief Kopiuje obraz źródłowy do obrazu docelowego
 * @param src Obraz źródłowy
 * @param dst Obraz docelowy (musi być już zainicjalizowany)
 * @param x Pozycja X w obrazie docelowym, gdzie zacznie się kopiowanie
 * @param y Pozycja Y w obrazie docelowym, gdzie zacznie się kopiowanie
 * 
 * Kopiuje cały obszar obrazu źródłowego przy użyciu metody copy() z SFML.
 * Obszar kopiowania obejmuje cały obraz źródłowy.
 * Kopia obejmuje również kanał alfa (przezroczystość).
 */
void BitmapHandler::copy(const sf::Image& src, sf::Image& dst, unsigned x, unsigned y) {
    dst.copy(src, x, y, sf::IntRect(0, 0, src.getSize().x, src.getSize().y), true);
}