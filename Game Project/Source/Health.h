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
#include <Color.h>

class Sprite;

namespace Behaviors
{
	class Health : public Component
	{
	public:
		Health(int maxHealth = 5, float invTime = 0.5f);

		Component* Clone() const;

		void Initialize() override;
		void Update(float dt) override;

		void Add(int toAdd);
		void Subtract(int toSubtract);

		int GetHealth();
		int GetMaxHealth();

	private:

		void CheckCap();

		int maxHealth;
		int currHealth;

		float invincibilityTime;
		float flashTimer;
		float timer1; // Invincibility Time
		float timer2; // Flash Timer

		bool invincible;

		Sprite* sprite;

		float invAlpha;

	};
}