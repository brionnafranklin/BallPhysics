#pragma once
#include "RigidBody.h"
#include "PhysicsObject.h"
#include "Sphere.h"

/// a Rigid Body with four sides
class Box : public RigidBody
{
public:

	/// initailizes all the values for box
	Box(glm::vec2 position, glm::vec2 velocity, float rotation, float mass, glm::vec2 extents, glm::vec4 colour);
	/// default deconstructer
	~Box() {}
	/// updates the boxes rotation and calls fixedUpdate for the RigedBody
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	/// draws box
	virtual void makeGizmo();

	/// check if any of the other box's corners are inside this box
	bool checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);

	virtual void debug();

	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	glm::vec2 getExtents() { return m_extents; }
	glm::vec2 getLocalX() { return m_localX; }
	glm::vec2 getLocalY() { return m_localY; }
	glm::vec2 getCenter() { return m_center; }

protected:

	/// the horizontal length
	float m_width;
	/// the vertical length
	float m_height;

	/// where the axes of the box intersect
	glm::vec2 m_center;

	/// the halfedge lengths
	glm::vec2 m_extents; 
	/// contains values for Red, Green, Blue and Alpha between 1.0f and 0.0f
	glm::vec4 m_colour;

	/// store the local x axe of the box based on its angle of rotation
	glm::vec2 m_localX;
	/// store the local y axe of the box based on its angle of rotation
	glm::vec2 m_localY;
};

