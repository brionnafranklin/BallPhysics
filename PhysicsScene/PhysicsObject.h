#pragma once
#include <glm\ext.hpp>

/// used to keep track of shapes by number as well as take note of how many shapes are in the program
enum ShapeType {
	PLANE = 0,
	SPHERE,
	SHAPE_COUNT
};

/// base class for every object in the program
class PhysicsObject
{
protected:
	/// sets the shapeID
	PhysicsObject(ShapeType shapeID) : m_shapeID(shapeID) {}
	/// default deconstructer
	PhysicsObject(){}
public:
	/// base function for updating
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	/// base function for debugging
	virtual void debug() = 0;
	/// base function for creating gizmos
	virtual void makeGizmo() = 0;
	/// base function for resetting position
	virtual void resetPosition() {};

	/// returns shape ID
	ShapeType getShapeID() { return m_shapeID; }

protected:
	/// stores shape ID
	ShapeType m_shapeID;
};