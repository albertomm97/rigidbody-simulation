#include "World.h"

namespace utad
{
const Vector3f Gravity(0.0f, 0.0f, 0.0f);

void World::Simulate(float dt)
{
    // Clear the force for all rigid bodies
    ClearForces();

    // Compute external forces applied on each rigid body
    ComputeExternalForces();

    // Compute the new cloth state by Euler's Method
    EulerIntegration(dt);

    // End step
    EndStep();
}

void World::Draw()
{
    for (RigidBody *rb : rbs) {
        rb->Draw();
    }
}

void World::ClearForces()
{
    for (RigidBody *rb : rbs) {
        rb->ClearForces();
    }
}

void World::ComputeExternalForces()
{
    Vector3f weight = Gravity;

    for (RigidBody *rb : rbs) {
        rb->m_Force += Gravity;
    }
}

void World::EulerIntegration(float dt)
{
    for (RigidBody *rb : rbs) {
        rb->EulerIntegration(dt);
    }
}

void World::EndStep()
{
    for (RigidBody *rb : rbs) {
        rb->EndStep();
    }
}
}  // namespace utad
