#pragma once

class AnimatedObject {
public:
    virtual void animate(float dt) = 0;
    virtual ~AnimatedObject() = default;
};
