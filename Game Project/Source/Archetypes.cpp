//==================================================================-
/*
/file   Archetypes.cpp
/author Jakob McFarland
/date   1/23/2018
/brief

This is the implementation file for all member functions
of the class Archetypes, as specified in specification
file Archetypes.h.

*/
//==================================================================-

#include "stdafx.h"
#include "Archetypes.h"

#include "TimedDeath.h"
#include "Collider.h"
#include "ColliderPoint.h"
#include "ColliderCircle.h"
#include "ColliderRectangle.h"
#include "ColliderTilemap.h"
#include "PlayerMovement.h"
#include "Space.h"
#include <Input.h>
#include <System.h>
///#include "GameObjectFactory.h"
#include "Sprite.h"
#include "SpriteTilemap.h"
#include "SpriteSource.h"
#include <Graphics.h>
#include "Physics.h"
#include "Transform.h"
#include "TileMap.h"
#include "EnemyOne.h"
#include "EnemySpawner.h"
#include "PlayerShooting.h"
#include "Health.h"
#include "EnemyThree.h"
#include "EnemyTwo.h"


//==================================================================-
// Public Functions:
//==================================================================-

// Create a game object archetype that uses the Bullet texture.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreateBulletArchetype(Mesh* mesh)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(14.0f, 14.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);

	Physics* physics = new Physics();
	Behaviors::TimedDeath* timedDeath = new Behaviors::TimedDeath(5.0f);

	ColliderCircle* colliderCircle = new ColliderCircle(transform->GetScale().x * 0.5f);

	//create object add all the components
	GameObject* bullet = new GameObject("Bullet");
	bullet->AddComponent(transform);
	bullet->AddComponent(physics);
	bullet->AddComponent(sprite);
	bullet->AddComponent(colliderCircle);
	bullet->AddComponent(timedDeath);

	//GameObjectFactory::GetInstance().SaveObjectToFile(bullet);

	return bullet;
}


GameObject * Archetypes::CreateTilemapObject(Mesh * mesh, SpriteSource * spriteSource, Tilemap * map)
{
	//initilize all components
	Transform* transform = new Transform(-366.5f, 281.0f);
	transform->SetScale(Vector2D(50.0f, 50.0f));

	SpriteTilemap* spriteMap = new SpriteTilemap();
	spriteMap->SetMesh(mesh);
	spriteMap->SetSpriteSource(spriteSource);
	spriteMap->SetTilemap(map);

	ColliderTilemap* colliderTilemap = new ColliderTilemap();
	colliderTilemap->SetTilemap(map);

	//create object add all the components
	GameObject* tileMap = new GameObject("TileMap");
	tileMap->AddComponent(transform);
	tileMap->AddComponent(spriteMap);
	tileMap->AddComponent(colliderTilemap);

	return tileMap;
}

// Create a game object archetype that uses the Player texture.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreatePlayer(Mesh* mesh, SpriteSource* spriteSource, GameObject* beam, Collider* map)
{
	UNREFERENCED_PARAMETER(beam);
	UNREFERENCED_PARAMETER(map);
	UNREFERENCED_PARAMETER(spriteSource);

	// Create object and initilize all components
	GameObject* playerObject = new GameObject("Player");
	Transform* transform = new Transform(0.0f, 0.0f);
	Physics* physics = new Physics();
	Sprite* sprite = new Sprite();
	ColliderRectangle* colliderRectangle = new ColliderRectangle(Vector2D(transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f));
	Behaviors::PlayerMovement* playerMovement = new Behaviors::PlayerMovement();
	Behaviors::PlayerShooting* playerShooting = new Behaviors::PlayerShooting(beam, map);
	Behaviors::Health* health = new Behaviors::Health(5, 2.0f);

	transform->SetScale(Vector2D(50.0f, 50.0f));
	sprite->SetMesh(mesh);
	//sprite->SetSpriteSource(spriteSource);

	// Add all the components
	playerObject->AddComponent(transform);
	playerObject->AddComponent(physics);
	playerObject->AddComponent(sprite);
	playerObject->AddComponent(playerMovement);
	playerObject->AddComponent(colliderRectangle);
	playerObject->AddComponent(playerShooting);
	playerObject->AddComponent(health);

	//GameObjectFactory::GetInstance().SaveObjectToFile(asteroidObject);

	return playerObject;
}

GameObject* Archetypes::CreateEnemySpawner()
{
	GameObject* spawner = new GameObject("Spawner");

	Behaviors::EnemySpawner* enemySpawner = new Behaviors::EnemySpawner();

	spawner->AddComponent(enemySpawner);

	return spawner;
}

