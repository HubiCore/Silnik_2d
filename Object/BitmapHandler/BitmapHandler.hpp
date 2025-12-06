#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class BitmapHandler {
public:
    BitmapHandler() = default;


    static bool loadImage(const std::string& filename, sf::Image& outImage);


    static bool saveImage(const std::string& filename, const sf::Image& image);


    static sf::Image createEmpty(unsigned width, unsigned height, sf::Color color = sf::Color::Transparent);


    static void copy(const sf::Image& src, sf::Image& dst, unsigned x = 0, unsigned y = 0);
};
