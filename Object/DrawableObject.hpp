#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include "GameObject/GameObjects.hpp"
#include "Renderer/PrimitiveRenderer.hpp"

class DrawableObject : public virtual GameObject {
public:
    virtual void draw(PrimitiveRenderer& renderer) = 0;
};

#endif
