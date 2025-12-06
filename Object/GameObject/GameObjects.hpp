#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>

class GameObject {
public:
    virtual ~GameObject() = default;
    virtual std::string getType() const = 0;

    virtual void update() = 0;
    virtual void draw() = 0;
};

#endif
