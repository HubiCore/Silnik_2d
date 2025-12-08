/**
 * @file BitmapHandler.hpp
 * @brief Deklaracja klasy do obsługi obrazów bitmapowych
 * @ingroup BitmapHandler
 * 
 * Zawiera deklarację klasy BitmapHandler z metodami do ładowania, zapisywania,
 * tworzenia i kopiowania obrazów przy użyciu biblioteki SFML.
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class BitmapHandler
 * @brief Klasa do operacji na obrazach bitmapowych
 * 
 * Klasa udostępnia statyczne metody do manipulacji obrazami SFML.
 * Wszystkie metody są statyczne, nie wymaga tworzenia instancji klasy.
 */
class BitmapHandler {
public:
    /**
     * @brief Domyślny konstruktor
     * 
     * Konstruktor jest domyślny, ponieważ wszystkie metody są statyczne.
     */
    BitmapHandler() = default;

    /**
     * @brief Ładuje obraz z pliku
     * @param filename Ścieżka do pliku obrazu
     * @param outImage Referencja do obiektu sf::Image, do którego zostanie załadowany obraz
     * @return true jeśli ładowanie się powiodło, false w przeciwnym razie
     */
    static bool loadImage(const std::string& filename, sf::Image& outImage);

    /**
     * @brief Zapisuje obraz do pliku
     * @param filename Ścieżka do pliku wynikowego
     * @param image Obraz do zapisania
     * @return true jeśli zapis się powiódł, false w przeciwnym razie
     */
    static bool saveImage(const std::string& filename, const sf::Image& image);

    /**
     * @brief Tworzy pusty obraz o podanych wymiarach
     * @param width Szerokość obrazu w pikselach
     * @param height Wysokość obrazu w pikselach
     * @param color Kolor wypełnienia (domyślnie przezroczysty)
     * @return sf::Image Utworzony obraz
     */
    static sf::Image createEmpty(unsigned width, unsigned height, 
                                 sf::Color color = sf::Color::Transparent);

    /**
     * @brief Kopiuje obraz źródłowy do obrazu docelowego
     * @param src Obraz źródłowy
     * @param dst Obraz docelowy (musi być już zainicjalizowany)
     * @param x Pozycja X w obrazie docelowym, gdzie zacznie się kopiowanie
     * @param y Pozycja Y w obrazie docelowym, gdzie zacznie się kopiowanie
     * 
     * Kopiuje cały obraz źródłowy do obrazu docelowego na podanej pozycji.
     * Jeśli obraz docelowy jest za mały, kopia zostanie przycięta.
     */
    static void copy(const sf::Image& src, sf::Image& dst, 
                     unsigned x = 0, unsigned y = 0);
};