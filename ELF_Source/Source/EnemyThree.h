//------------------------------------------------------------------------------
//
// File Name:	EnemyThree.h
// Author(s):	Bar Ben-zvi
// Description: Enemy three does not move but fires a quick burst of bullets at the player with short breaks between bursts
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Component.h"

#include "Vector2D.h"

class GameObject;
class Transform;

namespace Behaviors
{
	enum ShotTypes
	{
		ShotSingle = 1,
		ShotTriple,
		ShotPenta,
		ShotRing
	};

	class EnemyThree : public Component
	{
	public:

		//Constructor for the EnemyThree class
		EnemyThree();

		//Returns a copy of this component
		Component* Clone() const;

		//Handles collision between this and another object
		//Params:
		//	 object = the owner
		//	 other = the object we collided with
		friend void CollisionHandler(GameObject& object, GameObject& other);

		//Initializes this component
		void Initialize() override;

		// Update this component
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop
		void Update(float dt) override;

	private:

		//Fires a set amount of bullets at the player with a set angle offset between them
		//Params:
		//	 spreadAngle = the angle offset between each bullet
		//	 bulletCount = the amount of bullets we are firing
		void Shoot(float spreadAngle, int bulletCount);

		//Current shot type
		ShotTypes currType;

		//Components
		Transform* transform;
		Transform* playerTransform;

		//Shooting stuff
		GameObject* bulletArchetype;
		float projectileSpeed;
		int timesToShoot;
		int shotsRemaining;
		float shootTimer;
		float breakTimer;
		float timer1; //shoot timer
		float timer2; //break timer


	};
}
