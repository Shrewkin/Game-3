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
class Mesh;

namespace Behaviors
{
	class EnemySpawner : public Component
	{
	public:

		EnemySpawner();

		~EnemySpawner();

		Component* Clone() const;

		void Initialize() override;

		void Update(float dt) override;

		unsigned getToSpawn();

		unsigned GetWave() const;

	private:

		void SpawnWave();
		void SpawnEnemy();

		//Spawn stuff
		Vector2D spawnPos;
		unsigned baseSpawnCount;
		float randSpawnOffset;
		float spawnTimer;
		std::vector<int> spawnChance; //I couldn't think of another name for this, but it's used to choose enemy types based on the wave
						//(used when we add more enemies)
		unsigned toSpawn;

		//Enemy Archetypes
		GameObject* enemy1;

		//Wave stuff
		int currWave;
		int waveCountModifier;
		float waveTimer;

		//Timer stuff
		float timer1; //spawnTimer
		float timer2; //waveTimer

		//Enemy meshes
		Mesh* enemy1Mesh;


	};
}