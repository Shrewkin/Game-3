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

		EnemyThree();

		Component* Clone() const;

		friend void CollisionHandler(GameObject& object, GameObject& other);

		void Initialize() override;

		void Update(float dt) override;

	private:

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
