#ifndef SPHERE_SHAPE_H
#define SPHERE_SHAPE_H

#include <Shape.h>

#include <vector>

namespace utad
{
class SphereShape : public Shape
{
public:
    SphereShape();

    void Draw();

    Matrix3f InertiaTensor(float mass);
    float Volume();

    float m_Radius;
};

SphereShape *makeSphere(float radius);
}  // namespace utad

#endif