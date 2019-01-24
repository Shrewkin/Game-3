//------------------------------------------------------------------------------
//
// File Name:	EnemySpawner.cpp
// Author(s):	Bar Ben-zvi
// Description: Spawns waves of enemies
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "EnemySpawner.h"
#include "Archetypes.h"
#include <GameObject.h>
#include <Space.h>
#include <GameObjectManager.h>
#include "Transform.h"
#include <Random.h>
#include <MeshHelper.h>
#include <MeshFactory.h>
#include <Mesh.h>

namespace Behaviors
{
	EnemySpawner::EnemySpawner()
		: Component("EnemySpawner")
		, spawnPos(300.0f, 200.0f)
		, baseSpawnCount(2)
		, randSpawnOffset(25.0f)
		, spawnTimer(0.5f)
		, spawnChance(1)
		, toSpawn(0)
		, currWave(0)
		, waveCountModifier(2)
		, waveTimer(5.0f)
		, timer1(0.3f)
		, timer2(5.0f)
	{
	}

	EnemySpawner::~EnemySpawner()
	{
		delete enemy1Mesh;
	}

	Component* EnemySpawner::Clone() const
	{
		return new EnemySpawner(*this);
	}

	void EnemySpawner::Initialize()
	{
		enemy1Mesh = CreateQuadMesh(Vector2D(50.0f, 50.0f), Vector2D(0.5f, 0.5f));
	}

	void EnemySpawner::Update(float dt)
	{
		unsigned currCount = GetOwner()->GetSpace()->GetObjectManager().GetObjectCount("Enemy");
		//std::cout << currCount << std::endl;

		if (currCount == 0 && toSpawn == 0)
		{
			
			timer2 -= dt;
			if (timer2 <= 0.0f)
			{
				SpawnWave();
				timer2 = waveTimer;
			}
		}
		else if (toSpawn != 0)
		{
			timer1 -= dt;
			if (timer1 <= 0.0f)
			{
				SpawnEnemy();
				timer1 = spawnTimer;
			}
		}

	}

	unsigned EnemySpawner::getToSpawn()
	{
		return toSpawn;
	}

	void EnemySpawner::SpawnWave()
	{
		++currWave;
		toSpawn = baseSpawnCount + ((currWave - (currWave % waveCountModifier)) / waveCountModifier);
		
		spawnChance.clear();

		if (currWave < 3)
		{
			spawnChance.push_back(1);
		}
		else if (currWave < 5)
		{
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
		}
		else
		{
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(3);
		}
	}

	void EnemySpawner::SpawnEnemy()
	{
		//spawnPos starts at top right corner
		Vector2D enemyPos = spawnPos;

		//0 == top left
		//1 == top right
		//2 == bottom left
		//3 == bottom right
		int randPosNum = RandomRange(0, 3);

		if (randPosNum == 0)
		{
			enemyPos.x = -enemyPos.x;
		}
		else if (randPosNum == 2)
		{
			enemyPos.x = -enemyPos.x;
			enemyPos.y = -enemyPos.y;
		}
		else if (randPosNum == 3)
		{
			enemyPos.y = -enemyPos.y;
		}

		//Add a random offset
		enemyPos += Vector2D(RandomRange(-randSpawnOffset, randSpawnOffset), RandomRange(-randSpawnOffset, randSpawnOffset));

		//Generate a random num for enemy spawn (used when we have more enemy types)
		int randSpawn = spawnChance[RandomRange(0, static_cast<int>(spawnChance.size() - 1))];

		if (randSpawn == 1)
		{
			GameObject* enemy = Archetypes::CreateEnemyOneObject(enemy1Mesh, enemyPos);
			GetOwner()->GetSpace()->GetObjectManager().AddObject(*enemy);
		}
		else if (randSpawn == 2)
		{
			GameObject* enemy = Archetypes::CreateEnemyTwoObject(enemy1Mesh, enemyPos);
			GetOwner()->GetSpace()->GetObjectManager().AddObject(*enemy);
		}
		else if(randSpawn == 3)
		{
			GameObject* enemy = Archetypes::CreateEnemyThreeObject(enemy1Mesh, enemyPos);
			GetOwner()->GetSpace()->GetObjectManager().AddObject(*enemy);
		}

		--toSpawn;
	}
}