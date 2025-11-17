//
// Created by huber on 04.11.2025.
//
#include "PrimitiveRenderer.hpp"
#ifndef PGK_GAMEOBJECTS_HPP
#define PGK_GAMEOBJECTS_HPP


class DrawableObject :public PrimitiveRenderer {
    void draw();


};
class GameObject : public DrawableObject {
public://boze dlaczego to istnieje wtf wtf wtf
    void scale(float k, float x1, float y1); //D:
    void rotate();
    void move(float t, float x1, float y1);

};
class UpdatableObjects : public GameObject{
    void update();

};



class TransformatableObject : public GameObject{

};
class ShapeObject : public DrawableObject, public TransformatableObject{


};

#endif //PGK_GAMEOBJECTS_HPP

