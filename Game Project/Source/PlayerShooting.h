/*
/file   PlayerShooting.h
/author Jakob McFarland
/date   1/16/2019
/brief

This is the specification file for all member functions
of the class PlayerShooting.

*/

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Component.h" // base class

#include "Vector2D.h" // Vector2D


//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class Transform;
class Sprite;
class ColliderTilemap;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class PlayerShooting : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Constructor
		PlayerShooting(GameObject* laserBeamObj_, float maxheat_ = 5.0f, int beamLength = 10);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		// Initialize this component (happens at object creation).
		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

	private:
		//------------------------------------------------------------------------------
		// Private Functions:
		//------------------------------------------------------------------------------

		// Finds the player's aim vector based on the mouse current position
		// Returns:
		//	a normalized vector to the player's mouse
		Vector2D GetAim();

		// Shoots a laser beam based on the player's aim vector
		// Params:
		//	aim = Vector2D that holds the player's aim vector
		void Shoot(Vector2D aim);

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// properties
		float overHeating;
		float maxHeat;
		int rayCastLength;

		//ray
		ColliderTilemap* worldMap;

		GameObject* laserBeamObject;
		Transform* laserBeamTransform;
		Sprite* laserBeamSprite;

		// Components
		Transform* transform;
	};
}