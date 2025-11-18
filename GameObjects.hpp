#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif
