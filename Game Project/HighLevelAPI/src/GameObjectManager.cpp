//==================================================================-
/*
/file  GameObjectManager.cpp
/author Jakob McFarland
/date   11/15/2018
/brief

This is the implementation file for all member functions
of the class GameObjectManager, as specified in specification
file GameObjectManager.h.

*/
//==================================================================-

#include "stdafx.h"
#include "GameObjectManager.h"

#include "Space.h"
#include "Collider.h"

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Constructor(s)
GameObjectManager::GameObjectManager(Space* space)
	: BetaObject("GameObjectManager", space), numObjects(0), numArchetypes(0),
	fixedUpdateDt(60.0f), timeAccumulator(0.0f)
{
}

// Destructor
GameObjectManager::~GameObjectManager()
{
	Shutdown();
	Unload();
}

// Update all objects in the active game objects list.
// Params:
//	 dt = Change in time (in seconds) since the last game loop.
void GameObjectManager::Update(float dt) 
{
	if (!static_cast<Space*>(GetParent())->IsPaused())
	{
		VariableUpdate(dt);
		FixedUpdate(dt);
		CheckCollisions();
	}

	DestroyObjects();
	Draw();
}

// Shutdown the game object manager, destroying all active objects.
void GameObjectManager::Shutdown(void)
{
	for (unsigned i = 0; i < numObjects; ++i)
	{
		delete gameObjectActiveList[i];
	}

	numObjects = 0;
}

// Unload the game object manager, destroying all object archetypes.
void GameObjectManager::Unload(void)
{
	for (unsigned i = 0; i < numObjects; ++i)
	{
		gameObjectActiveList[i]->Unload();
	}

	for (unsigned i = 0; i < numArchetypes; ++i)
	{
		delete gameObjectArchetypes[i];
	}

	numArchetypes = 0;
}

// Add a game object to the active game object list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddObject(GameObject& gameObject)
{
	if (numObjects < maxObjects)
	{
		gameObject.SetParent(GetParent());
		gameObject.Initialize();
		gameObjectActiveList[numObjects] = &gameObject;
		++numObjects;
	}
}

// Add a game object to the game object archetype list.
// Params:
//	 gameObject = Reference to the game object to be added to the list.
void GameObjectManager::AddArchetype(GameObject& gameObject)
{
	if (numArchetypes < maxArchetypes)
	{
		gameObjectArchetypes[numArchetypes] = &gameObject;
		++numArchetypes;
	}
}

// Returns a pointer to the first active game object matching the specified name.
// Params:
//	 objectName = The name of the object to be returned, if found.
// Returns:
//   If the named object is found,
//	   then return the pointer to the named game object,
//	   else return nullptr.
GameObject* GameObjectManager::GetObjectByName(const std::string& objectName) const
{
	for (unsigned i = 0; i < numObjects; ++i)
	{
		if ( gameObjectActiveList[i]->GetName()._Equal(objectName) )
		{
			return gameObjectActiveList[i];
		}
	}
	return nullptr;
}

// Returns a pointer to the first game object archetype matching the specified name.
// Params:
//	 objectName = The name of the archetype to be returned, if found.
// Returns:
//   If the named archetype is found,
//	   then return the pointer to the named game object archetype,
//	   else return nullptr.
GameObject* GameObjectManager::GetArchetypeByName(const std::string& objectName) const
{
	for (unsigned i = 0; i < numArchetypes; ++i)
	{
		if ( gameObjectArchetypes[i]->GetName()._Equal( objectName ) ) 
		{
			return gameObjectArchetypes[i];
		}
	}
	return nullptr;
}

// Returns the number of active objects with the given name.
// Params:
//   objectName = The name of the objects that should be counted.
unsigned GameObjectManager::GetObjectCount(const std::string& objectName) const
{
	unsigned total = 0;

	for (unsigned i = 0; i < numObjects; ++i)
	{
		if (gameObjectActiveList[i]->GetName() == objectName)
		{
			++total;
		}
	}

	return total;
}

//------------------------------------------------------------------------------
// Private Functions:
//------------------------------------------------------------------------------

// Update object logic using variable timestep.
void GameObjectManager::VariableUpdate(float dt)
{
	for (unsigned i = 0; i < numObjects; ++i)
	{
		gameObjectActiveList[i]->Update(dt);
	}
}

// Update object physics using fixed timestep.
void GameObjectManager::FixedUpdate(float dt)
{
	timeAccumulator += dt;

	//call the fixed update for as many times as it fits into dt
	while (timeAccumulator >= dt)
	{
		for (unsigned i = 0; i < numObjects; ++i)
		{
			gameObjectActiveList[i]->FixedUpdate(1/fixedUpdateDt);
		}

		timeAccumulator -= 1/fixedUpdateDt;
	}	
}

// Destroy any objects marked for destruction.
void GameObjectManager::DestroyObjects()
{
	//foreach game object
	for (unsigned i = 0; i < numObjects; )
	{
		//check if destroyed
		if (gameObjectActiveList[i]->IsDestroyed())
		{
			//destroy it
			delete gameObjectActiveList[i];

			//and shrink the list by one
			--numObjects;

			//numObjects is now the last index, set i to last index 
			gameObjectActiveList[i] = gameObjectActiveList[numObjects];
			gameObjectActiveList[numObjects] = nullptr;		
		}
		else
		{
			++i;
		}
	}
}

// Draw all game objects in the active game object list.
void GameObjectManager::Draw(void)
{
	//draw each game object
	for (unsigned i = 0; i < numObjects; ++i)
	{
		gameObjectActiveList[i]->Draw();
	}
}

// Check for collisions between each pair of objects
void GameObjectManager::CheckCollisions(void)
{
	//foreach game object
	for (unsigned i = 0; i < numObjects; ++i)
	{
		if( gameObjectActiveList[i]->IsDestroyed())
		{
			continue;
		}

		Collider* collider = static_cast<Collider*>( gameObjectActiveList[i]->GetComponent("Collider") );

		if (collider == nullptr)
		{
			continue;
		}

		for (unsigned j = i + 1; j < numObjects; ++j)
		{
			if (gameObjectActiveList[j]->IsDestroyed())
			{
				continue;
			}

			Collider* otherCollider = static_cast<Collider*>(gameObjectActiveList[j]->GetComponent("Collider"));

			if (otherCollider == nullptr)
			{
				continue;
			}

			collider->CheckCollision(*otherCollider);
		}
	}
}