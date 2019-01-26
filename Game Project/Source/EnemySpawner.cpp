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
#include "Health.h"
#include "PlayerShooting.h"

namespace Behaviors
{
	EnemySpawner::EnemySpawner()
		: Component("EnemySpawner")
		, spawnPos(300.0f, 200.0f)
		, baseSpawnCount(2)
		, randSpawnOffset(15.0f)
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


		//If we aren't spawning stuff anymore we're on break
		if (currCount == 0 && toSpawn == 0)
		{
			if (!upgraded)
			{
				if ((currWave + 1) % 10 == 0)
				{
					GameObject* player = GetOwner()->GetSpace()->GetObjectManager().GetObjectByName("Player");

					Health* playerHealth = static_cast<Health*>(player->GetComponent("Health"));

					playerHealth->Add(playerHealth->GetMaxHealth() - playerHealth->GetHealth());

					if (currWave == 9)
					{
						static_cast<PlayerShooting*>(player->GetComponent("PlayerShooting"))->IncreaseDamage(1);
					}
					else if (currWave == 19)
					{
						static_cast<PlayerShooting*>(player->GetComponent("PlayerShooting"))->ScaleMaxHeat(2.0f);
					}
				}

				upgraded = true;
			}

			timer2 -= dt;
			if (timer2 <= 0.0f)
			{
				SpawnWave();
				timer2 = waveTimer;
			}
		}
		//Otherwise, we are spawning stuff
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

	unsigned EnemySpawner::GetWave() const
	{
		return currWave;
	}

	void EnemySpawner::SpawnWave()
	{
		++currWave;
		//Calculate the amount of enemies to spawn this wave
		toSpawn = baseSpawnCount + ((currWave - (currWave % waveCountModifier)) / waveCountModifier);
		
		upgraded = false;

		//Based on the current wave, set the spawnChance vector
		spawnChance.clear();

		if (currWave % 10 == 0)
		{

			if (currWave == 10)
			{
				spawnChance.push_back(2);
			}
			else if (currWave == 20)
			{
				spawnChance.push_back(1);
			}
			else
			{
				spawnChance.push_back(2);
				spawnChance.push_back(2);
				spawnChance.push_back(2);
				spawnChance.push_back(2);
				spawnChance.push_back(3);
			}
		}
		else if (currWave == 15)
		{
			spawnChance.push_back(3);
		}
		else if (currWave < 3)
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
		else if (currWave < 10)
		{
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(3);
		}
		else
		{
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(1);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(2);
			spawnChance.push_back(3);
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

		//Select a random index in our spawnChance vector to spawn a random enemy
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