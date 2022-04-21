#include "BoxShape.h"

#include <Gfx/Gfx.h>

#include <iostream>

namespace utad
{
BoxShape::BoxShape()
    : Shape(ShapeType::Box)
    , m_HalfSize(0.5f, 0.5f, 0.5f)
{
}

void BoxShape::Draw()
{
    Gfx::drawBox(-m_HalfSize, m_HalfSize, true);
}

Matrix3f BoxShape::InertiaTensor(float mass)
{
    // https://scienceworld.wolfram.com/physics/MomentofInertiaRectangularParallelepiped.html
    Vector3f realSize = m_HalfSize.array()*2;
    const auto x = realSize.x() * realSize.x();
    const auto y = realSize.y() * realSize.y();
    const auto z = realSize.z() * realSize.z();

    const auto Ixx = 0.33f * mass * (z + y);
    const auto Iyy = 0.33f * mass * (x + z);
    const auto Izz = 0.33f * mass * (x + y);

    const auto Ixy = 0.0f;
    const auto Ixz = 0.0f;
    const auto Iyz = 0.0f;

    Matrix3f tensor;
    tensor << Ixx, -Ixy, -Ixz, -Ixy, Iyy, -Iyz, -Ixz, -Iyz, Izz;

    return tensor;
}

float BoxShape::Volume()
{
    Vector3f realSize = m_HalfSize * 2;
    return (realSize.x() * realSize.y() * realSize.z());
}

inline int sgn(float x)
{
    return (x < 0) ? -1 : (x > 0) ? 1 : 0;
}

BoxShape *makeBox(Vector3f halfSize)
{
    BoxShape *shape = new BoxShape;
    shape->m_HalfSize = halfSize;

    return shape;
}
}  // namespace utad