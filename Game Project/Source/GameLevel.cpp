//------------------------------------------------------------------------------
//
// File Name:	GameLevel.cpp
// Author(s):	Peter Strizhev
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "GameLevel.h"

#include "Archetypes.h"
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
#include <Graphics.h>
#include <Engine.h>

namespace Levels
{
	//==================================================================-
	// Public Methods:
	//==================================================================-

	// Creates an instance of Level 2.
	GameLevel::GameLevel()
		: Level("Level2")
		, columnsPlayer(1)
		, rowsPlayer(1)
		, columnsMap(4)
		, rowsMap(3)
		, timer(0)
		, score(0)
		// When weapons are implemented and we merge the branches, multiply a modifier by the amount currently being dealt
		, currentDamage(100)
		, damageDealt(0)
	{
	}

	// Load the resources associated with Level 2.
	void GameLevel::Load()
	{
		std::cout << "Level2::Load" << std::endl;

		meshBullet = CreateTriangleMesh(Colors::Red, Colors::Red, Colors::Red);
		GetSpace()->GetObjectManager().AddArchetype(*Archetypes::CreateBulletArchetype(meshBullet));

		texturePlayer = Texture::CreateTextureFromFile("Player.png");
		spriteSourcePlayer = new SpriteSource(columnsPlayer, rowsPlayer, texturePlayer);

		meshPlayer = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5, 0.5));

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

	// Initialize the memory associated with Level 2.
	void GameLevel::Initialize()
	{
		std::cout << "Level2::Initialize" << std::endl;

		Graphics& graphics = Graphics::GetInstance();
		graphics.SetBackgroundColor(Colors::Grey);
		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateEnemySpawner());
		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreatePlayer(meshPlayer, spriteSourcePlayer));
		GetSpace()->GetObjectManager().AddObject(*Archetypes::CreateTilemapObject(meshMap, spriteSourceMap, dataMap));
	}

	// Update Level 2.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void GameLevel::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		// The following is made for gameplay testing purposes (can be considered cheat COdes)
		//if (Input::GetInstance().CheckTriggered('1'))
		//{
		//
		//}

		GameManager(dt);
	}

	// Unload the resources associated with Level 2.
	void GameLevel::Unload()
	{
		std::cout << "Level2::Unload" << std::endl;

		delete meshPlayer;
		delete texturePlayer;
		delete spriteSourcePlayer;

		delete meshBullet;
		delete dataMap;
		delete meshMap;
		delete textureMap;
		delete spriteSourceMap;
	}

	// Updates Game Variables
	void GameLevel::GameManager(float dt)
	{
		timer += dt;
	}
}