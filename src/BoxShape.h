#ifndef BOX_SHAPE_H
#define BOX_SHAPE_H

#include <Shape.h>

#include <vector>

namespace utad
{
class BoxShape : public Shape
{
public:
    BoxShape();

    void Draw();

    Matrix3f InertiaTensor(float mass);
    float Volume();

    Vector3f m_HalfSize;
};

BoxShape *makeBox(Vector3f halfSize);
}  // namespace utad

#endif