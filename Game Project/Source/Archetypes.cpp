//==================================================================-
/*
/file   Archetypes.cpp
/author Jakob McFarland
/date   12/4/2018
/brief

This is the implementation file for all member functions
of the class Archetypes, as specified in specification
file Archetypes.h.

*/
//==================================================================-

#include "stdafx.h"
#include "Archetypes.h"

#include "PlayerShip.h"
#include "TimedDeath.h"
#include "ScreenWrap.h"
#include "ColliderPoint.h"
#include "ColliderCircle.h"
#include "ColliderRectangle.h"
#include "ColliderTilemap.h"
#include "MonkeyMovement.h"
#include "PlayerMovement.h"
#include "Colorchange.h"
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


//==================================================================-
// Public Functions:
//==================================================================-

// Create a game object that uses the Ship texture.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreateShip(Mesh* mesh)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(50.0f, 50.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetColor(Colors::LightBlue);

	Physics* physics = new Physics();
	Behaviors::PlayerShip* playerShip = new Behaviors::PlayerShip(100.0f, 200.f, 5.0f, 100.0f);

	//create object add all the components
	GameObject* playerShipObject = new GameObject("PlayerShip");
	playerShipObject->AddComponent(transform);
	playerShipObject->AddComponent(physics);
	playerShipObject->AddComponent(sprite);
	playerShipObject->AddComponent(playerShip);

	//GameObjectFactory::GetInstance().SaveObjectToFile(playerShipObject);

	return playerShipObject;
}

// Create a game object archetype that uses the Bullet texture.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreateBulletArchetype(Mesh* mesh)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(7.0f, 7.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);

	Physics* physics = new Physics();
	Behaviors::TimedDeath* timedDeath = new Behaviors::TimedDeath(5.0f);

	//create object add all the components
	GameObject* bullet = new GameObject("Bullet");
	bullet->AddComponent(transform);
	bullet->AddComponent(physics);
	bullet->AddComponent(sprite);
	bullet->AddComponent(timedDeath);

	//GameObjectFactory::GetInstance().SaveObjectToFile(bullet);

	return bullet;
}

// Create a game object archetype that uses the Asteroid texture.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreateMonkey(Mesh* mesh, SpriteSource* spriteSource)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(100.0f, 100.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);

	Physics* physics = new Physics();
	ColliderRectangle* colliderRectangle = 
		new ColliderRectangle(Vector2D(transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f));

	Behaviors::MonkeyMovement* monkeyMovement = new Behaviors::MonkeyMovement();

	//create object add all the components
	GameObject* monkeyObject = new GameObject("Monkey");
	monkeyObject->AddComponent(transform);
	monkeyObject->AddComponent(physics);
	monkeyObject->AddComponent(sprite);
	monkeyObject->AddComponent(monkeyMovement);
	monkeyObject->AddComponent(colliderRectangle);

	//GameObjectFactory::GetInstance().SaveObjectToFile(asteroidObject);

	return monkeyObject;
}

// Create the circle game object.
// Params:
//   mesh  = The mesh to use for the object's sprite.
//   spriteSource = The sprite source to use for the object.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreateCircle(Mesh* mesh, SpriteSource* spriteSource)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(100.0f, 100.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);

	Physics* physics = new Physics();
	Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();

	ColliderCircle* colliderCircle = new ColliderCircle(transform->GetScale().x * 0.5f);
	Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Colors::Yellow, Colors::Red);

	//create object add all the components
	GameObject* circle = new GameObject("Circle");
	circle->AddComponent(transform);
	circle->AddComponent(physics);
	circle->AddComponent(sprite);
	circle->AddComponent(screenWrap);
	circle->AddComponent(colliderCircle);
	circle->AddComponent(colorChange);

	//GameObjectFactory::GetInstance().SaveObjectToFile(bullet);

	return circle;
}

// Create the point game object.
// Params:
//   mesh  = The mesh to use for the object's sprite.
//   spriteSource = The sprite source to use for the object.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreatePoint(Mesh* mesh, SpriteSource* spriteSource)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(20.0f, 20.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);

	Physics* physics = new Physics();
	Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();

	ColliderPoint* colliderPoint = new ColliderPoint();
	Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Colors::Blue, Colors::Red);

	//create object add all the components
	GameObject* point = new GameObject("Point");
	point->AddComponent(transform);
	point->AddComponent(physics);
	point->AddComponent(sprite);
	point->AddComponent(screenWrap);
	point->AddComponent(colliderPoint);
	point->AddComponent(colorChange);

	//GameObjectFactory::GetInstance().SaveObjectToFile(bullet);

	return point;
}

