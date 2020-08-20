#include "Sphere.h"
#include <Gizmos.h>

Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : RigidBody(SPHERE, position, velocity, 0.0f, mass)
{
	m_radius = radius;
	m_colour = colour;
}

void Sphere::makeGizmo()
{
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
}

bool Sphere::checkCollision(PhysicsObject* pOther)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(pOther);
	if (otherSphere)
	{
		return glm::distance(m_position, otherSphere->getPosition()) < m_radius + otherSphere->getRadius();
	}
}
