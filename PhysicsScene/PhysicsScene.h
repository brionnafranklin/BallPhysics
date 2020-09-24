#pragma once
#include "glm\ext.hpp""
#include "PhysicsObject.h"
#include <vector>

/// directly handles the physics 
class PhysicsScene
{
public:
	/// sets timeStep to 0.01f and gravity to nothing by default
	PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0.0f, 0.0f)) {}
	/// clears the acters
	~PhysicsScene();

	/// adds actor to the list of actors
	void addActor(PhysicsObject* actor);
	/// deletes actor from the list of actors
	void removeActor(PhysicsObject* actor);
	/// updates the the physics for every object in the game
	void update(float deltaTime);
	/// makes a gizmo for every object in the game
	void updateGizmos();
	/// calls debug for every object in the game
	void debugScene();

	/// takes in a value and sets gravity to that value
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	/// returns the value of m_gravity
	glm::vec2 getGravity() const { return m_gravity; }

	/// takes in a value and sets the time step to that value
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	/// returns the value of m_timeStep
	float getTimeStep() const { return m_timeStep; }

	/// checks for collisions against all objects
	void checkForCollision();

	/// checks for collision between a plane and another plane
	static bool planeToPlane(PhysicsObject*, PhysicsObject*);
	/// checks for collision between a plane and a sphere
	static bool planeToSphere(PhysicsObject*, PhysicsObject*);
	/// checks for collision between a sphere and a plane
	static bool sphereToPlane(PhysicsObject*, PhysicsObject*);
	/// checks for collision between a sphere and another sphere
	static bool sphereToSphere(PhysicsObject*, PhysicsObject*);

protected:
	/// stores the value of gravity
	glm::vec2	m_gravity;
	/// stores the value for the time step
	float		m_timeStep;

	/// a list of all the actors in the scene
	std::vector<PhysicsObject*>	m_actors;
};