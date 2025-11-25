#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class BitmapHandler {
public:
    BitmapHandler() = default;

    /// Wczytuje bitmapę z pliku
    static bool loadImage(const std::string& filename, sf::Image& outImage);

    /// Zapisuje bitmapę do pliku
    static bool saveImage(const std::string& filename, const sf::Image& image);

    /// Tworzy pustą bitmapę o danym rozmiarze
    static sf::Image createEmpty(unsigned width, unsigned height, sf::Color color = sf::Color::Transparent);

    /// Kopiuje zawartość obrazu src do dst
    static void copy(const sf::Image& src, sf::Image& dst, unsigned x = 0, unsigned y = 0);
};
