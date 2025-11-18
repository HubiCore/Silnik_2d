#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include "GameObjects.hpp"
#include "PrimitiveRenderer.hpp"

class DrawableObject : public virtual GameObject {
public:
    virtual void draw(PrimitiveRenderer& renderer) = 0;
};

#endif
