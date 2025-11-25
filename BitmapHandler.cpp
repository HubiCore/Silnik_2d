#include "BitmapHandler.hpp"

bool BitmapHandler::loadImage(const std::string& filename, sf::Image& outImage) {
    return outImage.loadFromFile(filename);
}

bool BitmapHandler::saveImage(const std::string& filename, const sf::Image& image) {
    return image.saveToFile(filename);
}

sf::Image BitmapHandler::createEmpty(unsigned width, unsigned height, sf::Color color) {
    sf::Image img;
    img.create(width, height, color);
    return img;
}

void BitmapHandler::copy(const sf::Image& src, sf::Image& dst, unsigned x, unsigned y) {
    dst.copy(src, x, y, sf::IntRect(0, 0, src.getSize().x, src.getSize().y), true);
}
