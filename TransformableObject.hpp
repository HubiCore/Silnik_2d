#ifndef TRANSFORMABLEOBJECT_HPP
#define TRANSFORMABLEOBJECT_HPP

#include "GameObject.hpp"

class TransformableObject : public virtual GameObject {
public:
    virtual void translate(float dx, float dy) = 0;
    virtual void rotate(float angleDeg) = 0;
    virtual void scale(float factor) = 0;
};

#endif
