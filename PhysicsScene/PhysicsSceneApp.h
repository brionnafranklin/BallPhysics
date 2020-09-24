#pragma once
#include "Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

/// create and place all objects in the scene
class PhysicsSceneApp : public aie::Application 
{
public:

	/// default contructer
	PhysicsSceneApp();
	/// default decontructer
	virtual ~PhysicsSceneApp();

	/// where the objects are created and placed
	virtual bool startup();
	/// deletes font and renderer
	virtual void shutdown();

	/// clears buffer, updates the PhysicsScene, and closes the program when excape it hit
	virtual void update(float deltaTime);
	/// draws the gizmos and text
	virtual void draw();

	/// calculates where the sphere will be in the next frame
	void setupContinuousDemo(glm::vec2 initialPosition, glm::vec2 initialVelocity, float gravity);

	/// calculates the velocity using intial and final positions, gravity, and time
	glm::vec2 calculateVelocity(glm::vec2 initialPosition, glm::vec2 finalPosition, float gravity, float time);

protected:

	/// renders 2d objects
	aie::Renderer2D*	m_2dRenderer;
	/// the font of the text
	aie::Font*			m_font;
	/// the scene in chrange up physics
	PhysicsScene* m_physicsScene;
};