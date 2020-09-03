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
	applyForce(gravity * m_mass * timeStep);
	//Calculate the change in position
	m_position += m_velocity * timeStep;
}

void RigidBody::debug()
{
}

void RigidBody::applyForce(glm::vec2 force)
{
	//Calculate the change in velocity
	m_velocity += force / m_mass;
}

void RigidBody::applyForceToActor(RigidBody* otherActor, glm::vec2 force)
{
	//Apply the force to the other actor
	otherActor->applyForce(force);
	//Apply the opposite force to this actor
	applyForce(-force);
}

void RigidBody::resolveCollision(RigidBody* actor2)
{
	glm::vec2 normal = glm::normalize(actor2->getPosition() - m_position);
	glm::vec2 relativeVelocity = actor2->getVelocity() - m_velocity;
	float elasticity = 1;
	float j = glm::dot(-(1 + elasticity) * (relativeVelocity), normal) /
		glm::dot(normal, normal * ((1 / m_mass) + (1 / actor2->getMass())));
	glm::vec2 force = normal * j;
	applyForceToActor(actor2, force);
}