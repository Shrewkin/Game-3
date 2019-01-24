//------------------------------------------------------------------------------
//
// File Name:	Health.cpp
// Author(s):	Bar Ben-zvi
// Project:		Game Prototype 3
// Course:		WANIC VGP2 2018-2019
//
// Copyright © 2018 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

#include "stdafx.h"

#include "Health.h"
#include "GameObject.h"
#include "Sprite.h"
#include "LoseLevel.h"
#include <Space.h>

namespace Behaviors
{

	Health::Health(int maxHealth, float invTime, float flashTime)
		: Component("Health"), maxHealth(maxHealth), currHealth(maxHealth), invincibilityTimer(invTime), flashTimer(flashTime),
		  timer1(invTime), timer2(flashTime), invincible(false)
	{
	}

	Component* Health::Clone() const
	{
		return new Health(*this);
	}

	void Health::Update(float dt)
	{
		if (invincible)
		{
			timer1 -= dt;
			timer2 -= dt;
			Sprite* sprite = static_cast<Sprite*>(GetOwner()->GetComponent("Sprite"));
			if (timer2 <= 0)
			{
				
				if (sprite->GetAlpha() == 0.5f)
				{
					sprite->SetAlpha(1.0f);
				}
				else
				{
					sprite->SetAlpha(0.5f);
				}
				timer2 = flashTimer;
			}
			if (timer1 <= 0)
			{
				invincible = false;
				timer1 = invincibilityTimer;
				sprite->SetAlpha(1.0f);
			}
		}
	}

	void Health::Add(int toAdd)
	{
		currHealth += toAdd;
		CheckCap();
	}

	void Health::Subtract(int toSubtract)
	{
		if (!invincible)
		{
			currHealth -= toSubtract;
			invincible = true;
			if (currHealth <= 0)
			{
				//change to lose level on player death.
				if (GetOwner()->GetName() == "Player")
				{
					GetOwner()->GetSpace()->SetLevel(new Levels::LoseLevel());
				}

				GetOwner()->Destroy();
			}
		}
	}

	int Health::GetHealth()
	{
		return currHealth;
	}

	int Health::GetMaxHealth()
	{
		return maxHealth;
	}

	void Health::CheckCap()
	{
		if (currHealth > maxHealth)
		{
			currHealth = maxHealth;
		}
	}
}