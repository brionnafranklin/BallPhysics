#pragma once
#include <glm\ext.hpp>

class PhysicsObject
{
protected:
	PhysicsObject() {}
public:
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void debug() = 0;
	virtual void makeGizmo() = 0;
	virtual void resetPosition() {};
};

