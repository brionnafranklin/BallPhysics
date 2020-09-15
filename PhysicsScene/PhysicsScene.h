#pragma once
#include "glm\ext.hpp""
#include "PhysicsObject.h"
#include <vector>

class PhysicsScene
{
public:
	PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0.0f, 0.0f)) {}
	~PhysicsScene();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void update(float deltaTime);
	void updateGizmos();
	void debugScene();

	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }
	glm::vec2 getGravity() const { return m_gravity; }

	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }
	float getTimeStep() const { return m_timeStep; }

	void checkForCollision();

	static bool planeToPlane(PhysicsObject*, PhysicsObject*);
	static bool planeToSphere(PhysicsObject*, PhysicsObject*);
	static bool planeToBox(PhysicsObject*, PhysicsObject*);
	static bool sphereToPlane(PhysicsObject*, PhysicsObject*);
	static bool sphereToSphere(PhysicsObject*, PhysicsObject*);
	static bool sphereToBox(PhysicsObject*, PhysicsObject*);
	static bool boxToPlane(PhysicsObject*, PhysicsObject*);
	static bool boxToSphere(PhysicsObject*, PhysicsObject*);
	static bool boxToBox(PhysicsObject*, PhysicsObject*);

protected:
	glm::vec2	m_gravity;
	float		m_timeStep;

	std::vector<PhysicsObject*>	m_actors;
};