//==================================================================-
/*
/file   PlayerShip.cpp
/author Jakob McFarland
/date   10/18/2018
/brief

This is the implementation file for all member functions
of the class PlayerShip, as specified in specification
file PlayerShip.h.

*/
//==================================================================-

#include "stdafx.h"
#include "PlayerShip.h"

#include "Space.h"
#include <Engine.h>
#include "SoundManager.h"
#include <Random.h>
#include "GameObjectManager.h"
#include <Input.h>
#include <Parser.h>
#include "Transform.h"
#include "Physics.h"
#include "Sprite.h"

namespace Behaviors
{
	//==================================================================-
	// Public Functions:
	//==================================================================-
	
	// Constructor
	// Params:
	//   forwardThrust = Amount of force added to the ship when thrusters are activated.
	//   maximumSpeed  = Maximum attainable speed of the ship.
	//   rotationSpeed = Speed at which the ship rotates.
	//   bulletSpeed   = Speed at which bullets move when fired by ship.
	//   deathDuration = Length of death "animation" in seconds.
	PlayerShip::PlayerShip(float forwardThrust, float maximumSpeed,
		float rotationSpeed, float bulletSpeed)
		: Component("PlayerShip"), forwardThrust(forwardThrust), maximumSpeed(maximumSpeed),
		rotationSpeed(rotationSpeed), bulletSpeed(bulletSpeed)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* PlayerShip::Clone() const 
	{
		return new PlayerShip(*this);
	}
	
	// Initialize this component (happens at object creation).
	void PlayerShip::Initialize()
	{
		transform = static_cast<Transform*>( GetOwner()->GetComponent("Transform") );
		physics = static_cast<Physics*>( GetOwner()->GetComponent("Physics") );

		bulletArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet");

		SoundManager* soundManager = Engine::GetInstance().GetModule<SoundManager>();
		soundEvent = soundManager->PlayEvent("Test Tones");

		soundEvent->setPaused(true);
		soundEvent->setVolume(0.5f);
		soundEvent->setParameterValue("Wave Type", 0);
		soundEvent->setParameterValue("LowMidHigh", 0);
	}
	
	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void PlayerShip::Update(float dt) 
	{
		UNREFERENCED_PARAMETER(dt);

		Move();
		Rotate();
		if(bulletArchetype != nullptr) 
			Shoot();		
	}

	//==================================================================-
	// Private Functions:
	//==================================================================-
	
	// Move forward when up arrow is pressed
	void PlayerShip::Move() const
	{
		if (Input::GetInstance().CheckHeld(VK_UP))
		{
			physics->AddForce( Vector2D::FromAngleRadians(transform->GetRotation()) * forwardThrust );

			//clamp velocity
			if (physics->GetVelocity().Magnitude() > maximumSpeed)
			{
				physics->SetVelocity(Vector2D::FromAngleRadians(transform->GetRotation()) * maximumSpeed);
			}

			soundEvent->setPaused(false);
		}
		else
		{
			soundEvent->setPaused(true);
		}
	}
	
	// Rotate when left or right arrow key is pressed
	void PlayerShip::Rotate() const
	{
		float newAngularVelocity = 0;

		if (Input::GetInstance().CheckHeld(VK_RIGHT))
		{
			newAngularVelocity -= rotationSpeed;  
		}

		if (Input::GetInstance().CheckHeld(VK_LEFT))
		{
			newAngularVelocity += rotationSpeed;
		}

		physics->SetAngularVelocity(newAngularVelocity);
	}
	
	// Shoot projectiles when space is pressed
	void PlayerShip::Shoot() const
	{
		if (Input::GetInstance().CheckTriggered(VK_SPACE))
		{
			//initiliaze working data
			GameObject* bullet = new GameObject(*bulletArchetype);

			Vector2D shipDirection = Vector2D::FromAngleRadians(transform->GetRotation());
			Transform* bulletTransform = static_cast<Transform*>( bullet->GetComponent("Transform") );
			Physics* bulletPhysics = static_cast<Physics*>( bullet->GetComponent("Physics"));

			//adjust bullet data
			bulletTransform->SetTranslation(transform->GetTranslation() + shipDirection.Normalized() * transform->GetScale().x / 2);
			bulletTransform->SetRotation(transform->GetRotation());
			bulletPhysics->SetVelocity(shipDirection * bulletSpeed);

			GetOwner()->GetSpace()->GetObjectManager().AddObject(*bullet);
		}
	}
}