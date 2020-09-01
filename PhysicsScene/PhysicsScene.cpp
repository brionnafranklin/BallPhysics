#include "PhysicsScene.h"
#include "RigidBody.h"
#include "Sphere.h"
#include <list>
#include "Plane.h"

PhysicsScene::~PhysicsScene()
{
	for (auto actor : m_actors) {
		delete actor;
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	for (auto i = m_actors.begin(); i < m_actors.end(); i++) {
		if (*i == actor) {
			m_actors.erase(i);
		}
	}
}

void PhysicsScene::update(float deltaTime)
{
	// store how much time has accumulated since last update
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	// while enough time has accumulated...
	while (accumulatedTime >= m_timeStep) {
		// for each PhysicsObject in m_actors...
		for (auto pActor : m_actors) {
			// updated the physics of that object
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		// spend the time needed for that update
		accumulatedTime -= m_timeStep;
		// check for collisions
		checkForCollision();
	}
}

void PhysicsScene::updateGizmos()
{
	for (auto pActor : m_actors) {
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	for (auto actor : m_actors) {
		actor->debug();
	}
}

typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctions[] =
{
	PhysicsScene::planeToPlane, PhysicsScene::planeToSphere,
	PhysicsScene::sphereToPlane, PhysicsScene::sphereToSphere
};

void PhysicsScene::checkForCollision()
{
	// get the number of actors in the scene
	int actorCount = m_actors.size();

	// check for collisions against all objects except this one
	for (int outer = 0; outer < actorCount - 1; outer++) {
		for (int inner = outer + 1; inner < actorCount; inner++) {
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			// find the function in the collision function array
			int functionID = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPtr = collisionFunctions[functionID];
			if (collisionFunctionPtr != nullptr) {
				// check collision
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(obj1);
	Plane* plane = dynamic_cast<Plane*>(obj2);
	//if we are successful then test for collision
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		float sphereToPlane = glm::dot(
			sphere->getPosition(),
			plane->getNormal()) - plane->getDistance();
		// if we are behind plane then we flip the normal
		if (sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}
		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0) {
			//set sphere velocity to zero here
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);
	if (sphere1 != nullptr && sphere2 != nullptr) {
		if (glm::distance(sphere1->getPosition(), sphere2->getPosition()) < sphere1->getRadius() + sphere2->getRadius()) {
			sphere1->applyForceToActor(sphere2, sphere1->getVelocity() * sphere1->getMass());
			return true;
		}
	}
	return false;
}

