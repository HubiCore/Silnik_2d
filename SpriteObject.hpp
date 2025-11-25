#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include "DrawableObject.hpp"
#include "TransformableObject.hpp"
#include <SFML/Graphics.hpp>

class SpriteObject : public DrawableObject, public TransformableObject {
protected:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    SpriteObject() = default;
    explicit SpriteObject(const sf::Texture& tex);

    std::string getType() const override { return "SpriteObject"; }

    void update() override {}
    void draw() override {}

    void draw(PrimitiveRenderer& renderer) override;

    // Transformable
    void translate(float dx, float dy) override;
    void rotate(float angleDeg) override;
    void scale(float factor) override;

    // Helpers
    void setTexture(const sf::Texture& tex);
    const sf::Sprite& getSprite() const { return sprite; }
    sf::Sprite& getSprite() { return sprite; }
};

#endif
