//------------------------------------------------------------------------------
//
// File Name:	GameLevel.cpp
// Author(s):	Peter Strizhev, Jakob McFarland
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright � 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameLevel.h"

#include "Archetypes.h"
#include "Health.h"
#include "LoseLevel.h"
#include "Space.h"
#include "Tilemap.h"
#include "Physics.h"
#include "Mesh.h"
#include "Animation.h"
#include "Sprite.h"
#include "Transform.h"
#include "Input.h"
#include "SpriteSource.h"
#include "MeshHelper.h"
#include "Texture.h"
#include "EnemyOne.h"
#include "EnemySpawner.h"
#include <Collider.h>
#include <Graphics.h>
#include <Engine.h>
#include <System.h>
#include "PlayerShooting.h"

namespace Levels
{
	//==================================================================-
	// Public Methods:
	//==================================================================-

	// Creates an instance of GameLevel.
	GameLevel::GameLevel()
		: Level("GameLevel")
		, columnsPlayer(1)
		, rowsPlayer(1)
		, columnsMap(4)
		, rowsMap(3)
		, timer(0)
		, score(0)
	{
	}

	// Load the resources associated with GameLevel.
	void GameLevel::Load()
	{
		std::cout << "GameLevel::Load" << std::endl;

		meshBullet = CreateTriangleMesh(Colors::Red, Colors::Red, Colors::Red);
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(meshBullet));

		texturePlayer = Texture::CreateTextureFromFile("Player.png");
		spriteSourcePlayer = new SpriteSource(columnsPlayer, rowsPlayer, texturePlayer);

		meshPlayer = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5, 0.5));

		meshPool = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		texturePool = Texture::CreateTextureFromFile("AcidPool.png");
		spriteSourcePool = new SpriteSource(1, 1, texturePool);
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateAcidPoolArchetype(meshPool, spriteSourcePool));

		Tilemap* tilemapBuffer = Tilemap::CreateTilemapFromFile("Assets/Levels/GameMap.txt");

		if (tilemapBuffer != nullptr)
		{
			dataMap = tilemapBuffer;
		}
		else
		{
			std::cout << "Error loading map!" << std::endl;
		}

		textureMap = Texture::CreateTextureFromFile("Tilemap.png");
		spriteSourceMap = new SpriteSource(columnsMap, rowsMap, textureMap);

		meshMap = CreateQuadMesh(Vector2D(0.0625f, 0.0833333f), Vector2D(0.5, 0.5));
	}

	// Initialize the memory associated with GameLevel.
	void GameLevel::Initialize()
	{
		std::cout << "GameLevel::Initialize" << std::endl;

		Graphics& graphics = Graphics::GetInstance();
		graphics.SetBackgroundColor(Colors::Grey);
		GameObject* spawner = Archetypes::CreateEnemySpawner();
		enemySpawner = static_cast<Behaviors::EnemySpawner*>(spawner->GetComponent("EnemySpawner"));
		GetSpace()->GetObjectManager().AddObject(*spawner);
		GameObject* map = Archetypes::CreateTilemapObject(meshMap, spriteSourceMap, dataMap);
		GetSpace()->GetObjectManager().AddObject(*map);
		GameObject* beam = Archetypes::CreateLaserBeamObject(meshPlayer);
		GetSpace()->GetObjectManager().AddObject(*beam);
		GameObject* player = Archetypes::CreatePlayer(meshPlayer, spriteSourcePlayer, beam,
			static_cast<Collider*>(map->GetComponent("Collider")));
		playerHealth = static_cast<Behaviors::Health*>(player->GetComponent("Health"));
		playerShooting = static_cast<Behaviors::PlayerShooting*>(player->GetComponent("PlayerShooting"));
		GetSpace()->GetObjectManager().AddObject(*player);
	}

	// Update GameLevel.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void GameLevel::Update(float dt)
	{
		//UNREFERENCED_PARAMETER(dt);

		// The following is made for gameplay testing purposes (can be considered cheat COdes)
		if ( Input::GetInstance().CheckTriggered('1'))
		{
			GetSpace()->SetLevel(new Levels::LoseLevel());
		}

		GameManager(dt);
	}

	// Unload the resources associated with GameLevel.
	void GameLevel::Unload()
	{
		std::cout << "GameLevel::Unload" << std::endl;

		delete meshPlayer;
		delete texturePlayer;
		delete spriteSourcePlayer;

		delete meshBullet;
		delete dataMap;
		delete meshMap;
		delete textureMap;
		delete spriteSourceMap;

		delete meshPool;
		delete texturePool;
		delete spriteSourcePool;
	}

	// Updates Game Variables
	void GameLevel::GameManager(float dt)
	{
		// Timer and damage stuff
		timer += dt;

		health = playerHealth->GetHealth();

		score = static_cast<float>( enemySpawner->GetWave() );

		float maxHeat = playerShooting->GetMaxHeat();

		int damage = playerShooting->GetDamage();

		sprintf_s(windowTitle, titleStringLength, "Time: %.2f :: Score: %.1f :: Health: %d :: Max Heat %.1f :: Laser Damage %d", timer, score, health, maxHeat, damage);

		System::GetInstance().SetWindowTitle(windowTitle);
	}
}
