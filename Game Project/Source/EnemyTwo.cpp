//------------------------------------------------------------------------------
//
// File Name:	EnemyTwo.cpp
// Author(s):	Bar Ben-zvi
// Description: Enemy two slowly lumbers towards the player and spawns an Acid Pool on death. Bouncy!
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "EnemyTwo.h"
#include "Transform.h"
#include "Physics.h"
#include "Collider.h"
#include "ColliderTilemap.h"
#include "Health.h"
#include "GameObject.h"
#include "Space.h"
#include "GameObjectManager.h"

namespace Behaviors
{
	EnemyTwo::EnemyTwo()
		: Component("EnemyTwo"), maxSpeed(100.0f), acceleration(20.0f)
	{
	}

	Component* EnemyTwo::Clone() const
	{
		return new EnemyTwo(*this);
	}

	void EnemyTwoMapCollisionHandler(GameObject& object, const MapCollision& tilemap)
	{
		Physics* physics = static_cast<Physics*>(object.GetComponent("Physics"));

		if (tilemap.bottom)
		{
			physics->SetVelocity(Vector2D(0.0f, 35.0f));
		}
		else if (tilemap.top)
		{
			physics->SetVelocity(Vector2D(0.0f, -35.0f));
		}
		else if (tilemap.left)
		{
			physics->SetVelocity(Vector2D(35.0f, 0.0f));
		}
		else
		{
			physics->SetVelocity(Vector2D(-35.0f, 0.0f));
		}
	}

	void EnemyTwoCollisionHandler(GameObject& owner, GameObject& other)
	{
		if (other.GetName() == "RayPoint")
		{
			Health* health = static_cast<Health*>(owner.GetComponent("Health"));
			health->Subtract(1);
		}
	}

	void EnemyTwo::Initialize()
	{
		Collider* collider = static_cast<Collider*>(GetOwner()->GetComponent("Collider"));
		collider->SetCollisionHandler(EnemyTwoCollisionHandler);
		collider->SetMapCollisionHandler(EnemyTwoMapCollisionHandler);

		transform = static_cast<Transform*>(GetOwner()->GetComponent("Transform"));
		physics = static_cast<Physics*>(GetOwner()->GetComponent("Physics"));
		playerTransform = static_cast<Transform*>(GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("Player")->GetComponent("Transform"));

		acidPool = GetOwner()->GetSpace()->GetObjectManager().GetArchetypeByName("AcidPool");

		static_cast<Health*>(GetOwner()->GetComponent("Health"))->SetToCreate(acidPool);
	}

	void EnemyTwo::Update(float dt)
	{
		ChasePlayer();
		UNREFERENCED_PARAMETER(dt);
	}

	void EnemyTwo::ChasePlayer()
	{
		Vector2D dir = playerTransform->GetTranslation() - transform->GetTranslation();

		dir = dir.Normalized();

		physics->AddForce(dir * acceleration);

		if (physics->GetVelocity().MagnitudeSquared() > maxSpeed * maxSpeed)
		{
			physics->SetVelocity(physics->GetVelocity().Normalized() * maxSpeed);
		}
	}
}