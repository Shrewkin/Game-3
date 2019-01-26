//------------------------------------------------------------------------------
//
// File Name:	GameLevel.h
// Author(s):	Jeremy Kings (j.kings)
// Project:		BetaFramework
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

//------------------------------------------------------------------------------
// Include Files:
//------------------------------------------------------------------------------

#include "Vector2D.h"
#include "Level.h"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward References:
//------------------------------------------------------------------------------

class Texture;
class Mesh;
class SpriteSource;
class GameObject;
class Tilemap;

namespace Behaviors
{
	class Health;
	class EnemySpawner;
	class PlayerShooting;
}

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Levels
{
	class GameLevel : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of Level 2.
		GameLevel();

		// Load the resources associated with Level 2.
		void Load() override;

		// Initialize the memory associated with Level 2.
		void Initialize() override;

		// Update Level 2.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with Level 2.
		void Unload() override;

		void GameManager(float dt);

	private:

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		// Monkey
		Mesh* meshPlayer;
		Texture* texturePlayer;
		SpriteSource* spriteSourcePlayer;

		// Bullet
		Mesh* meshBullet;

		unsigned columnsPlayer;
		unsigned rowsPlayer;

		//Acid Pool
		Mesh* meshPool;
		Texture* texturePool;
		SpriteSource* spriteSourcePool;

		// Tilemap
		Tilemap* dataMap;
		Texture* textureMap;
		SpriteSource* spriteSourceMap;
		Mesh* meshMap;


		unsigned columnsMap;
		unsigned rowsMap;

		// Game Manager Data
		Behaviors::Health* playerHealth;
		Behaviors::EnemySpawner* enemySpawner;
		Behaviors::PlayerShooting* playerShooting;
		int counter;
		float timer;
		float score;
		int health;

		// Title
		static const unsigned titleStringLength = 100;
		char windowTitle[titleStringLength];
	};
}

//----------------------------------------------------------------------------
