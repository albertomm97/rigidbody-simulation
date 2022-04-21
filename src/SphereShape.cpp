#include "SphereShape.h"

#include <Gfx/Gfx.h>

namespace utad
{
SphereShape::SphereShape()
    : Shape(ShapeType::Sphere)
    , m_Radius(0.5)
{
}

void SphereShape::Draw()
{
    Gfx::drawSphere(Vector3f(0, 0, 0), m_Radius, true);
}

Matrix3f SphereShape::InertiaTensor(float mass)
{
    // https:  // scienceworld.wolfram.com/physics/MomentofInertiaSphere.html
    // TODO
    auto coeff = 0.4f * mass * m_Radius * m_Radius;
   
    auto Ixy = 0.0f;
    auto Ixz = 0.0f;
    auto Iyz = 0.0f;

    Matrix3f tensor;
    tensor << coeff, -Ixy, -Ixz, -Ixy, coeff, -Iyz, -Ixz, -Iyz, coeff;
    return tensor;
}

float SphereShape::Volume()
{
    return ((4/3)*M_PI*(m_Radius*m_Radius*m_Radius));
}

SphereShape *makeSphere(float radius)
{
    SphereShape *shape = new SphereShape;
    shape->m_Radius = radius;

    return shape;
}
}  // namespace utad