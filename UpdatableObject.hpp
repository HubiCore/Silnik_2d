#ifndef UPDATABLEOBJECT_HPP
#define UPDATABLEOBJECT_HPP

#include "GameObject.hpp"

class UpdatableObject : public virtual GameObject {
public:
    virtual void update() = 0;
};

#endif
