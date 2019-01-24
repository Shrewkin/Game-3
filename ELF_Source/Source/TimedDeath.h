//------------------------------------------------------------------------------
//
// File Name:	TimedDeath.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

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

typedef class Transform Transform;
typedef class Physics Physics;
struct MapCollision;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Behaviors
{

	class TimedDeath : public Component
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------
		
		// Constructor
		// Params:
		//   timeUntilDeath = Amount of time until the object self-destructs.
		TimedDeath(float timeUntilDeath = 3.0f, bool mapCollision = true);

		// Clone a component and return a pointer to the cloned component.
		// Returns:
		//   A pointer to a dynamically allocated clone of the component.
		Component* Clone() const override;

		friend void BulletMapCollisionHandler(GameObject& object, const MapCollision& collision);

		void Initialize() override;

		// Update function for this component.
		// Params:
		//   dt = The (fixed) change in time since the last step.
		void Update(float dt) override;

		// Sets the "enemy" bool which controls wether the bullet hits the player
		// Params:
		//	 val = the value we are setting the enemy bool to
		void SetEnemyBool(bool val);

		// Returns the enemy bool
		bool GetEnemyBool() const;

		

	private:
		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Amount of time until the object self-destructs.
		float timeUntilDeath;

		bool enemy;
		bool connectMapCollision;
	};
}

//------------------------------------------------------------------------------