// Create the rectangle game object.
// Params:
//   mesh  = The mesh to use for the object's sprite.
// Returns:
//	 A pointer to the newly constructed game object
GameObject* Archetypes::CreateRectangle(Mesh* mesh)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(250.0f, 100.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);

	Physics* physics = new Physics();
	Behaviors::ScreenWrap* screenWrap = new Behaviors::ScreenWrap();

	ColliderRectangle* colliderRectangle = new ColliderRectangle( Vector2D( transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f));
	Behaviors::ColorChange* colorChange = new Behaviors::ColorChange(Colors::Green, Colors::Red);

	//create object add all the components
	GameObject* rect = new GameObject("Rect");
	rect->AddComponent(transform);
	rect->AddComponent(physics);
	rect->AddComponent(sprite);
	rect->AddComponent(screenWrap);
	rect->AddComponent(colliderRectangle);
	rect->AddComponent(colorChange);

	//GameObjectFactory::GetInstance().SaveObjectToFile(bullet);

	return rect;
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
GameObject* Archetypes::CreatePlayer(Mesh* mesh, SpriteSource* spriteSource)
{
	// Create object and initilize all components
	GameObject* playerObject = new GameObject("Player");
	Transform* transform = new Transform(0.0f, 0.0f);
	Physics* physics = new Physics();
	Sprite* sprite = new Sprite();
	ColliderRectangle* colliderRectangle = new ColliderRectangle(Vector2D(transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f));
	Behaviors::PlayerMovement* playerMovement = new Behaviors::PlayerMovement();

	transform->SetScale(Vector2D(50.0f, 50.0f));
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);

	// Add all the components
	playerObject->AddComponent(transform);
	playerObject->AddComponent(physics);
	playerObject->AddComponent(sprite);
	playerObject->AddComponent(playerMovement);
	playerObject->AddComponent(colliderRectangle);

	//GameObjectFactory::GetInstance().SaveObjectToFile(asteroidObject);

	return playerObject;
}

/*
// Create a collectable object
// Params:
//   mesh = The mesh to use for the sprite.
//   spriteSource = The sprite source to use for the sprite.
// Returns:
//   A pointer to the newly constructed game object.
GameObject * Archetypes::CreateCollectableObject(Mesh * mesh, SpriteSource * spriteSource)
{
	//initilize all components
	Transform* transform = new Transform(100.0f, 50.0f);
	transform->SetScale(Vector2D(50.0f, 50.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	sprite->SetColor(Colors::Yellow);

	ColliderCircle* colliderCircle = new ColliderCircle();
	colliderCircle->SetRadius( transform->GetScale().x * 0.5f );

	//create object add all the components
	GameObject* collectable = new GameObject("Collectable");
	collectable->AddComponent(transform);
	collectable->AddComponent(sprite);
	collectable->AddComponent(colliderCircle);

	return collectable;
}
*/

/*
// Create a hazard object
// Params:
//   mesh = The mesh to use for the sprite.
//   spriteSource = The sprite source to use for the sprite.
// Returns:
//   A pointer to the newly constructed game object.
GameObject * Archetypes::CreateHazardObject(Mesh * mesh, SpriteSource * spriteSource)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(50.0f, 50.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);

	ColliderRectangle* colliderRectangle = new ColliderRectangle();
	colliderRectangle->SetExtents( Vector2D( transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f) );

	//create object add all the components
	GameObject* hazard = new GameObject("Hazard");
	hazard->AddComponent(transform);
	hazard->AddComponent(sprite);
	hazard->AddComponent(colliderRectangle);

	return hazard;
}
*/

/*
// Create an enemy object
// Params:
//   mesh = The mesh to use for the sprite.
//   spriteSource = The sprite source to use for the sprite.
// Returns:
//   A pointer to the newly constructed game object.
GameObject * Archetypes::CreateEnemyObject(Mesh * mesh, SpriteSource * spriteSource)
{
	//initilize all components
	Transform* transform = new Transform(0.0f, 0.0f);
	transform->SetScale(Vector2D(50.0f, 50.0f));

	Sprite* sprite = new Sprite();
	sprite->SetMesh(mesh);
	sprite->SetSpriteSource(spriteSource);
	sprite->SetColor(Colors::Red);

	ColliderRectangle* colliderRectangle = new ColliderRectangle( Vector2D( transform->GetScale().x * 0.5f, transform->GetScale().y * 0.5f) );

	Physics* physics = new Physics();

	Behaviors::Enemy* enemy = new Behaviors::Enemy();

	//create object add all the components
	GameObject* enemyObject = new GameObject("Enemy");
	enemyObject->AddComponent(transform);
	enemyObject->AddComponent(sprite);
	enemyObject->AddComponent(colliderRectangle);
	enemyObject->AddComponent(physics);
	enemyObject->AddComponent(enemy);

	return enemyObject;
}
*/

//==================================================================-