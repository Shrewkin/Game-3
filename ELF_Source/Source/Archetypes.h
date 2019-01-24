//------------------------------------------------------------------------------
//
// File Name:	Archetypes.h
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

#include <Vector2D.h>

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Forward Declarations:
//------------------------------------------------------------------------------

class GameObject;
class SpriteSource;
class Mesh;
class Tilemap;
class Collider;

//------------------------------------------------------------------------------
// Public Structures:
//------------------------------------------------------------------------------

namespace Archetypes
{
	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------
		
	// Create the ship game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateShip(Mesh* mesh);

	// Create the archetype for the bullet object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateBulletArchetype(Mesh* mesh);

	// Create the monkey game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject * CreateMonkey(Mesh * mesh, SpriteSource * spriteSource);

	// Create the circle game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateCircle(Mesh* mesh, SpriteSource* spriteSource);

	// Create the point game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//   spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreatePoint(Mesh* mesh, SpriteSource* spriteSource);

	// Create the rectangle game object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateRectangle(Mesh* mesh);
	
	// Create a tilemap object
	// Params:
	//   mesh = The mesh to use for the sprite.
	//   spriteSource = The sprite source to use for the sprite.
	//   map = The map to use for tilemap related components.
	// Returns:
	//   A pointer to the newly constructed game object.
	GameObject* CreateTilemapObject(Mesh* mesh, SpriteSource* spriteSource, Tilemap* map);

	// Create a game object archetype that uses the Asteroid texture.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreatePlayer(Mesh* mesh, SpriteSource* spriteSource, GameObject* beam, Collider* map);
	

	//Creates and returns an Enemy Spawner game object that will handle spawning waves
	GameObject* CreateEnemySpawner();

	// Create an enemy one object
	// Params:
	//   mesh = The mesh to use for the sprite.
	//	 spawnPos = the position this enemy will be spawned at
	// Returns:
	//   A pointer to the newly constructed game object.
	GameObject* CreateEnemyOneObject(Mesh* mesh, Vector2D spawnPos);

	// Create an enemy two object
	// Params:
	//   mesh = The mesh to use for the sprite.
	//	 spawnPos = the position this enemy will be spawned at
	// Returns:
	//   A pointer to the newly constructed game object.
	GameObject* CreateEnemyTwoObject(Mesh * mesh, Vector2D spawnPos);

	// Create an enemy three object
	// Params:
	//   mesh = The mesh to use for the sprite.
	//	 spawnPos = the position this enemy will be spawned at
	// Returns:
	//   A pointer to the newly constructed game object.
	GameObject* CreateEnemyThreeObject(Mesh* mesh, Vector2D spawnPos);


	// Create the laser beams object.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//	 spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateLaserBeamObject(Mesh* mesh);

	// Create Acid Pool archetype.
	// Params:
	//   mesh  = The mesh to use for the object's sprite.
	//	 spriteSource = The sprite source to use for the object.
	// Returns:
	//	 A pointer to the newly constructed game object
	GameObject* CreateAcidPoolArchetype(Mesh* mesh, SpriteSource* spriteSource);
	
}

//----------------------------------------------------------------------------
