#include "RigidBody.h"

#include <Gfx/Gfx.h>
#include <BoxShape.h>
#include <SphereShape.h>

#include <iostream>

namespace utad
{
RigidBody::RigidBody(Shape *shape)
    : m_Shape(shape)
{
    m_Density = 10.0f;
    m_Position = Vector3f(0, 0, 0);
    m_Rotation = Quaternionf(1, 0, 0, 0);
    m_LinearMomentum = Vector3f(0, 0, 0);
    m_AngularMomentum = Vector3f(0, 0, 0);

    m_Velocity = Vector3f(0, 0, 0);
    m_AngularVelocity = Vector3f(0, 0, 0);
    m_Force = Vector3f(0, 0, 0);
    m_Torque = Vector3f(0, 0, 0);
   
    auto volume = shape->Volume();
    m_Mass = volume * m_Density;
    m_MassInverse = 1 / m_Mass;

    // TODO
    m_InertiaTensorBody = shape->InertiaTensor(m_Mass);
    m_InertiaTensorBodyInverse = m_InertiaTensorBody.inverse();

    m_ForceAccum = Vector3f(0, 0, 0);
    m_TorqueAccum = Vector3f(0, 0, 0);
        
    /*
    std::cout << "Mass: " << m_Mass << "\n";
    std::cout << "MassInv: " << m_MassInverse << "\n";
    std::cout << "Inertia: \n" << m_InertiaTensorBody << "\n";
    std::cout << "InertiaInv: \n" << m_InertiaTensorBodyInverse << "\n";
    */
}

void RigidBody::ApplyForce(const Vector3f &force, const Vector3f &position)
{
    m_ForceAccum += force;
    Vector3f point = position;
    m_TorqueAccum += point.cross(force);
}

void RigidBody::Draw()
{
    Gfx::pushTransform();

    Gfx::translate(m_Position);
    Gfx::rotate(m_Rotation);
    Gfx::setColor(m_Color);
    m_Shape->Draw();

    Gfx::popTransform();
}

void RigidBody::UpdateDerivedState()
{
   
}

void RigidBody::ClearForces()
{
    m_Force = m_ForceAccum;
    m_Torque = m_TorqueAccum;
}

void RigidBody::EulerIntegration(float dt)
{
    const Matrix3f rotation_matrix = m_Rotation.toRotationMatrix();
    m_InertiaTensor = rotation_matrix * m_InertiaTensorBody * rotation_matrix.transpose();
    m_InertiaTensorInverse = m_InertiaTensor.inverse();
    
    m_Torque += m_TorqueAccum;
    m_Force += m_ForceAccum;

    // Aceleracion
    Vector3f acceleration = m_Force * m_MassInverse;
    
    // Velocidad lineal
    m_Velocity += acceleration * dt;

    // Momento lineal
    m_LinearMomentum = m_Velocity * m_Mass;

    // Aceleracion angular
    Vector3f angular_acceleration = m_InertiaTensorInverse * m_Torque;
 
    // Momento angular
    m_AngularMomentum = m_InertiaTensorInverse * m_Torque;

    // Velocidad angular
    m_AngularVelocity += angular_acceleration * dt;
    
    // Rotation
    const Quaternionf rotToAdd = Quaternionf(0.0f, 
        m_AngularVelocity.x(), 
        m_AngularVelocity.y(), 
        m_AngularVelocity.z());                        
    
    m_Rotation += (0.5f * dt * rotToAdd * m_Rotation);
    m_Rotation.normalize();

    // Posicion
    m_Position += m_Velocity * dt;
}


void RigidBody::EndStep()
{
    m_ForceAccum = Vector3f(0, 0, 0);
    m_TorqueAccum = Vector3f(0, 0, 0);
}
}  // namespace utad