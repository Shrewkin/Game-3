/*
/file   PlayerShooting.cpp
/author Jakob McFarland
/date   1/16/2019
/brief

This is the implementation file for all member functions
of the class PlayerShooting.

*/

#include "stdafx.h"
#include "PlayerShooting.h"

#include <Input.h>
#include <Color.h>
#include <Graphics.h>
#include <Transform.h>
#include <GameObject.h>
#include <Sprite.h>
#include <Space.h>
#include <Interpolation.h>
#include <ColliderTilemap.h>
#include <ColliderRectangle.h>

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------


namespace Behaviors
{
	// Constructor
	// Params:
	//	mHeat = float, Maximum over heating that the laser can take
	//	beamLenth
	PlayerShooting::PlayerShooting(GameObject* laserBeamObj_, ColliderTilemap* worldMap_, float maxHeat_,
		int beamLength_, float beamWidth_)
		: Component("PlayerShooting"), laserBeamObject(laserBeamObj_), overHeating(0.0f),
		maxHeat(maxHeat_), rayCastLength(beamLength_), beamWidth(beamWidth_), worldMap(worldMap_)
	{
	}

	// Clone a component and return a pointer to the cloned component.
	// Returns:
	//   A pointer to a dynamically allocated clone of the component.
	Component* PlayerShooting::Clone() const
	{
		return new PlayerShooting(*this);
	}

	// Initialize this component (happens at object creation).
	void PlayerShooting::Initialize()
	{
		overHeating = 0.0f;

		coolColor = Colors::Red;
		hotColor = Colors::White;

		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));

		laserBeamTransform =  static_cast<Transform*>( laserBeamObject->GetComponent("Transform") );
		laserBeamSprite = static_cast<Sprite*>(laserBeamObject->GetComponent("Sprite"));
	}

	// Update function for this component.
	// Params:
	//   dt = The (fixed) change in time since the last step.
	void PlayerShooting::Update(float dt)

	{
		if (Input::GetInstance().CheckHeld(VK_LBUTTON))
		{
			//check heat
			if (overHeating <= maxHeat)
			{
				//update overheating with delta time
				overHeating += dt;

				//shoot
				Vector2D aim = GetAim();

				Vector2D result = Vector2D(0.0f, 0.0f);

				Shoot( aim, result );

				//draw beam
				laserBeamSprite->SetAlpha(1);

				laserBeamTransform->SetRotation(atan2f(aim.y, aim.x));
				laserBeamTransform->SetScale( Vector2D( result.Magnitude(), beamWidth) );
			}
		}
		else
		{
			laserBeamSprite->SetAlpha(0);

			//update cooldown with delta time
			overHeating -= dt;
		}		

		laserBeamTransform->SetTranslation(transform->GetTranslation());
		laserBeamSprite->SetColor(Interpolate(coolColor, hotColor, 1.0f / overHeating));
	}

	//------------------------------------------------------------------------------
	// Private Functions:
	//------------------------------------------------------------------------------

	// Finds the player's aim vector based on the mouse current position
	// Returns:
	//	a normalized vector to the player's mouse
	Vector2D PlayerShooting::GetAim()
	{
		//get direction on screen
		Vector2D scrnPos = Input::GetInstance().GetCursorPosition();

		//Graphics::GetInstance()

		//return that normalized, should be equal to a world coordinate vector
		return scrnPos.Normalized();
	}

	// Shoots a laser beam based on the player's aim vector
	// Params:
	//	aim = Vector2D that holds the player's aim vector
	void PlayerShooting::Shoot(Vector2D aim, Vector2D result)
	{
		//ray cast
		for (float i = 0; i < rayCastLength; ++i)
		{
			GameObject* obj = new GameObject("RayPoint");
			Transform* objTransform = new Transform(aim * (i + 1.0f) * 10.0f);
			ColliderRectangle* collider = new ColliderRectangle(Vector2D(10.0f, 10.0f));
			obj->AddComponent(objTransform);
			obj->AddComponent(collider);

			GetOwner()->GetSpace()->GetObjectManager().AddObject(*obj);
			obj->Destroy();		

			if (worldMap != nullptr)
			{
				//stop at tilemap
				if (collider->IsCollidingWith(*worldMap))
				{
					return;
				}
			}

			result = objTransform->GetTranslation();
		}
	}
}
