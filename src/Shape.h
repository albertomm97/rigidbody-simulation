#ifndef SHAPE_H
#define SHAPE_H

#include <Math/Matrix3f.h>
#include <Math/Vector3f.h>

#include <vector>

namespace utad
{
enum ShapeType { Sphere, Box };

class Shape
{
public:
    Shape(ShapeType type);

    virtual void Draw() = 0;

    virtual Matrix3f InertiaTensor(float mass) = 0;

    virtual float Volume() = 0;

    ShapeType m_Type;
};
}  // namespace utad

#endif