//==================================================================-
/*
/file   TimedDeath.cpp
/author Jakob McFarland
/date   10/15/2018
/brief

This is the implementation file for all member functions
of the class TimedDeath, as specified in specification
file TimedDeath.h.

*/
//==================================================================-

#include "stdafx.h"
#include "TimedDeath.h"

#include "GameObject.h"
#include "ColliderTilemap.h"


namespace Behaviors
{
	//==================================================================-
	// Public Functions:
	//==================================================================-

	// Constructor
	// Params:
	//   timeUntilDeath = Amount of time until the object self-destructs.
	TimedDeath::TimedDeath(float timeUntilDeath)
		: Component("TimedDeath"), timeUntilDeath(timeUntilDeath), enemy(false)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* TimedDeath::Clone() const
	{
		return new TimedDeath(*this);
	}

	void BulletMapCollisionHandler(GameObject& object, const MapCollision& collision)
	{
		UNREFERENCED_PARAMETER(collision);
		object.Destroy();
	}

	void TimedDeath::Initialize()
	{
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetMapCollisionHandler(BulletMapCollisionHandler);
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void TimedDeath::Update(float dt)
	{
		timeUntilDeath -= dt;

		if (timeUntilDeath <= 0)
		{
			GetOwner()->Destroy();
		}
	}

	void TimedDeath::SetEnemyBool(bool val)
	{
		enemy = val;
	}

	bool TimedDeath::GetEnemyBool() const
	{
		return enemy;
	}
}