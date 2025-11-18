#ifndef SHAPEOBJECT_HPP
#define SHAPEOBJECT_HPP

#include "DrawableObject.hpp"
#include "TransformableObject.hpp"

class ShapeObject :
        public virtual DrawableObject,
        public virtual TransformableObject {
public:
    virtual ~ShapeObject() = default;

    // draw(), translate(), rotate(), scale()
    // pozostają abstrakcyjne
};

#endif
