/*
/file   Loselevel.h
/author Jakob McFarland
/date   1/22/2019
/brief

This is the specification file for all member functions
of the level LoseLevel.

*/

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
	class LoseLevel : public Level
	{
	public:
		//------------------------------------------------------------------------------
		// Public Functions:
		//------------------------------------------------------------------------------

		// Creates an instance of LoseLevel.
		LoseLevel();

		// Load the resources associated with LoseLevel.
		void Load() override;

		// Initialize the memory associated with LoseLevel.
		void Initialize() override;

		// Update LoseLevel.
		// Params:
		//	 dt = Change in time (in seconds) since the last game loop.
		void Update(float dt) override;

		// Unload the resources associated with LoseLevel.
		void Unload() override;

	private:

		//------------------------------------------------------------------------------
		// Private Variables:
		//------------------------------------------------------------------------------

		//screen
		Mesh* meshScreen;
		Texture* textureScreen;
		SpriteSource* spriteSourceScreen;
	};
}

//----------------------------------------------------------------------------
