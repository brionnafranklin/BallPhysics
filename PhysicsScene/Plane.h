#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"

/// Static object that spans across the whole screen in a straight line
class Plane : public PhysicsObject
{
public:
	/// default constructer
	Plane();
	/// constructer that sets up the normal and distance of the plane
	Plane(glm::vec2 normal, float distance);
	/// default deconstructer
	~Plane();

	/// overrides the base function
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	/// overrides the base function
	virtual void debug() {}
	/// draws the plane
	virtual void makeGizmo();
	/// overrides the base function
	virtual void resetPosition();
	/// returns the normal
	glm::vec2 getNormal() { return m_normal; }
	/// returns the distance
	float getDistance() { return m_distanceToOrigin; }

	/// tells the physics objects what to do when they collide
	void Plane::resolveCollision(RigidBody* actor2, glm::vec2 contact);

protected:
	/// stores the normal
	glm::vec2 m_normal;
	/// how far away the line is from the center of the screen
	float m_distanceToOrigin;
};

