#include "Box.h"
#include <Gizmos.h>

Box::Box(glm::vec2 position, glm::vec2 velocity, float rotation, float mass, glm::vec2 extents, glm::vec4 colour) : RigidBody(BOX, position, velocity, rotation, mass)
{
	m_extents = extents;
	m_colour = colour;
	m_width = m_extents.x * 2;
	m_height = m_extents.y * 2;
	m_rotation = rotation;
	m_center.x = position.x - extents.x;
	m_center.y = position.y - extents.y;
	m_localX.x = m_center.x;
	m_localX.y = m_center.x + m_extents.x;
	m_localY.x = m_center.y;
	m_localY.y = m_center.y + m_extents.y;
	m_angularVelocity = 0.0f;
	m_angularDrag = 0.0f;
}

void Box::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	RigidBody::fixedUpdate(gravity, timeStep);
	//store the local axes
	float cs = cosf(m_rotation);
	float sn = sinf(m_rotation);
	m_localX = glm::normalize(glm::vec2(cs, sn));
	m_localY = glm::normalize(glm::vec2(-sn, cs));
}

void Box::makeGizmo()
{
	// if only using rotation
	// glm::mat4 transform = glm::rotate(m_rotation, glm::vec3(0, 0, 1));
	// aie::Gizmos::add2DAABBFilled(getCenter(),
	// m_extents, m_colour, &transform);
	// draw using local axes
	glm::vec2 p1 = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p2 = m_position + m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p3 = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
	glm::vec2 p4 = m_position + m_localX * m_extents.x + m_localY * m_extents.y;
	aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
	aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
}

// check if any of the other box's corners are inside this box
bool Box::checkBoxCorners(const Box& box, glm::vec2& contact, int& numContacts,
	float& pen, glm::vec2& edgeNormal)
{
	float minX, maxX, minY, maxY;
	float boxW = box.m_width;
	float boxH = box.m_height;
	int numLocalContacts = 0;
	glm::vec2 localContact(0, 0);
	bool first = true;
	for (float x = -box.m_extents.x; x < boxW; x += boxW)
	{
		for (float y = -box.m_extents.y; y < boxH; y += boxH)
		{
			// position in worldspace
			glm::vec2 p = box.m_center + x * box.m_localX + y * box.m_localY;
			// position in our box's space
			glm::vec2 p0(glm::dot(p - m_position, m_localX),
				glm::dot(p - m_position, m_localY));
			if (first || p0.x < minX) minX = p0.x;
			if (first || p0.x > maxX) maxX = p0.x;
			if (first || p0.y < minY) minY = p0.y;
			if (first || p0.y > maxY) maxY = p0.y;
			if (p0.x >= -m_extents.x && p0.x <= m_extents.x &&
				p0.y >= -m_extents.y && p0.y <= m_extents.y)
			{
				numLocalContacts++;
				localContact += p0;
			}
			first = false;
		}
	}
	if (maxX <-m_extents.x || minX >m_extents.x ||
		maxY<-m_extents.y || minY >m_extents.y)
		return false;
	if (numLocalContacts == 0)
		return false;
	bool res = false;
	contact += m_position + (localContact.x * m_localX + localContact.y * m_localY) /
		(float)numLocalContacts;
	numContacts++;
	float pen0 = m_extents.x - minX;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) {
		edgeNormal = m_localX;
		pen = pen0;
		res = true;
	}
	pen0 = maxX + m_extents.x;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) {
		edgeNormal = -m_localX;
		pen = pen0;
		res = true;
	}
	pen0 = m_extents.y - minY;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) {
		edgeNormal = m_localY;
		pen = pen0;
		res = true;
	}
	pen0 = maxY + m_extents.y;
	if (pen0 > 0 && (pen0 < pen || pen == 0)) {
		edgeNormal = -m_localY;
		pen = pen0;
		res = true;
	}
	return res;
}

bool Box::checkCollision(PhysicsObject* pOther)
{
	Sphere* otherSphere = dynamic_cast<Sphere*>(pOther);
	Box* otherBox = dynamic_cast<Box*>(pOther);
	if (otherSphere)
	{
		if (glm::distance(m_position, otherSphere->getPosition()) < m_extents.x + otherSphere->getRadius() || glm::distance(m_position, otherSphere->getPosition()) < m_extents.y + otherSphere->getRadius())
		{
			return true;
		}
	}
	/*if (otherBox)
	{
		if (checkBoxCorners(pOther))
		{
			return true;
		}
	}*/
}
