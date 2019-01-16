//------------------------------------------------------------------------------
//
// File Name:	EnemyOne.h
// Author(s):	Bar Ben-zvi
// Description: Enemy one attempts to stay at a specified distance from the player and fire at the player
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Component.h"
#include <Vector2D.h>

namespace Behaviors
{
	class EnemyOne : public Component
	{
	public:

		EnemyOne(float dist = 10.0f, float fireRate = 1.0f, float walkSpeed = 100.0f, float runSpeed = 200.0f);

		Component* Clone() const;



	};
}