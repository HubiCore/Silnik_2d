//
// Created by huber on 04.11.2025.
//

#include "GameObjects.hpp"
void DrawableObject::draw() {
    //PrimitiveRenderer::dr
}
void GameObject::move(float t, float x1, float y1) {
    float x2 = x1 + t;
    float y2 = y1 + t;
}
void GameObject::rotate() {

}
void GameObject::scale(float k, float x1, float y1) {
    float x2 = x1 * k;
    float y2 = y1 * k;
}
