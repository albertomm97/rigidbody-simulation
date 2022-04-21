#ifndef RIGID_BODY_H
#define RIGID_BODY_H

#include <Math/Quaternionf.h>
#include <Math/Matrix3f.h>
#include <Math/Vector3f.h>
#include <Shape.h>

#include <iostream>

namespace utad
{
class RigidBody
{
public:
    Shape *m_Shape;

    float m_Density;
    Vector3f m_Position;
    Quaternionf m_Rotation;
    Vector3f m_LinearMomentum;
    Vector3f m_AngularMomentum;

    float m_Mass;
    float m_MassInverse;
    Matrix3f m_InertiaTensorBody;
    Matrix3f m_InertiaTensorBodyInverse;

    Vector3f m_Force;
    Vector3f m_Torque;

    Vector3f m_Velocity;
    Vector3f m_AngularVelocity;

    Matrix3f m_InertiaTensor;
    Matrix3f m_InertiaTensorInverse;

    Vector3f m_ForceAccum;
    Vector3f m_TorqueAccum;

    Vector3f m_Color;

    RigidBody(Shape *shape);

    void ApplyForce(const Vector3f &force, const Vector3f &position);

    void Draw();

    void UpdateDerivedState();

    void ClearForces();
    void EulerIntegration(float dt);
    void EndStep();
};
}  // namespace utad

#endif