//------------------------------------------------------------------------------
//
// File Name:	Health.h
// Author(s):	Bar Ben-zvi
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#pragma once

#include "Component.h"


namespace Behaviors
{
	class Health : public Component
	{
	public:
		Health(int maxHealth = 5);

		Component* Clone() const;

		void Add(int toAdd);
		void Subtract(int toSubtract);

		int GetHealth();
		int GetMaxHealth();

	private:

		void CheckCap();

		int maxHealth;
		int currHealth;

	};
}