//------------------------------------------------------------------------------
//
// File Name:	EnemyTwo.cpp
// Author(s):	Bar Ben-zvi
// Description: Enemy two slowly lumbers towards the player and spawns an Acid Pool on death
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
struct MapCollision;
class Transform;
class Physics;
class Texture;
class SpriteSource;
class Mesh;

namespace Behaviors
{
	class EnemyTwo : public Component
	{
	public:

		EnemyTwo();

		Component* Clone() const;

		void Initialize() override;

		//Updates this component
		void Update(float dt) override;

		//Handles collision between the enemy and the tilemap
		friend void EnemyMapCollisionHandler(GameObject& object, const MapCollision& tilemap);

		//Handles collision between the enemy and another object
		friend void EnemyCollisionHandler(GameObject& owner, GameObject& other);

	private:

		//Chases the player
		void ChasePlayer();


		//Components
		Transform* transform;
		Transform* playerTransform;
		Physics* physics;

		//Movement stuff
		float maxSpeed;
		float acceleration;

		//Acid pool stuff
		GameObject* acidPool;


	};
}
