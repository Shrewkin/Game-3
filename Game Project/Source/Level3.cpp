//==================================================================-
/*
/file   Level3.cpp
/author Jakob McFarland
/date   11/15/2018
/brief

This is the implementation file for all member functions
of the class Level3, as specified in specification
file Level3.h.

*/
//==================================================================-

#include "stdafx.h"
#include "Level3.h"

#include "Space.h"
#include "GameObjectManager.h"
#include "Archetypes.h"
#include "Physics.h"
#include "Transform.h"

#include "Mesh.h"
#include "MeshHelper.h"
#include "SpriteSource.h"
#include "Texture.h"
#include "Graphics.h"

#include "Input.h"
#include "Level1.h"
#include "Level2.h"

namespace Levels
{

	//------------------------------------------------------------------------------
	// Public Functions:
	//------------------------------------------------------------------------------

	// Creates an instance of Level 3.
	Level3::Level3()
		: Level("Level3"), circleSpeed(50.0f), pointSpeed(75.0f)
	{
	}

	// Load the resources associated with Level 3.
	void Level3::Load()
	{
		meshQuad = CreateQuadMesh(Vector2D(1.0f, 1.0f), Vector2D(0.5f, 0.5f));
		textureCircle = Texture::CreateTextureFromFile("Circle.png");
		spriteSourceCircle = new SpriteSource(1, 1, textureCircle);
	}

	// Initialize the memory associated with Level 3.
	void Level3::Initialize()
	{
		GetSpace()->GetObjectManager().AddObject( *Archetypes::CreateCircle(meshQuad, spriteSourceCircle));

		GameObject* point1 = Archetypes::CreatePoint(meshQuad, spriteSourceCircle);
		static_cast<Transform*>(point1->GetComponent("Transform"))->SetTranslation(Vector2D(-200.0f, 200.0f));
		GetSpace()->GetObjectManager().AddObject(*point1);

		GameObject* rect1 = Archetypes::CreateRectangle(meshQuad);
		static_cast<Transform*>(rect1->GetComponent("Transform"))->SetTranslation(Vector2D(200.0f, -200.0f));
		GetSpace()->GetObjectManager().AddObject(*rect1);

		GameObject* point2 = Archetypes::CreatePoint(meshQuad, spriteSourceCircle);
		static_cast<Physics*>(point2->GetComponent("Physics"))->SetVelocity(Vector2D(0.0f, -1.0f * pointSpeed));
		GetSpace()->GetObjectManager().AddObject( *point2 );

		GameObject* rect2 = Archetypes::CreateRectangle(meshQuad);
		const BoundingRectangle& screen = Graphics::GetInstance().GetScreenWorldDimensions();
		static_cast<Transform*>(rect2->GetComponent("Transform"))->SetTranslation( Vector2D(screen.left, screen.top) );
		static_cast<Physics*>(rect2->GetComponent("Physics"))->SetVelocity(Vector2D(circleSpeed, -1.0f * circleSpeed));
		GetSpace()->GetObjectManager().AddObject(*rect2);
	}

	// Update Level 3.
	// Params:
	//	 dt = Change in time (in seconds) since the last game loop.
	void Level3::Update(float dt)
	{
		UNREFERENCED_PARAMETER(dt);

		if (Input::GetInstance().CheckTriggered('1'))
		{
			GetSpace()->SetLevel(new Level1());
		}
		else if (Input::GetInstance().CheckTriggered('2'))
		{
			GetSpace()->SetLevel(new Level2());
		}
		else if (Input::GetInstance().CheckTriggered('3'))
		{
			GetSpace()->RestartLevel();
		}
	}

	// Unload the resources associated with Level 3.
	void Level3::Unload()
	{
		delete meshQuad;
		delete textureCircle;
		delete spriteSourceCircle;
	}
}