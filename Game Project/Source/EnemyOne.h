//------------------------------------------------------------------------------
//
// File Name:	EnemyOne.h
// Author(s):	Bar Ben-zvi
// Description: Enemy one attempts to stay at a specified distance from the player and fire at the player
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Component.h"
#include <Vector2D.h>

struct MapCollision;
class Transform;
class Physics;


namespace Behaviors
{

	enum InnerStates
	{
		InnerStateEnter,
		InnerStateUpdate,
		InnerStateExit
	};

	enum EnemyStates
	{
		StateRunAway,
		StateRunTowards
	};

	class EnemyOne : public Component
	{
	public:

		//Constructor for enemy one
		EnemyOne(float fireRate = 1.0f, float walkSpeed = 100.0f, float runSpeed = 200.0f, float projectileSpeed = 150.0f, float dist = 10.0f);

		//Clones this component
		Component* Clone() const;

		//Initializes this component
		void Initialize() override;

		//Updates this component
		void Update(float dt) override;

		//Handles collision between the enemy and the tilemap
		friend void EnemyMapCollisionHandler(GameObject& object, const MapCollision& tilemap);

		//Handles collision between the enemy and another object
		friend void EnemyCollisionHandler(GameObject& owner, GameObject& other);

	private:

		//Chases the player
		void ChasePlayer(float speed);

		//Runs away from the player
		void RunFromPlayer();

		//Fires a projectile at the player
		void FireAtPlayer();

		//States
		unsigned currState;
		unsigned nextState;
		unsigned innerState;
		
		//Components
		Transform* transform;
		Transform* playerTransform;
		Physics* physics;

		//Timer related stuff
		float shootTimer;
		float stateChangeTime;
		float timer1; //Used for shoot timer
		float timer2; //Used for state change time

		//Game related variables
		float walkSpeed;
		float runSpeed;
		GameObject* projectile; //The projectile we fire
		float projectileSpeed;
		float wantedDist; //The distance we want to be from the player, if we are too close to the player (dist < wantedDist / 2)
						 //we run away from the player


	};
}