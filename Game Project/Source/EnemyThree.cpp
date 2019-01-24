//------------------------------------------------------------------------------
//
// File Name:	EnemyThree.cpp
// Author(s):	Bar Ben-zvi
// Description: Enemy three does not move but fires a quick burst of bullets at the player with short breaks between bursts
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------
#include "stdafx.h"

#include "EnemyThree.h"
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include <Transform.h>
#include <Physics.h>
#include "TimedDeath.h"
#include <Random.h>
#include "Health.h"
#include "Collider.h"

namespace Behaviors
{
	EnemyThree::EnemyThree()
		: Component("EnemyThree"), currType(ShotSingle), projectileSpeed(200.0f), timesToShoot(10), shotsRemaining(10), shootTimer(0.3f),
		  breakTimer(3.0f), timer1(0.3f), timer2(3.0f)
	{
	}

	Component* EnemyThree::Clone() const
	{
		return new EnemyThree(*this);
	}

	void CollisionHandler(GameObject& owner, GameObject& other)
	{
		if(other.GetName() == "RayPoint")
		{
			static_cast<Health*>(owner.GetComponent("Health"))->Subtract(1);
		}

		if (other.GetName() == "Bullet" && !static_cast<TimedDeath*>(other.GetComponent("TimedDeath"))->GetEnemyBool())
		{
			static_cast<Health*>(owner.GetComponent("Health"))->Subtract(1);
			other.Destroy();
		}
	}

	void EnemyThree::Initialize()
	{
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(CollisionHandler);

		bulletArchetype = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet");

		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		playerTransform = static_cast<Transform*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("Player")->GetComponent("Transform"));
	}

	void EnemyThree::Update(float dt)
	{
		//If we still need to shoot
		if (shotsRemaining > 0)
		{
			timer1 -= dt;

			if (timer1 <= 0)
			{
				float f_PI = static_cast<float>(M_PI);
				if (currType == ShotSingle)
				{
					Shoot(0.0f, 1);
				}
				else if (currType == ShotTriple)
				{
					Shoot(f_PI / 4.0f, 3);
				}
				else if (currType == ShotPenta)
				{
					Shoot(f_PI / 6.0f, 5);
				}
				else
				{
					Shoot(f_PI / 8.0f, 16);
				}
				
				shotsRemaining--;
				timer1 = shootTimer * currType;
			}
		}
		else
		{
			timer2 -= dt;

			//After a break between firing, select a new random shot type
			if (timer2 <= 0)
			{
				int newType = RandomRange(ShotSingle, ShotRing);
				currType = static_cast<ShotTypes>(newType);
				
				//Shots remaining and the time between shots depends on the Shot Type
				shotsRemaining = timesToShoot / currType;
				timer1 = shootTimer * currType;

				timer2 = breakTimer;
			}
		}
	}

	void EnemyThree::Shoot(float spreadAngle, int bulletCount)
	{
		//Get the direction to the player
		Vector2D dirToPlayer = playerTransform->GetTranslation() - transform->GetTranslation();

		//Get the angle to the player so we can make the bullets look good later
		float angleToPlayer = atan2(dirToPlayer.y, dirToPlayer.x);

		//Get the angle of the first bullet
		float firstAngle = spreadAngle * (static_cast<float>(bulletCount - 1) / 2);

		//Loop through each bullet we have to fire
		for (int i = 0; i < bulletCount; i++)
		{
			//Calculate the angle offset of this bullet + a lil randomness
			float currOffset = firstAngle - (spreadAngle * i) + RandomRange(static_cast<float>(-M_PI / 15.0f), static_cast<float>(M_PI / 15.0f));

			//Create the bullet and set it's stuff
			GameObject* bullet = new GameObject(*bulletArchetype);
			Vector2D dir = Vector2D::FromAngleRadians(angleToPlayer + currOffset);

			static_cast<Transform*>(bullet->GetComponent("Transform"))->SetTranslation(transform->GetTranslation());
			static_cast<Physics*>(bullet->GetComponent("Physics"))->SetVelocity(dir * projectileSpeed);
			static_cast<TimedDeath*>(bullet->GetComponent("TimedDeath"))->SetEnemyBool(true);

			GetOwner()->GetSpace()->GetObjectManager().AddObject(*bullet);

		}
	}
}