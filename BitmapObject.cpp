#include "BitmapObject.hpp"

BitmapObject::BitmapObject(const std::string& path) {
    loadFromFile(path);
}

bool BitmapObject::loadFromFile(const std::string& path) {
    if (!image.loadFromFile(path))
        return false;

    texture.loadFromImage(image);
    sprite.setTexture(texture);
    return true;
}

void BitmapObject::draw(PrimitiveRenderer& renderer) {
    renderer.getTarget()->draw(sprite);
}

void BitmapObject::translate(float dx, float dy) {
    sprite.move(dx, dy);
}

void BitmapObject::rotate(float angleDeg) {
    sprite.rotate(angleDeg);
}

void BitmapObject::scale(float factor) {
    sprite.scale(factor, factor);
}
