#pragma once
#include "RigidBody.h"

/// a rigid body in the shape of a circle
class Sphere : public RigidBody
{
public:
	/// sets intial position, velocity, mass, radius, and color
	Sphere(glm::vec2 position, glm::vec2 velocity,
		float mass, float radius, glm::vec4 colour);
	/// default deconstructer
	~Sphere() {}

	/// draws a circle and a line(to show rotation)
	virtual void makeGizmo();
	/// checks for collision between two spheres
	virtual bool checkCollision(PhysicsObject* pOther);

	/// returns the length of the radius
	float getRadius() { return m_radius; }
	/// returns the color
	glm::vec4 getColour() { return m_colour; }

protected:
	/// stores the length of radius
	float m_radius;
	/// stores the color in a vector 4 where all values are equal to or inbetween 0 and 1
	glm::vec4 m_colour;
};