// Create an enemy object
// Params:
//   mesh = The mesh to use for the sprite.
//   spriteSource = The sprite source to use for the sprite.
// Returns:
//   A pointer to the newly constructed game object.
GameObject* Archetypes::CreateEnemyOneObject(Mesh * mesh, Vector2D spawnPos/*, SpriteSource * spriteSource*/)
{
	//initilize all components
	Transform* transform = new Transform(spawnPos.x, spawnPos.y);
	transform->SetScale(Vector2D(50.0f, 50.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	//sprite->SetSpriteSource(spriteSource);
	sprite->SetColor(Colors::Red);

	ColliderRectangle* colliderRectangle = new ColliderRectangle(Vector2D(transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f));

	Physics* physics = new Physics();

	Behaviors::Health* health = new Behaviors::Health(5);

	Behaviors::EnemyOne* enemy = new Behaviors::EnemyOne(1.0f, 100.0f, 150.0f, 250.0f, 300.0f);

	//create object add all the components
	GameObject* enemyObject = new GameObject("Enemy");

	enemyObject->AddComponent(transform);
	enemyObject->AddComponent(sprite);
	enemyObject->AddComponent(colliderRectangle);
	enemyObject->AddComponent(physics);
	enemyObject->AddComponent(health);
	enemyObject->AddComponent(enemy);

	return enemyObject;
}

GameObject* Archetypes::CreateEnemyTwoObject(Mesh * mesh, Vector2D spawnPos/*, SpriteSource * spriteSource*/)
{
	//initilize all components
	Transform* transform = new Transform(spawnPos.x, spawnPos.y);
	transform->SetScale(Vector2D(75.0f, 75.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	//sprite->SetSpriteSource(spriteSource);
	sprite->SetColor(Colors::Yellow);

	ColliderRectangle* colliderRectangle = new ColliderRectangle(Vector2D(transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f));

	Physics* physics = new Physics();

	Behaviors::Health* health = new Behaviors::Health(15);

	Behaviors::EnemyTwo* enemy = new Behaviors::EnemyTwo();

	//create object add all the components
	GameObject* enemyObject = new GameObject("Enemy");

	enemyObject->AddComponent(transform);
	enemyObject->AddComponent(sprite);
	enemyObject->AddComponent(colliderRectangle);
	enemyObject->AddComponent(physics);
	enemyObject->AddComponent(health);
	enemyObject->AddComponent(enemy);

	return enemyObject;
}

GameObject* Archetypes::CreateEnemyThreeObject(Mesh * mesh, Vector2D spawnPos/*, SpriteSource * spriteSource*/)
{
	//initilize all components
	Transform* transform = new Transform(spawnPos.x, spawnPos.y);
	transform->SetScale(Vector2D(50.0f, 50.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	//sprite->SetSpriteSource(spriteSource);
	sprite->SetColor(Colors::Violet);

	ColliderRectangle* colliderRectangle = new ColliderRectangle(Vector2D(transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f));

	Physics* physics = new Physics();

	Behaviors::Health* health = new Behaviors::Health(10);

	Behaviors::EnemyThree* enemy = new Behaviors::EnemyThree();

	//create object add all the components
	GameObject* enemyObject = new GameObject("Enemy");

	enemyObject->AddComponent(transform);
	enemyObject->AddComponent(sprite);
	enemyObject->AddComponent(colliderRectangle);
	enemyObject->AddComponent(physics);
	enemyObject->AddComponent(health);
	enemyObject->AddComponent(enemy);

	return enemyObject;
}

// Create the laser beams object.
// Params:
//   mesh  = The mesh to use for the object's sprite.
//	 spriteSource = The sprite source to use for the object.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreateLaserBeamObject(Mesh * mesh)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(20.0f, 20.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);

	//create object add all the components
	GameObject* laser = new GameObject("LaserBeam");
	laser->AddComponent(transform);
	laser->AddComponent(sprite);

	//GameObjectFactory::GetInstance().SaveObjectToFile(bullet);

	return laser;
}

GameObject* Archetypes::CreateAcidPoolArchetype(Mesh* mesh, SpriteSource* spriteSource)
{
	GameObject* acidPool = new GameObject("AcidPool");

	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(128.0f, 128.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);

	ColliderCircle* collider = new ColliderCircle(64.0f);

	Behaviors::TimedDeath* timedDeath = new Behaviors::TimedDeath(5.0f, false);

	acidPool->AddComponent(transform);
	acidPool->AddComponent(sprite);
	acidPool->AddComponent(collider);
	acidPool->AddComponent(timedDeath);

	return acidPool;
}

//==================================================================-