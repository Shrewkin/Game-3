//==================================================================-
/*
/file   level3.cpp
/author Jakob McFarland
/date   11/15/2018
/brief

This is the implementation file for all member functions
of the class level3, as specified in specification
file level3.h.

*/
//==================================================================-

#include "stdafx.h"
#include "ColorChange.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Collider.h"

namespace Behaviors
{

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Constructor
	// Params:
	//   normalColor = The color that the object reverts to when not colliding.
	//   collidedColor = The color that the object changes to when colliding.
	//   collidedColorTime = The amount of time the object will retain the collided color.
	ColorChange::ColorChange(const Color& normalColor, const Color& collidedColor, float collidedColorTime)
		: Component("ColorChange"), normalColor(normalColor), collidedColor(collidedColor),
		collidedColorTime(collidedColorTime), collided(false), timer(0.0f)
	{
	}

	// Return a new copy of the component.
	Component* ColorChange::Clone() const
	{
		return new Behaviors::ColorChange(*this);
	}

	// Collision handler for ColorChange objects.
	// Params:
	//   object = The first object.
	//   other  = The other object the first object is colliding with.
	void ColorChangeCollisionHandler(GameObject& object, GameObject& other)
	{
		UNREFERENCED_PARAMETER(other);

		ColorChange* colorChange = static_cast<ColorChange*>(object.GetComponent("ColorChange"));

		colorChange->collided = true;
		colorChange->timer = colorChange->collidedColorTime;
	}

	// Initialize data for this object.
	void ColorChange::Initialize()
	{
		sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));

		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(ColorChangeCollisionHandler);
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void ColorChange::Update(float dt)
	{
		if (collided)
		{
			collided = false;
			sprite->SetColor(collidedColor);
		}

		if (!collided && timer <= 0.0f)
		{
			sprite->SetColor(normalColor);
		}

		timer -= dt;
	}
}