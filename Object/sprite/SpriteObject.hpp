#ifndef SPRITEOBJECT_HPP
#define SPRITEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include "../Renderer/PrimitiveRenderer.hpp"

class SpriteObject {
public:
    SpriteObject() = default;
    SpriteObject(const sf::Texture& tex);
    virtual ~SpriteObject() = default;

    void setTexture(const sf::Texture& tex);
    void draw(PrimitiveRenderer& renderer);

    void translate(float dx, float dy);
    void rotate(float angleDeg);
    void scale(float factor);

    const sf::Sprite& getSprite() const { return sprite; }
    virtual std::string getType() const { return "SpriteObject"; }
    virtual void update() {}

    void setTextureRect(const sf::IntRect& rect) { sprite.setTextureRect(rect); }


protected:
    const sf::Texture* texture = nullptr;
    sf::Sprite sprite;
};

#endif
