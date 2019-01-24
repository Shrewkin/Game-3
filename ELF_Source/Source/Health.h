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
		Health(int maxHealth = 5, float invTimer = 0.3f, float flashTime = 0.05f, GameObject* toCreate = nullptr);

		Component* Clone() const;

		void Add(int toAdd);
		void Subtract(int toSubtract);

		void Update(float dt) override;

		int GetHealth() const;
		int GetMaxHealth() const;

		void SetToCreate(GameObject* newToCreate);

	private:

		void CheckCap();

		int maxHealth;
		int currHealth;

		float invincibilityTimer;
		float flashTimer;
		float timer1; //invincibility timer
		float timer2; //flash timer
		bool invincible;

		GameObject* toCreate;

	};
}