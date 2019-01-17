//------------------------------------------------------------------------------
//
// File Name:	EnemySpawner.h
// Author(s):	Bar Ben-zvi
// Description: Spawns waves of enemies
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Vector2D.h"
#include "Component.h"

class Transform;

namespace Behaviors
{
	class EnemySpawner : public Component
	{
	public:

		EnemySpawner();

		Component* Clone() const;

		void Initialize() override;

		void Update(float dt) override;

	private:

		void SpawnWave(int wave);

		Vector2D spawnPos;
		int baseSpawnCount;


	};
}