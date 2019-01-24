//------------------------------------------------------------------------------
//
// File Name:	EnemyOne.cpp
// Author(s):	Bar Ben-zvi
// Description: Enemy one attempts to stay at a specified distance from the player and fire at the player
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "EnemyOne.h"
#include "GameObject.h"
#include "Physics.h"
#include "Transform.h"
#include <Collider.h>
#include <ColliderTilemap.h>
#include <GameObjectManager.h>
#include <Space.h>
#include "Health.h"
#include "TimedDeath.h"

namespace Behaviors
{
	EnemyOne::EnemyOne(float fireRate, float walkSpeed, float runSpeed, float projectileSpeed, float dist)
		: Component("EnemyOne"), currState(StateRunTowards), nextState(StateRunTowards), innerState(InnerStateEnter), 
		  shootTimer(fireRate), stateChangeTime(0.2f), timer1(fireRate), timer2(1.0f), walkSpeed(walkSpeed), 
		  runSpeed(runSpeed), projectileSpeed(projectileSpeed), wantedDist(dist)
	{
	}

	Component* EnemyOne::Clone() const
	{
		return new EnemyOne(*this);
	}

	void EnemyMapCollisionHandler(GameObject& object, const MapCollision& tilemap)
	{
		if (tilemap.left || tilemap.right)
		{
			//Do stuff here later
			UNREFERENCED_PARAMETER(object);
		}
	}

	void EnemyCollisionHandler(GameObject& owner, GameObject& other)
	{
		if (other.GetName() == "RayPoint")
		{
			static_cast<Health*>(owner.GetComponent("Health"))->Subtract(1);
		}

		if (other.GetName() == "Bullet" && !static_cast<TimedDeath*>(other.GetComponent("TimedDeath"))->GetEnemyBool())
		{
			static_cast<Health*>(owner.GetComponent("Health"))->Subtract(1);
			other.Destroy();
		}
	}

	void EnemyOne::Initialize()
	{
		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
		playerTransform = static_cast<Transform*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("Player")->GetComponent("Transform"));

		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetMapCollisionHandler(EnemyMapCollisionHandler);
		static_cast<Collider*>(GetOwner()->GetComponent("Collider"))->SetCollisionHandler(EnemyCollisionHandler);

		projectile = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("Bullet");
	}

	void EnemyOne::Update(float dt)
	{
		float dist = (transform->GetTranslation().Distance(playerTransform->GetTranslation()));
		timer2 -= dt;

		switch (currState)
		{
			case StateRunAway:
			{
				switch (innerState)
				{
				case InnerStateEnter:
					innerState = InnerStateUpdate;
					break;
					
				case InnerStateUpdate:
					RunFromPlayer();

					if (timer2 <= 0)
					{
						if (dist > wantedDist)
						{
							innerState = InnerStateExit;
							nextState = StateRunTowards;
						}

						timer2 = stateChangeTime;
					}
					break;

				case InnerStateExit:
					innerState = InnerStateEnter;
					currState = nextState;
					break;
				}
				break;
			}

			case StateRunTowards:
			{
				switch (innerState)
				{
				case InnerStateEnter:
					innerState = InnerStateUpdate;
					break;

				case InnerStateUpdate:
					if (dist > wantedDist)
					{
						ChasePlayer(runSpeed);
					}
					else if (dist < wantedDist)
					{
						timer1 -= dt;
						ChasePlayer(walkSpeed);
						if (timer1 <= 0)
						{
							FireAtPlayer();
						}
					}

					if (timer2 <= 0)
					{
						if (dist < wantedDist / 2)
						{
							innerState = InnerStateExit;
							nextState = StateRunAway;
						}
						timer2 = stateChangeTime;
					}
					break;

				case InnerStateExit:
					innerState = InnerStateEnter;
					currState = nextState;
				}
			}
			break;

		}
	}

	void EnemyOne::ChasePlayer(float speed)
	{
		Vector2D dir = playerTransform->GetTranslation() - transform->GetTranslation();
		dir = dir.Normalized();

		physics->SetVelocity(dir * speed);
	}

	void EnemyOne::RunFromPlayer()
	{
		Vector2D dir = playerTransform->GetTranslation() - transform->GetTranslation();

		dir = -dir.Normalized();

		physics->SetVelocity(dir * runSpeed);
	}

	void EnemyOne::FireAtPlayer()
	{
		GameObject* bullet = new GameObject(*projectile);

		Vector2D dir = (playerTransform->GetTranslation() - transform->GetTranslation()).Normalized();
		Transform* bulletTransform = static_cast<Transform*>(bullet->GetComponent("Transform"));
		Physics* bulletPhysics = static_cast<Physics*>(bullet->GetComponent("Physics"));

		bulletTransform->SetTranslation(transform->GetTranslation() + dir * transform->GetScale().x / 2);
		bulletTransform->SetRotation(atan2(dir.y, dir.x));
		bulletPhysics->SetVelocity(dir * projectileSpeed);
		
		static_cast<TimedDeath*>(bullet->GetComponent("TimedDeath"))->SetEnemyBool(true);

		GetOwner()->GetSpace()->GetObjectManager().AddObject(*bullet);

		timer1 = shootTimer;


	}

}