#pragma once
#include "RigidBody.h"
#include "PhysicsObject.h"
#include "Sphere.h"

class Box : public RigidBody
{
public:

	Box(glm::vec2 position, glm::vec2 velocity, float rotation, float mass, glm::vec2 extents, glm::vec4 colour);
	~Box() {}
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);
	virtual void makeGizmo();

	bool checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts, float& pen, glm::vec2& edgeNormal);

	virtual bool checkCollision(PhysicsObject* pOther);

	float getWidth() { return m_width; }
	float getHeight() { return m_height; }
	glm::vec2 getExtents() { return m_extents; }
	glm::vec2 getLocalX() { return m_localX; }
	glm::vec2 getLocalY() { return m_localY; }
	glm::vec2 getCenter() { return m_center; }

protected:

	float m_width;
	float m_height;

	glm::vec2 m_center;

	glm::vec2 m_extents; // the halfedge lengths
	glm::vec4 m_colour;

	// store the local x,y axes of the box based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;
};

