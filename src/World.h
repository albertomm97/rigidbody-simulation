#ifndef WORLD_H
#define WORLD_H

#include <RigidBody.h>

#include <vector>

namespace utad
{
class World
{
public:
    std::vector<RigidBody *> rbs;

    void Simulate(float dt);

    void Draw();

    void ClearForces();
    void ComputeExternalForces();
    void EulerIntegration(float dt);
    void EndStep();
};
}  // namespace utad

#endif