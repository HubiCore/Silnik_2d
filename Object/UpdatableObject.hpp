#ifndef UPDATABLEOBJECT_HPP
#define UPDATABLEOBJECT_HPP

#include "GameObject/GameObjects.hpp"

class UpdatableObject : public virtual GameObject {
public:
    virtual void update(float deltaTime) = 0;
};

#endif
