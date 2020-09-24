#include "Sphere.h"
#include <Gizmos.h>

/// sets intial position, velocity, mass, radius, and color
Sphere::Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour) : RigidBody(SPHERE, position, velocity, 0.0f, mass)
{
	m_radius = radius;
	m_colour = colour;
	m_moment = 0.5f * mass * radius * radius;
}

/// draws a circle and a line(to show rotation)
void Sphere::makeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) *
		m_radius;
	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(255 - m_colour.x, 255 - m_colour.y, 255 - m_colour.z, 1));
}

/// checks for collision between two spheres
bool Sphere::checkCollision(PhysicsObject* pOther)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(pOther);
	if (otherSphere)
	{
		return glm::distance(m_position, otherSphere->getPosition()) < m_radius + otherSphere->getRadius();
	}
}
