#pragma once
#include "PhysicsObject.h"

/// A physics object the moves and interacts with other objects using physics
class RigidBody : public PhysicsObject
{
public:
	/// Constructer; sets the shape id, position, velocity, rotation, mass
	RigidBody(ShapeType shapeID, glm::vec2 position,
		glm::vec2 velocity, float rotation, float mass);
	/// default deconstructer
	~RigidBody();

	/// applies gravity and calculates the change in position
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	/// prints the object's position, and the word "collision" when it collides with something
	virtual void debug();
	/// callculates the change in velocity once a force is applied
	void applyForce(glm::vec2 force, glm::vec2 position);

	/// tells the rigid body how to react when a collision happens
	void resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal = nullptr);

	/// calculates the kinetic energy
		float getKineticEnergy();
		
	/// returns position
	glm::vec2 getPosition() { return m_position; }
	/// returns rotation
	float getRotation() { return m_rotation; }
	/// returns velocity
	glm::vec2 getVelocity() { return m_velocity; }
	/// returns mass
	float getMass() { return m_mass; }
	/// returns linear drag
	float getLinearDrag() { return m_linearDrag; }
	///s ets linear drag
	void setLinearDrag(float value) { m_linearDrag = value; }
	/// returns angular drag
	float getAngualrDrag() { return m_angularDrag; }
	/// sets  angular drag
	void setAngularDrag(float value) { m_angularDrag = value; }
	/// return elasticity
	float getElasticity() { return m_elasticity; }
	/// sets elasticity
	void setElasticity(float value) { m_elasticity = value; }
	/// returns momentum
	float getMoment() { return m_moment; }
	/// sets momentum
	void setMoment(float value) { m_moment = value; }
	/// returns angular velocity
	float getAngularVelocity() { return m_angularVelocity; }

protected:
	/// stores position in the x and y 
	glm::vec2 m_position;
	/// stores velocity in the x and y
	glm::vec2 m_velocity;
	/// the maxium speed an object can react before its capped
	float m_maxSpeed = 1000.0f;
	/// stores angular velocity
	float m_angularVelocity;
	/// stores momentum
	float m_moment;
	/// stores mass
	float m_mass;
	/// stores rotation
	float m_rotation; //2D so we only need a single float to represent our rotation
	/// stores linear drag
	float m_linearDrag = 0.3f;
	/// stores angular drag
	float m_angularDrag = 0.3f;
	/// stores elasticity
	float m_elasticity = 0.5f;
};

