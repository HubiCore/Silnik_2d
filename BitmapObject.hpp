#ifndef BITMAPOBJECT_HPP
#define BITMAPOBJECT_HPP

#include "DrawableObject.hpp"
#include "TransformableObject.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class BitmapObject : public DrawableObject, public TransformableObject {
private:
    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    BitmapObject() = default;
    explicit BitmapObject(const std::string& path);

    std::string getType() const override { return "BitmapObject"; }

    void update() override {}
    void draw() override {}

    void draw(PrimitiveRenderer& renderer) override;

    // TransformableObject
    void translate(float dx, float dy) override;
    void rotate(float angleDeg) override;
    void scale(float factor) override;

    // Own
    bool loadFromFile(const std::string& path);
};

#endif
