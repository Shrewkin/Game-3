//------------------------------------------------------------------------------
//
// File Name:	PlayerMovement
// Author(s):	Peter Strizhev
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "PlayerMovement.h"
#include "GameObject.h"
#include "Collider.h"
#include "Input.h"
#include "Transform.h"
#include "Physics.h"
#include "Space.h"
#include "Graphics.h"

namespace Behaviors
{
	//==================================================================-
	// Public methods:
	//==================================================================-

	// Constructor
	PlayerMovement::PlayerMovement()
		: Component("PlayerMovement")
		, playerWalkSpeed(200.0f)
		, playerJumpSpeed(400.0f)
		, gravity(0.0f, -300.0f)
		, onGround(false)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* PlayerMovement::Clone() const
	{
		return new PlayerMovement(*this);
	}

	// Map collision handler for Player objects.
	// Params:
	//   object = The Player object.
	//   collision = Which sides the Player collided on.
	void PlayerMapCollisionHandler(GameObject& object,
		const MapCollision& collision)
	{
		if (collision.bottom)
		{
			static_cast<PlayerMovement*>(object.GetComponent("PlayerMovement"))->onGround = true;
		}
	}

	// Collision handler for Player.
	// Params:
	//   object = The Player.
	//   other  = The object the Player is colliding with.
	void PlayerCollisionHandler(GameObject& object, GameObject& other)
	{
		//if the object is named collectable, destroy it
		if (other.GetName()._Equal("Collectable"))
		{
			other.Destroy();

			//check if THIS collectable is the last one
			if (object.GetSpace()->GetObjectManager().GetObjectCount("Collectable") <= 1)
			{
				object.GetSpace()->RestartLevel();
			}
		}

		//if the object is named hazard, kill the player
		if (other.GetName()._Equal("Hazard"))
		{
			object.GetSpace()->RestartLevel();
		}

		//if the object is named enemy, kill the player
		if (other.GetName()._Equal("Enemy"))
		{
			object.GetSpace()->RestartLevel();
		}
	}

	// Initialize this component (happens at object creation).
	void PlayerMovement::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
	}

	// Fixed update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void PlayerMovement::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);
		MoveHorizontal();
		MoveVertical();

		Graphics& graphics = Graphics::GetInstance();
		Camera& camera = graphics.GetCurrentCamera();
		camera.SetTranslation(Vector2D(8.0f, 6.0f));
	}

	//==================================================================-
	// Private Methods:
	//==================================================================-

	// Moves horizontally based on input
	void PlayerMovement::MoveHorizontal() const
	{
		Vector2D move = physics->GetVelocity();
		move.x = 0.0f;

		if (Input::GetInstance().CheckHeld(VK_RIGHT) || Input::GetInstance().CheckHeld('D'))
		{
			move.x += playerWalkSpeed;
		}
		else if (Input::GetInstance().CheckHeld(VK_LEFT) || Input::GetInstance().CheckHeld('A'))
		{
			move.x -= playerWalkSpeed;
		}

		physics->SetVelocity(move);
	}

	// Moves vertically based on input
	void PlayerMovement::MoveVertical()
	{
		Vector2D move = physics->GetVelocity();
		move.y = 0.0f;
		if (Input::GetInstance().CheckHeld(VK_UP) || Input::GetInstance().CheckHeld('W'))
		{
			move.y += playerWalkSpeed;
		}
		else if (Input::GetInstance().CheckHeld(VK_DOWN) || Input::GetInstance().CheckHeld('S'))
		{
			move.y -= playerWalkSpeed;
		}

		physics->SetVelocity(move);
	}
}