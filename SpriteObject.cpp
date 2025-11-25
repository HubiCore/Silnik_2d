#include "SpriteObject.hpp"

SpriteObject::SpriteObject(const sf::Texture& tex) {
    setTexture(tex);
}

void SpriteObject::setTexture(const sf::Texture& tex) {
    texture = tex;
    sprite.setTexture(texture);
}

void SpriteObject::draw(PrimitiveRenderer& renderer) {
    renderer.getTarget()->draw(sprite);
}

void SpriteObject::translate(float dx, float dy) {
    sprite.move(dx, dy);
}

void SpriteObject::rotate(float angleDeg) {
    sprite.rotate(angleDeg);
}

void SpriteObject::scale(float factor) {
    sprite.scale(factor, factor);
}
