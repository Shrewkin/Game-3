//------------------------------------------------------------------------------
//
// File Name:	Level2.h
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

		unsigned columnsPlayer;
		unsigned rowsPlayer;

		// Tilemap
		Tilemap* dataMap;
		Texture* textureMap;
		SpriteSource* spriteSourceMap;
		Mesh* meshMap;

		unsigned columnsMap;
		unsigned rowsMap;

		// Game Manager Data
		float timer;
		int score;
		// Amount of damage that the weapon currently deals to each enemy it comes in contact with.
		// Current Damage will change with the more upgrades that the player has.
		int currentDamage;
		int damageDealt;
	};
}

//----------------------------------------------------------------------------
