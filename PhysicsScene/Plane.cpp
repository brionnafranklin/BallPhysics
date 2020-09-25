#include "Plane.h"
#include <Gizmos.h>

/// default constructer
Plane::Plane()
	: PhysicsObject(PLANE)
{
	m_normal = glm::vec2(0.0f, 0.0f);
	m_distanceToOrigin = 0.0f;
}

/// constructer that sets up the normal and distance of the plane
Plane::Plane(glm::vec2 normal, float distance) : PhysicsObject(PLANE)
{
	m_normal = normal;
	m_distanceToOrigin = distance;
}

/// default deconstructer
Plane::~Plane()
{
}

/// overrides the base function
void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

/// draws the plane
void Plane::makeGizmo()
{
	float lineSegmentLength = 300;
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	// easy to rotate normal through 90 degrees around z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colour(1, 1, 1, 1);
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	aie::Gizmos::add2DLine(start, end, colour);
}

/// overrides the base function
void Plane::resetPosition()
{
}

/// tells the physics objects what to do when they collide
void Plane::resolveCollision(RigidBody* actor2, glm::vec2 contact)
{
	glm::vec2 collisionNormal = m_normal;
	glm::vec2 relativeVelocity = actor2->getVelocity();

	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), collisionNormal) /
		(1 / actor2->getMass());

	glm::vec2 force = collisionNormal * j;
	actor2->applyForce(force, contact - actor2->getPosition());
}