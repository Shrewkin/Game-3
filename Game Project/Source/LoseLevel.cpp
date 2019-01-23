/*
/file   LoseLevel.cpp
/author Jakob McFarland
/date   1/22/2019
/brief

This is the implementation file for all member functions
of the level LoseLevel.

*/

#include "stdafx.h"
#include "LoseLevel.h"

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
#include <Graphics.h>
#include <Engine.h>

namespace Levels
{
	//==================================================================-
	// Public Methods:
	//==================================================================-

	// Creates an instance of LoseLevel.
	LoseLevel::LoseLevel()
		: Level("Screen")
	{
	}

	// Load the resources associated with LoseLevel.
	void LoseLevel::Load()
	{
		std::cout << "LoseLevel::Load" << std::endl;

		textureScreen = Texture::CreateTextureFromFile("EndScreen.png");
		spriteSourceScreen = new SpriteSource(1, 1, textureScreen);

		meshScreen = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5, 0.5));	
	}

	// Initialize the memory associated with LoseLevel.
	void LoseLevel::Initialize()
	{
		std::cout << "LoseLevel::Initialize" << std::endl;

		GameObject* screen = new GameObject("Screen");

		Sprite* sprite = new Sprite();
		sprite->SetMesh(meshScreen);
		sprite->SetSpriteSource(spriteSourceScreen);

		screen->AddComponent(sprite);

		GetSpace()->GetObjectManager().AddObject(*screen);
	}

	// Update LoseLevel.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void LoseLevel::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		//switch back to the game
		if (Input::GetInstance().CheckTriggered(VK_RETURN))
		{
			GetSpace()->SetLevel( new GameLevel() );
		}

		//quit
		if (Input::GetInstance().CheckTriggered(VK_ESCAPE))
		{
			Engine::GetInstance().Stop();
		}
	}

	// Unload the resources associated with LoseLevel.
	void LoseLevel::Unload()
	{
		std::cout << "LoseLevel::Unload" << std::endl;

		delete meshScreen;
		delete textureScreen;
		delete spriteSourceScreen;
	}
}