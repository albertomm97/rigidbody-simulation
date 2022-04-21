#include "Spring.h"

#include <GL/glut.h>

namespace utad
{
Spring::Spring(Particle *p1, Particle *p2, float restLength, float stiffness)
    : m_RestLength(restLength)
    , m_Stiffness(stiffness)
{
    m_Particle1 = p1;
    m_Particle2 = p2;
}

void Spring::Draw()
{
    glBegin(GL_LINES);
    glVertex3f(m_Particle1->m_Position.x(), m_Particle1->m_Position.y(), m_Particle1->m_Position.z());
    glVertex3f(m_Particle2->m_Position.x(), m_Particle2->m_Position.y(), m_Particle2->m_Position.z());
    glEnd();
}

float Spring::ComputeLength()
{
    Vector3f link = m_Particle2->m_Position - m_Particle1->m_Position;
    float length = link.norm();

    return length;
}

Vector3f Spring::ComputeForce()
{
    Vector3f link = m_Particle1->m_Position - m_Particle2->m_Position;
    float length = link.norm();
    Vector3f force = (link / length) * ((m_RestLength - length) * m_Stiffness);

    return force;
}
}  // namespace utad