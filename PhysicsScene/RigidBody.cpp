#include "RigidBody.h"

RigidBody::RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass)
{
	m_shapeID = shapeID;
	m_position = position;
	m_velocity = velocity;
	m_rotation = rotation;
	m_mass = mass;
}

RigidBody::~RigidBody()
{
}

void RigidBody::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	//Apply gravity
	applyForce(gravity * m_mass * timeStep, m_position);

	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	if (glm::length(m_velocity) < 0.01f) {
		m_velocity = glm::vec2(0.0f, 0.0f);
	}
	if (glm::abs(m_angularVelocity) < 0.01f) {
		m_angularVelocity = 0;
	}
	m_velocity -= m_velocity * m_linearDrag * timeStep;
	//Calculate the change in position
	m_position += m_velocity * timeStep;
	m_angularVelocity -= m_angularVelocity * m_angularDrag * timeStep;
	m_rotation += m_angularVelocity * timeStep;
}

void RigidBody::debug()
{
}

void RigidBody::applyForce(glm::vec2 force, glm::vec2 position)
{
	//Calculate the change in velocity
	m_velocity += force / m_mass;
}

void RigidBody::resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal)
{
	// find the vector between their centres, or use the provided direction
// of force, and make sure it's normalised
	glm::vec2 normal = glm::normalize(collisionNormal ? *collisionNormal :
		actor2->m_position - m_position);
	// get the vector perpendicular to the collision normal
	glm::vec2 perp(normal.y, -normal.x);

	// detemine the total velocity of the contact points for the two objects,
	// for both linear and rotational

	// 'r' is the radius from axis to application of force
	float radius = glm::dot(contact - m_position, -perp);
	float otherRadius = glm::dot(contact - actor2->m_position, perp);
	// velocity of the contact point on this object
	float velocity = glm::dot(m_velocity, normal) - radius * m_angularVelocity;
	// velocity of contact point on actor2
	float otherVelocity = glm::dot(actor2->m_velocity, normal) +
		otherRadius * actor2->m_angularVelocity;
	if (velocity > otherVelocity) // they're moving closer
	{
		// calculate the effective mass at contact point for each object
		// ie how much the contact point will move due to the force applied.
		float mass = 1.0f / (1.0f / m_mass + (radius * radius) / m_moment);
		float otherMass = 1.0f / (1.0f / actor2->m_mass + (otherRadius * otherRadius) / actor2->m_moment);

		float elasticity = (m_elasticity + actor2->getElasticity()) / 2.0f;

		glm::vec2 force = (1.0f + elasticity) * mass * otherMass /
			(mass + otherMass) * (velocity - otherVelocity) * normal;

		//apply equal and opposite forces
		applyForce(-force, contact - m_position);
		actor2->applyForce(force, contact - actor2->m_position);
	}
}

float RigidBody::getKineticEnergy()
{
	return 0.5f * (m_mass * glm::dot(m_velocity, m_velocity) +
		m_moment * m_angularVelocity * m_angularVelocity);
}
